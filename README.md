# MiniDB

A lightweight in-memory database written in C++17 with a custom command-line interface (CLI).

This project was built to explore how basic database systems work under the hood, including data storage, command parsing, and query execution using only standard C++ libraries.

---

## Features

- INSERT records (id, age, name)
- REMOVE records by ID
- UPDATE records (partial field updates supported)
- SELECT queries (ALL or by ID)
- Fast in-memory storage using unordered_map
- Simple CLI-based interaction system

---

## Example Usage

Run the program and enter commands:

INSERT 1 25 John
INSERT 2 30 Alice
INSERT 3 19 Bob

---

SELECT ALL
Displays all records in the database.

---

SELECT 2
Finds record with ID = 2.

---

UPDATE 1 age=26 name=JohnDoe
Updates only the provided fields.

---

REMOVE 2
Deletes record with ID 2.

---

EXIT
Closes the program.

---

## Architecture

The project is divided into three main layers:

### CLI Layer
Handles user input and command routing.

- handleInsert
- handleRemove
- handleUpdate
- handleSelect

### Database Layer
Core data storage and logic.

- Uses unordered_map for fast O(1) access by ID
- Handles insert, update, delete, and query operations

### Function Interface Layer
Connects CLI commands to database logic through a clean API.

---

## Build Instructions

Requirements:
- C++17 or higher
- g++ compiler
- Make

Build:
make

Run:
./program

Clean:
make clean

---

## Project Goals

This project was built to understand:

- How databases store and retrieve data efficiently
- How command-line interfaces process and execute commands
- How hash maps behave under heavy load
- How to structure a modular C++ project

---

## Future Improvements

Planned features:

- Persistent storage (save/load database to file)
- SQL-like query syntax (WHERE clauses)
- Indexing for faster queries beyond ID lookup
- Improved parser (support quotes and spaces in strings)
- Performance benchmark for large-scale inserts
- Multi-threaded performance testing

---

## Notes

This is an educational project, not a production database system. It is intended to demonstrate systems programming concepts in C++.
