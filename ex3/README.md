# Exercise 3 – Task Management System with SortedList

This assignment focuses on implementing a **task management system** in C++ using a custom generic container `SortedList` and applying object-oriented programming principles. It includes both a **data structures component** and an **application component**.

---

---

## SortedList

A generic container template implementing a **sorted linked list**.  

- Elements are always kept in sorted order (using `operator>`).  
- Supports duplicates (older items are considered “greater”).  
- Key operations:
  - `insert(element)` – inserts in sorted position
  - `remove(iterator)` – removes the element pointed by iterator
  - `length()` – returns number of elements
  - `filter(predicate)` – returns new list with elements matching predicate
  - `apply(function)` – applies a function to all elements, returns new list
  - Iterators: `begin()`, `end()`, `ConstIterator` with `++`, `!=`, `*`

Exceptions:  
- Incrementing past end throws `std::out_of_range`.  
- Removing with invalid iterators is handled safely.

---

## Task

Represents a task with:

- **ID** (assigned by TaskManager)  
- **Priority** (0–100 range enforced)  
- **Type** (`Meeting`, `Development`, `Testing`, etc.)  
- **Description** (free text)  

Features:  
- Comparison (`operator>`) based on priority (higher first).  
- Output (`operator<<`) prints full details.  
- Constructor ensures priority stays within bounds.  

---

## Person

Represents an employee that can have tasks.  

- Stores tasks in a `SortedList<Task>`.  
- Key operations:
  - `assignTask(task)` – add task
  - `completeTask()` – remove and return ID of highest-priority task
  - `getHighestPriorityTask()` – access top task
- Output operator prints person name and tasks.  

---

## TaskManager

Coordinates tasks among multiple people.  

- Max employees: 10  
- Key operations:
  - `assignTask(personName, task)` – assign task, add person if new (throws if limit reached)
  - `completeTask(personName)` – removes top task for a person
  - `bumpPriorityByType(type, delta)` – increases priority of all tasks of given type
  - Printing methods:
    - `printAllEmployees()` – print each person and tasks
    - `printAllTasks()` – print all tasks by priority
    - `printTasksByType(type)` – print tasks of a given type

---

## Tests

A comprehensive test runner (`main.cpp`) is provided. 

Compile:
```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o TaskManager *.cpp
```

Run all tests:
./TaskManager
```

Run a single test (example):
```bash
./tests 1 > test1.out
diff --strip-trailing-cr -B -Z test1.out tests/test1.expected
```

---
## Tests with Valgrind (Memory Check)

To also check for memory leaks and invalid memory usage, run the program under **Valgrind**:

```bash
g++ -DNDEBUG -std=c++17 -Wall -pedantic-errors -Werror -o TaskManager *.cpp
valgrind --leak-check=full --show-leak-kinds=all ./TaskManager 1 > test1.out
diff --strip-trailing-cr -B -Z test1.out tests/test1.expected
```

This runs the same test as before, but Valgrind will additionally report any memory errors or leaks.

---

## Key Skills Practiced

- Template programming and iterators in C++  
- Exception safety and deep copies  
- Operator overloading (`<<`, `>`, etc.)  
- Building modular systems (`Task`, `Person`, `TaskManager`)  
- Using data structures in practical applications  
