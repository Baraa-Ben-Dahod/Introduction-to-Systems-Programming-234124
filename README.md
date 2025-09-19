````markdown
# Technion – Introduction to Systems Programming (234124)

This repository contains my solutions to the six programming exercises (ex0–ex5) from the Technion course *Introduction to Systems Programming (Matam)*.

## Repository Structure

- **ex0** – Intro C programs (`mtm_bug.c`, `mtm_tot.c`) with tests  
- **ex1** – Blockchain implementation in C++ (linked list of transactions)  
- **ex2** – Matrix operations (rotation, multiplication, error handling)  
- **ex3** – Task Manager system with `SortedList`, `Task`, and `Person` classes  
- **ex4** – *MatamStory*: a small game simulation (players, jobs, events, event factory)  
- **ex5** – Enigma encryption machine in Python (configurable with JSON, input/output tests)

## Testing

Each folder contains:
- Input files (`*.in`) and expected outputs (`*.expected`)  
- Config files where relevant (`*.json`)  
- A `README.md` with build/run instructions

To run a test:
```bash
# Example for ex2
g++ -std=c++17 -Wall -pedantic-errors -Werror -DNDEBUG *.cpp -o matrix_tests
./matrix_tests
````

```bash
# Example for ex5
python3 enigma.py -c config_file.json -i tests/test1.in -o test1.out
diff --strip-trailing-cr -B -Z test1.out tests/test1.expected
```

## Notes

* Code follows the course guidelines and was checked against both the official tests and additional external tests.
* Each assignment has its own README with more details.