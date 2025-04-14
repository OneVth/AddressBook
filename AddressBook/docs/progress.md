# Address Book Project Progress Summary

## Project Overview
- **Language**: C (planning to port to C++ later)
- **Description**: A command-line address book program for managing contact info. Supports insert/search/edit/delete and file I/O.

## Current Architecture and Features
- **Data Type**: `Contact` (fields: age, name, phone)
- **File Format**: Binary `.dat` file using fixed-size records
- **Data Structure**: `ContactStore` implemented using **Red-Black Tree (RBT)**
- **Features**:
  - Insert, delete, update, search for contacts
  - File read/write operations (with format validation)
  - Logical search using `AND`/`OR` syntax
  - Console UI for interaction
  - Complete unit test suite in `test.c`
  - Benchmarking via `benchmark.c` and `.md` result logging

## Completed Milestones
- ✅ Fully removed old linked list-based `ContactStore`
- ✅ Refactored UI to interact with RBT version
- ✅ Updated `AddressGenerator` to generate into RBT structure
- ✅ Implemented and passed all feature tests
- ✅ Benchmarked and compared performance (RBT vs List)
- ✅ Analyzed and visualized benchmark results externally using linear and log scale graphs

## Benchmark Summary
- Benchmark measured time to insert *N* contacts into `ContactStore` and save them to a binary file
- Tested from 1,000 to 100,000 nodes
- RBT version showed **up to 17x speedup** over List in search/load
- Performance grows logarithmically with input size

### Load Time Comparison (Linear Scale)
![output](https://github.com/user-attachments/assets/58f85eed-c4e5-45c0-9b74-48f3924d2750)

### Load Time Comparison (Log Scale)
![output_log_scale](https://github.com/user-attachments/assets/1ea315ea-da47-4d9c-8989-00cccb468a80)

## Next Steps

### 1. Multithreading Support (C)
- Goal: concurrent search and file I/O
- Strategy:
  - Use Windows threads or `_beginthreadex`
  - Protect shared resources (e.g., `ContactStore`) with synchronization tools
  - Ensure thread safety in insert/delete/search

### 2. Port to C++
- Wrap contact logic in classes (`Contact`, `ContactStore`)
- Use STL (`std::map`, `std::vector`) where appropriate
- Apply C++ best practices: RAII, smart pointers, exceptions

## File Structure

```text
/AddressBook
├── main.c                # Entry point
├── control.c             # Core file I/O and processing logic
├── contact.c             # Contact creation and access
├── contact_store_rbt.c   # RBT-based contact storage
├── ui.c                  # Interactive console UI
├── test.c                # Unit and feature tests
└── benchmark.c           # Dataset generation and performance test
```
