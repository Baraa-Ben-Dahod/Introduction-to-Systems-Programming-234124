# Exercise 2 – Matrices, Movies & Pirates

This assignment combines **object-oriented C++ programming** with matrix operations and simple class design. It includes three main parts:

---

---

## Matrix Class

Implements a **2D integer matrix** with support for:

- **Element access** with bounds checking:
  ```cpp
  m(0, 1) = 5;
  ```

- **Arithmetic operators**:
  - `+`, `-`, `*` (matrix multiplication and scalar multiplication)
  - `+=`, `-=`, `*=`
  - Unary `-` (negation)

- **Comparison operators**:
  - `==`, `!=`

- **Transformations**:
  - `transpose()`
  - `rotateClockwise()`, `rotateCounterClockwise()`

- **Matrix norms & determinant**:
  - `CalcFrobeniusNorm(matrix)`
  - `CalcDeterminant(matrix)`

- **Error handling**:
  - Throws MatamErrorType via `exitWithError` when accessing out of bounds or using invalid sizes.

---

## MataMvidia Class

Represents a **movie made of matrices** (each frame is a Matrix).

- Stores:
  - Movie name
  - Producer name
  - Dynamic array of frames

- Supports:
  - `operator[]` – access a specific frame
  - `operator+=` – add a new frame or append another movie
  - `operator+` – merge two movies
  - `operator<<` – print the movie in the format:

    ```
    Movie Name: <name>
    Author: <producer>
    
    Frame 0:
    |...|...|
    
    Frame 1:
    |...|...|
    
    -----End of Movie-----
    ```

---

## Pirate Class

A simple class used in the dry part of the exercise.

- Stores a pirate's name.
- Provides `getName`, `setName`, and printing with `operator<<`.
- Demonstrated in `main.cpp` by building a small pirate crew.

---

## Tests

Run `tests.cpp` to validate the `Matrix` and `MataMvidia` implementations.  
Expected output is in `test.expected`.

Example compile & run:

```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o Mvidia *.cpp
./Mvidia > test.out
diff --strip-trailing-cr -B -Z test.out test.expected

```
## Tests with Valgrind (Memory Check)

To also check for memory leaks and invalid memory usage, run the program under **Valgrind**:

```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o Mvidia *.cpp
valgrind --leak-check=full --show-leak-kinds=all ./Mvidia > test.out
diff --strip-trailing-cr -B -Z test.out test.expected
```

This runs the same test as before, but Valgrind will additionally report any memory errors or leaks.

---

## Key Skills Practiced

- Operator overloading in C++  
- Deep copy, destructors, memory management  
- Exception-style error handling with enums  
- Using classes to model mathematical and multimedia concepts  
