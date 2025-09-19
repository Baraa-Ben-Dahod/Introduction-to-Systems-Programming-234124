**ex5 (Enigma machine)** assignment.
This will summarize the spec (from `hw5.pdf`), your provided implementation (`enigma.py`), and the usage expectations.

---

# Exercise 5 – Enigma Machine (Python)

This assignment implements a simplified version of the **Enigma encryption machine** in Python.
It is split into two main parts:

1. **Coding** – build an `Enigma` class with wheels, hash map, and reflector map that can encrypt messages.
2. **Scripting** – make the program executable from the command line as `enigma.py`, reading configuration and input files, and writing encrypted output.

---

## Enigma Configuration

The machine is defined by three parameters provided in a JSON file:

* **hash\_map**: mapping from lowercase letters `'a'–'z'` to integers `0–25`.
* **wheels**: list of three integers `[W1, W2, W3]`, where:

  * `W1` ∈ \[1,8]
  * `W2` ∈ \[1,8]
  * `W3` ∈ {0,5,10}
* **reflector\_map**: symmetric mapping between letters, e.g. `"a": "q", "q": "a"`.

---

## Encryption Algorithm

For each character `c` in the input:

1. If `c` is not a lowercase letter `a–z`, leave it unchanged (but still update wheels).
2. Otherwise:

   * Map `c → i` using `hash_map`.
   * Compute:

     ```
     value = (2*W1 – W2 + W3) mod 26
     i = i + (value if value != 0 else 1)
     i = i mod 26
     ```
   * Map back to letter `c1`.
   * Reflect `c1 → c2` using `reflector_map`.
   * Map `c2 → i` with `hash_map`.
   * Compute:

     ```
     value = (2*W1 – W2 + W3) mod 26
     i = i – (value if value != 0 else 1)
     i = i mod 26
     ```
   * Map back to letter `c3`.
   * Output `c3`.
3. Update the wheels after each letter:

   * `W1` increments by 1 (rolls over to 1 after 8).
   * `W2` doubles if the message index is even, otherwise decrements by 1.
   * `W3` becomes 10 if the index % 10 == 0,
     becomes 5 if the index % 3 == 0,
     else becomes 0.

After encrypting a full message, reset wheels to their initial state.

---

## Command-Line Script

Usage:

```bash
python3 enigma.py -c <config_file> -i <input_file> -o <output_file>
```

* `-c <config_file>`: required, JSON config with hash\_map, wheels, reflector\_map.
* `-i <input_file>`: required, plaintext input file to encrypt.
* `-o <output_file>`: optional, writes encrypted output to file (otherwise prints to stdout).

### Error Handling

* Missing or wrong arguments → print:

  ```
  Usage: python3 enigma.py -c <config_file> -i <input_file> -o <output_file>
  ```

  and exit with code 1.
* Bad config or input/output file → print:

  ```
  The enigma script has encountered an error
  ```

  to stderr.

---

## Testing

The official tests include:

* **Valid runs**: encrypting input and comparing output to expected.
* **Bad config file**: should trigger the generic error.
* **Bad input file**: should trigger the generic error.
* **Bad JSON**: should trigger the generic error.
* **Missing arguments**: should print the usage string.

### Example

```bash
python3 enigma.py -c config_file.json -i tests/test1.in -o test1.out
diff --strip-trailing-cr -B -Z test1.out tests/test1.expected
```

---

## Key Skills Practiced

* File parsing (JSON, text files).
* Class and function design in Python.
* Command-line argument parsing with `argparse`.
* Robust error handling and exception safety.

---