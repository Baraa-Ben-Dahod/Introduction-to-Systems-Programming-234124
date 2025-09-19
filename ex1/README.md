# Technion Matam - Homework 1

This directory contains the solution for Homework 1 of the Technion course **Introduction to Systems Programming (234124)**. The assignment revolves around implementing a miniature blockchain data structure, exposing a command-line tool named `mtm_blockchain`, and supporting several data-processing operations on transaction logs.

## Assignment Overview

The project models a blockchain as a singly linked list that stores transactions in reverse chronological order. You are required to implement the API declared in `BlockChain.h` and `Transaction.h`, using helper routines from `Utilities.*`. The core responsibilities are:

- **Loading** a blockchain from a plain-text ledger where each line lists `sender receiver amount timestamp`.
- **Dumping** the chain in a human-readable layout (the `format` operation).
- **Hashing** individual transactions with a deterministic helper function (the `hash` operation).
- **Verifying** that a file of hashed transactions matches the current chain (the `verify` operation). The comparison must handle both `\n` and `\r\n` line endings.
- **Compressing** consecutive blocks that share the same sender and receiver by merging their values (the `compress` operation).
- **Balance queries and transforms**, as defined in the supplied headers, while managing dynamic memory safely.

All structures are already defined; the task is to provide correct logic, maintain ownership discipline, and pass the provided unit tests and Valgrind checks.

## Building

Compile the executable with the flags required by the course infrastructure:

```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -g -o mtm_blockchain *.cpp
```

The build must succeed without warnings; treat any compiler warning as an error.

## Command-Line Usage

The binary expects three arguments:

```
./mtm_blockchain <operation> <source> <target>
```

Supported operations:

- `format` - pretty print the blockchain into `target`.
- `hash` - output hashed transactions to `target`, one per line.
- `compress` - merge adjacent blocks with matching sender and receiver, then dump the formatted chain to `target`.
- `verify` - read hashed strings from `target` and report `Verification passed` or `Verification failed`.

Supplying an unknown operation or the wrong number of parameters prints the usage string from `Utilities.cpp`.

## Running the Provided Tests

The repository ships with four sanity checks under `tests/`. Each exercise reads an input ledger (`*.source`) and expects a specific output (`*.expected`). After building the executable, you can reproduce the full suite manually:

```bash
# inside ex1
./mtm_blockchain format tests/format.source tests/format.target.out
./mtm_blockchain hash tests/hash.source tests/hash.target.out
./mtm_blockchain compress tests/compress.source tests/compress.target.out
./mtm_blockchain verify tests/verify.source tests/verify.target > verify.out

# compare against the expected artefacts (Unix diff shown; use fc/PowerShell diff on Windows)
diff tests/format.target.out tests/format.target.expected
diff tests/hash.target.out tests/hash.target.expected
diff tests/compress.target.out tests/compress.target.expected
diff verify.out tests/verify.expected
```

If every `diff` reports no differences, the implementation matches the examples supplied with the assignment. Remember to remove temporary outputs (`*.out`) if you rerun the tests.

## Implementation Notes

- The blockchain is stored with the newest transaction at the head; when loading from files, reverse the intermediate structure so the public API sees chronological order.
- Use the `hash` helper in `Utilities.cpp` for any hashed representations. Do not modify its definition.
- Always clean up dynamically allocated `Block` nodes via the supplied `destruct` function to avoid leaks.
- Handle platform differences in text files: ignore trailing carriage returns when checking hashed lines so both Unix and Windows outputs pass verification.

## Deliverables

Submit the completed source files (`*.cpp`, `*.h`) without altering the directory layout. Ensure that the provided tests, including Valgrind checks, pass before submission.
