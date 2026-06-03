# C++ Data Structures Practice

This repository is a personal playground dedicated to implementing, practicing, and mastering core data structures in C++17. Every structure is built from scratch with clean code, comprehensive memory management (Rule of Three), template-based generic programming, and a custom testing suite.

---

## 📂 Repository Structure

The project is organized into self-contained modules, each focusing on a specific data structure:

| Folder | Data Structure | Type | Key Details / Features |
| :--- | :--- | :--- | :--- |
| [`01_DynamicArray`](file:///Users/cboris/Downloads/cpp-data-structures-practice/01_DynamicArray) | Dynamic Array (Vector) | `int` | Amortized $O(1)$ push back, geometric resizing, deep copy support. |
| [`02_LinkedList`](file:///Users/cboris/Downloads/cpp-data-structures-practice/02_LinkedList) | Singly & Doubly Linked List | Template | Node-based dynamic allocation, pointer manipulation, $O(1)$ head/tail operations. |
| [`03_Stack`](file:///Users/cboris/Downloads/cpp-data-structures-practice/03_Stack) | Stack (LIFO) | Template | Linked-node implementation, copy-and-swap resource protection. |
| [`04_Queue`](file:///Users/cboris/Downloads/cpp-data-structures-practice/04_Queue) | Queue (FIFO) | Template | Circular array or linked node structure. |
| [`05_Deque`](file:///Users/cboris/Downloads/cpp-data-structures-practice/05_Deque) | Double-Ended Queue | Template | Support for push/pop from both ends. |
| [`06_BinarySearchTree`](file:///Users/cboris/Downloads/cpp-data-structures-practice/06_BinarySearchTree) | Binary Search Tree (BST) | Template | Recursive insertion, searching, 3-case deletion, and pre/in/post-order traversals. |

---

## 🛠️ Design & Implementation Best Practices

Each data structure implementation adheres to rigorous programming guidelines:

* **Resource Management (Rule of Three)**: Clean destructors, deep-copy constructor implementations, and copy assignment operators utilizing the **Copy-and-Swap** idiom to guarantee strong exception safety.
* **Generics (Templates)**: Implementation of `template <typename T>` to allow the structures to work with arbitrary data types.
* **Robust Error Handling**: Out-of-bounds checks, empty container checks, and proper use of standard exception types (e.g., `std::out_of_range`).
* **Custom Testing Framework**: Utilizes a lightweight, macro-based testing framework ([`TestFramework.h`](file:///Users/cboris/Downloads/cpp-data-structures-practice/TestFramework.h)) providing test reporting, comparison checks (`TEST_EQUAL`), and exception assertions (`TEST_EXCEPTION`).

---

## 🚀 How to Build and Run Tests

Each module directory contains a `Makefile` linked to a global config [`common.mk`](file:///Users/cboris/Downloads/cpp-data-structures-practice/common.mk).

### Prerequisites
* **Compiler**: A C++ compiler supporting **C++17** (GCC 7+ or Clang 5+).
* **Build System**: `make`

### Building Locally

Navigate to the directory of the data structure you wish to test, build it, and run the generated executable:

```bash
# Navigate to the target folder
cd 01_DynamicArray

# Build the test executable
make

# Run the test suite
./dynamic_array_test
```

To clean compile targets:
```bash
make clean
```

### Running with Docker (Alternative for restricted environments)

If you are running on an environment with strict security policies (e.g., company computer blocking local unsigned binaries), you can run a Docker container containing a GCC build environment to compile and execute:

```bash
# Launch a GCC container with current directory mounted
docker run --rm -it -v "$(pwd)":/workspace -w /workspace gcc:latest bash

# Inside the container, compile and run
cd 06_BinarySearchTree
make clean && make
./bst_test
```
