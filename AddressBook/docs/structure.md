# Address Book Project Progress Summary

## Project Overview
- Language: C (planning to port to C++ later)
- Description: A command-line based address book program that saves contact info to a file and supports insertion/search/edit/delete

## Current Architecture and Features
- Data Type: Contact (includes age, name, phone)
- File Format: Binary file using direct access
- Data Structure: ContactStore (currently implemented as a doubly linked list; will be replaced with Red-Black Tree)

## Completed Core Features
- Insert / Delete / Search / Update contacts
- File I/O using binary format
- UI interface for interactive input/output (UI layer)
- Unit test suite provided ('test.c')
- Benchmarks and performance measurement using `benchmark.c`
- Logs and `.md` table output for performance data

## ADT Transition Status
- Removed all `LIST`, `NODE` structures and functions
- All features now use `ContactStore`-based ADT
- UI now fully migrated to use `ContactStore`

## Next Goals
1. Replace `ContactStore` implementation with a Red-Black Tree
    - Redesign data structure and all relevant logic
    - Implement insert, delete, search, rotation, rebalancing
    - Tree-based output and search logic
2. Keep current interfaces
    - Keep using functions like `ContactStore_AddToEnd`, `TryAddContact`, etc.
    - Minimal change to UI, test and benchmark code
3. Learn and experiment with Red-Black Tree
    - Resources: CLRS, Wikipedia, Visualgo
4. Multithreading
    - Goal: Efficient file I/O, concurrent search/write
    - Consider lock-based or lock-free structure
5. Port to C++
    - Abstracted structure
    - STL-based implementation (e.g. `map`, `set`)
    
## File Structure (Partial)
- /AddressBook
    - main.c		// entry point
    - control.c      // main logic
    - contact.c      // contact-related functions
    - contact_store.c // store-related logic (currently linked list → planned RBT)
    - ui.c           // user interface
    - test.c         // test functions
    - benchmark.c    // performance measurement
    - result.md      // benchmark result output

## Suggested Work Plan
1. Design new RBT data structure (`RBNode`, `RBTree`)
2. Implement all core operations
3. Replace `ContactStore_AddToEnd` with tree insert
4. Apply changes to UI
5. Measure and compare tree performance with existing list
