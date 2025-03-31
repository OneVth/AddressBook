## Program Structure Overview

This document summarizes the structure and responsibilities of each file in the Address Book project. It is intended to help understand the organization of code and guide further development or refactoring.

---

### `main.c`
- Entry point of the program.
- Calls top-level test suites for `List`, `Util`, and `Control` components.

---

### `common.c / common.h`
- **Responsibility**: Utility functions and shared logic not specific to a single module.
- Includes:
  - String validation (`Str_IsAllDigit`, `Str_IsAllAlpha`, etc.)
  - Input parsing (`ClassifyToken`, `SplitSearchExpression`)
  - Helper macros (`NODE_MATCH`, etc.)
- Extensively unit-tested.

---

### `control.c / control.h`
- **Responsibility**: Core file and record handling logic.
- Handles:
  - Loading, editing, deleting records from file
  - Saving list back to file
  - Searching file records by different fields
- Depends on:
  - `List` module for in-memory representation
  - `common.c` for string parsing/validation
- All functions are tested with test data files.

---

### `ui.c / ui.h`
- **Responsibility**: User interaction, input/output handling.
- Primarily deals with:
  - Getting input from the user
  - Printing formatted results
- Not unit-tested directly (user interface layer).

---

### `test.c / test.h`
- **Responsibility**: All unit tests for logic functions.
- Organized into groups:
  - List-related tests
  - Utility function tests
  - File control function tests
- Helper functions:
  - `CreateTestDataFile_Minimal`
  - Assertions and validation helpers

---

### `common.h`
- Defines `NODE` and `LIST` structures.
- Central header shared across all components.

---

### Notes:
- The program avoids global variables.
- Clear separation of concerns: UI, logic, file handling.
- `test.c` covers nearly all non-UI functionality.

---

### Next Steps
- Consider using `Makefile` for automated builds
- Add integration tests for complete workflows
- Document UI interaction flow (optionally)
- Evaluate need for modularity if ported to C++ or C#

---

_Last updated: 3/31/2025_

