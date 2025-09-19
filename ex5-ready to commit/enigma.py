import json
import argparse
import sys

# Error messages as per spec
USAGE_MESSAGE = "Usage: python3 enigma.py -c <config_file> -i <input_file> -o <output_file>"
ENIGMA_ERROR = "The enigma script has encountered an error"


class Enigma:
    MAX_NUM = 8
    CHANGE_WHEN_DIVIDES_BY_TEN = 10
    CHANGE_WHEN_DIVIDES_BY_THREE = 5
    EVEN = 2
    DIVISOR = 26
    MINUS = -1

    def __init__(self, hash_map, wheels, reflector_map):
        self.hash_map = hash_map
        self.initial_wheels = wheels[:]
        self.wheels = wheels[:]
        self.reflector_map = reflector_map
        self.counter = 0

    def encrypt(self, message: str) -> str:
        """Encrypt a full message string, resetting state before and after."""
        self._reset_state()
        encrypted_message = [self.encrypt_letter(ch) for ch in message]
        self._reset_state()
        return ''.join(encrypted_message)

    def encrypt_letter(self, c: str) -> str:
        """Encrypt a single character (update wheels even for non-letters)."""
        if not ('a' <= c <= 'z'):
            self._update_wheel()
            return c

        
        i = self.hash_map[c]
        i = self._i_from_v(i)
        c1 = self._get_key_by_value(self.hash_map, i)

        
        c2 = self.reflector_map[c1]

       
        i = self.hash_map[c2]
        i = self._i_from_v(i, self.MINUS)
        c3 = self._get_key_by_value(self.hash_map, i)

        self.counter += 1
        self._update_wheel()
        return c3

    def _get_key_by_value(self, mapping, target_value):
        for key, value in mapping.items():
            if value == target_value:
                return key
        return None

    def _i_from_v(self, i: int, operator: int = 1) -> int:
        """Apply the wheel transformation."""
        value = (2 * self.wheels[0] - self.wheels[1] + self.wheels[2]) % self.DIVISOR
        shift = value if value != 0 else 1
        return (i + operator * shift) % self.DIVISOR

    def _update_wheel(self):
        """Update wheels based on current counter index."""
        # wheel[0]: increment; wrap 8 -> 1
        self.wheels[0] = 1 if self.wheels[0] + 1 > self.MAX_NUM else self.wheels[0] + 1

        # wheel[1]: if message index even -> double; else decrement by 1
        if self.counter % self.EVEN == 0:
            self.wheels[1] *= 2
        else:
            self.wheels[1] -= 1

        # wheel[2]: set depending on divisibility of index by 10 or 3
        if self.counter % 10 == 0:
            self.wheels[2] = self.CHANGE_WHEN_DIVIDES_BY_TEN
        elif self.counter % 3 == 0:
            self.wheels[2] = self.CHANGE_WHEN_DIVIDES_BY_THREE
        else:
            self.wheels[2] = 0

    def _reset_state(self):
        """Reset counter and wheels to initial config."""
        self.counter = 0
        self.wheels = self.initial_wheels[:]


class JSONFileError(Exception):
    def __init__(self, message):
        super().__init__(message)
        self.message = message


def _usage_and_exit() -> None:
    sys.stdout.write(USAGE_MESSAGE)
    sys.stdout.flush()
    sys.exit(1)


def _validate_config(data):
    """Strictly validate config JSON. Raise JSONFileError on any issue."""
    try:
        hash_map = data["hash_map"]
        wheels = data["wheels"]
        reflector_map = data["reflector_map"]
    except Exception:
        raise JSONFileError(ENIGMA_ERROR)

    # hash_map checks
    if not isinstance(hash_map, dict) or len(hash_map) != 26:
        raise JSONFileError(ENIGMA_ERROR)
    for k, v in hash_map.items():
        if not (isinstance(k, str) and len(k) == 1 and 'a' <= k <= 'z'):
            raise JSONFileError(ENIGMA_ERROR)
        if not (isinstance(v, int) and 0 <= v <= 25):
            raise JSONFileError(ENIGMA_ERROR)

    # wheels checks
    if not (isinstance(wheels, list) and len(wheels) == 3):
        raise JSONFileError(ENIGMA_ERROR)
    w1, w2, w3 = wheels
    if not (isinstance(w1, int) and 1 <= w1 <= 8):
        raise JSONFileError(ENIGMA_ERROR)
    if not (isinstance(w2, int) and 1 <= w2 <= 26):
        raise JSONFileError(ENIGMA_ERROR)
    if not (isinstance(w3, int) and w3 in (0, 5, 10)):
        raise JSONFileError(ENIGMA_ERROR)

    # reflector_map checks (symmetric involution on a-z)
    if not isinstance(reflector_map, dict):
        raise JSONFileError(ENIGMA_ERROR)
    for k, v in reflector_map.items():
        if not (isinstance(k, str) and len(k) == 1 and 'a' <= k <= 'z'):
            raise JSONFileError(ENIGMA_ERROR)
        if not (isinstance(v, str) and len(v) == 1 and 'a' <= v <= 'z'):
            raise JSONFileError(ENIGMA_ERROR)
    for a, b in reflector_map.items():
        if reflector_map.get(b) != a:
            raise JSONFileError(ENIGMA_ERROR)

    return hash_map, wheels, reflector_map


def load_enigma_from_path(path):
    try:
        with open(path, 'r', encoding='utf-8') as f:
            data = json.load(f)
        hash_map, wheels, reflector_map = _validate_config(data)
        return Enigma(hash_map, wheels, reflector_map)
    except JSONFileError:
        raise
    except Exception:
        raise JSONFileError(ENIGMA_ERROR)


def parse_args(argv):
    parser = argparse.ArgumentParser(add_help=False)
    parser.add_argument('-c', '--config')
    parser.add_argument('-i', '--input')
    parser.add_argument('-o', '--output')
    parser.add_argument('-h', '--help', action='store_true')
    args, unknown = parser.parse_known_args(argv)

    if args.help or unknown or not args.config or not args.input:
        _usage_and_exit()

    return args


def main(argv=None):
    if argv is None:
        argv = sys.argv[1:]

    try:
        args = parse_args(argv)
        enigma = load_enigma_from_path(args.config)

        try:
            with open(args.input, 'r', encoding='utf-8') as input_file:
                lines = input_file.readlines()
        except Exception:
            print(ENIGMA_ERROR, file=sys.stderr)
            sys.exit(1)

        encrypted_message = ''.join(enigma.encrypt(line) for line in lines)

        if args.output:
            try:
                with open(args.output, 'w', encoding='utf-8') as output_file:
                    output_file.write(encrypted_message)
            except Exception:
                print(ENIGMA_ERROR, file=sys.stderr)
                sys.exit(1)
        else:
            print(encrypted_message, end="")

    except JSONFileError as e:
        print(e.message, file=sys.stderr)
        sys.exit(1)


if __name__ == "__main__":
    main()