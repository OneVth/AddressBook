# AddressBook (C-based Console Contact Manager)

A simple console-based contact management program written in C.  
It supports operations like inserting, searching, editing, and deleting contact records, using a Red-Black Tree as the underlying data structure for efficient lookup.  
Multithreading has been introduced to improve user experience and responsiveness.

---

## 📌 Features

- Add new contacts
- Search by single or multiple conditions (supports AND / OR)
- Delete contacts by phone number
- Edit contact info (age, name, phone number)
- Save and load contacts to/from a file

---

## 🧱 Project Structure

```
AddressBook/
├── main.c # Program entry point
├── ui.c / ui.h # User interface logic
├── contact.c / contact.h # Contact struct and related functions
├── contact_store.c / .h # Red-Black Tree-based ContactStore implementation
├── contact_store_internal.h # Internal structures for RBT nodes
├── control.c / control.h # File I/O and record operations
├── benchmark.c # Benchmarking and performance analysis
└── test.h # Unit test declarations
```

---

## 🧠 Data Structures

- **Contact**  
  A structure holding age, name, and phone number.

- **ContactStore (Red-Black Tree)**  
  Stores all contact entries using a balanced Red-Black Tree to support fast search, insert, and delete operations.

---

## ⚙️ Multithreading Integration

To improve UI responsiveness, selected UI functions have been updated to perform time-consuming I/O tasks in background threads.

### ✅ Affected Functions

| Function         | Description                                  |
|------------------|----------------------------------------------|
| `UI_InsertNode`  | Saves to file on a background thread         |
| `UI_DeleteNode`  | Deletes with animated progress feedback      |
| `UI_Search`      | Performs threaded search with live animation |

### 🔧 Threading APIs Used

- `_beginthreadex`, `WaitForSingleObject`, `CloseHandle`
- Console animation like `"Saving..."`, `"Deleting..."`, `"Searching..."` shown during operations

---

## 📂 File Format

- **Text-based file storage**
  - Each contact record is stored in a separate line
  - Save path is passed as a flexible `path` argument

---

## 🚧 Planned Improvements

- Full rewrite in modern C++ (AddressBook_Cpp)
- Class-based design for `Contact`, `ContactStore`
- Smart pointer usage and RAII patterns
- Unit test framework integration
- STL-based containers for data storage
