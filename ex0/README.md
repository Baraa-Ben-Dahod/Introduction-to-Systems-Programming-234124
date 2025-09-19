# Exercise 0 – Introduction to C & Shell

This folder contains the first homework assignment, focused on practicing **basic C programming**, **debugging**, and **testing with input/output files**.  
It is divided into two main C programs and additional test materials.

---

## `mtm_bug.c`

This program demonstrates string handling in C and is used mainly for **debugging practice**.

### Features
- Reads a number `n` and then `n` words from the user.  
- Finds and prints:
  - The **longest word** (by length).  
  - The **lexicographically maximal** word.  
  - The **lexicographically minimal** word.  
- Implements helper functions for:
  - Swapping strings.
  - Finding the longest string.
  - Sorting an array of strings (bubble sort).
  - Memory allocation and cleanup for dynamically read words.

### Input / Output Example
```
Enter number of strings:
3
hello
apple
zebra
```
Output:
```
The longest word is: hello
The maximal word lexicographically is: zebra
The minimal word lexicographically is: apple
```

---

## `mtm_tot.c`

This program works with integer arrays and detects **powers of 2**.

### Features
- Reads an integer `n` (the size of the array).  
- Reads `n` integers.  
- For each integer:
  - Checks if it is a **power of 2**.  
  - Prints the exponent `j` such that `a = 2^j`.  
- At the end, prints the **total sum of all exponents**.

### Input / Output Example
```
Enter size of input:
4
1 2 8 12
```
Output:
```
The number 1 is a power of 2: 1 = 2^0
The number 2 is a power of 2: 2 = 2^1
The number 8 is a power of 2: 8 = 2^3
Total exponent sum is 4
```

---

## Tests

- **part1/** – input and expected output files for `mtm_bug.c`.  
- **part2/** – input and expected output files for `mtm_tot.c`.  

To test a program manually:
```bash
gcc -std=c99 -Wall -pedantic-errors -Werror code/mtm_bug.c -o mtm_bug
./mtm_bug < part1/test1.in > out.txt
diff --strip-trailing-cr out.txt part1/test1.expected
```
Same idea applies for `mtm_tot.c` with files under `part2/`.

---

## Running with Valgrind (Memory Check)

To also check for memory leaks and invalid memory usage with **Valgrind**, prepend the program execution with `valgrind`:

```bash
gcc -std=c99 -Wall -pedantic-errors -Werror code/mtm_bug.c -o mtm_bug
valgrind --leak-check=full --show-leak-kinds=all ./mtm_bug < part1/test1.in > out.txt
diff --strip-trailing-cr out.txt part1/test1.expected
```

Or for `mtm_tot.c`:

```bash
gcc -std=c99 -Wall -pedantic-errors -Werror code/mtm_tot.c -o mtm_tot
valgrind --leak-check=full --show-leak-kinds=all ./mtm_tot < part2/test1.in > out.txt
diff --strip-trailing-cr out.txt part2/test1.expected
```

This way you verify **both correctness** (with `diff`) and **memory safety** (with `valgrind`).  

--- 
## Key Skills Practiced 
- Working with **dynamic memory allocation** in C. 
- Using **strings and arrays** safely. 
- Debugging **segmentation faults** and memory leaks. 
- Validating program output against expected results.