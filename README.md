
# Tree Data Structure Visualization and Traversal

**Author:** Sapir Blumshtein  
**Email:** sapirblumshtein@gmail.com  
**ID:** 324246651

## Project Overview

This project implements a general tree data structure in C++ and provides functionalities to add nodes, perform various tree traversals, and visualize the tree using SFML (Simple and Fast Multimedia Library). The tree can handle different types of data, including basic types (like `int`, `double`, `char`), `std::string`, and a custom `Complex` number class.

## Files Description

### 1. main.cpp

This is the main program file. It demonstrates the usage of the tree data structure by creating trees with different data types (`double` and `Complex`), adding nodes, performing various traversals, and visualizing the tree.

### 2. tree.hpp

This file contains the template class `Tree<T>` that implements the tree data structure. The tree supports nodes with a maximum number of children (k-ary trees) and provides iterators for pre-order, in-order, post-order, breadth-first search (BFS), depth-first search (DFS), and heap traversal.

### 3. node.hpp

This file defines the `Node<T>` class, which represents a node in the tree. Each node holds a value and pointers to its children.

### 4. complex.hpp

This file defines the `Complex` class, which represents complex numbers. The class supports basic operations like comparison and streaming output.

### 5. test.cpp

This file contains unit tests for the `Tree` class using the Catch2 testing framework. It tests tree operations for different data types, including integers, strings, doubles, complex numbers, and characters.

## How to Build and Run

### Prerequisites

- SFML library (Simple and Fast Multimedia Library)
- Catch2 testing framework

### Installation

To install SFML on a Debian-based system, run:

```sh
sudo apt-get update
sudo apt-get install libsfml-dev
```

### Building the Project

To build the project, navigate to the project directory and run:

```sh
make
```

### Running the Program

To run the main program, execute:

```sh
./main
```

This will display the tree visualizations and perform the specified traversals.

### Running the Tests

To run the unit tests, execute:

```sh
./test
```

## Code Explanation

### tree.hpp

- **Tree<T> Class:** 
  - **Constructor:** Initializes the tree with a given maximum number of children (`k`).
  - **set_root:** Sets the root node of the tree.
  - **add_child:** Adds a child to a parent node, ensuring the maximum number of children (`k`) is not exceeded.
  - **Iterators:** Provides pre-order, in-order, post-order, BFS, DFS, and heap iterators to traverse the tree.

- **Node<T> Class:**
  - **Constructor:** Initializes a node with a given value.
  - **get_value:** Returns the value of the node.
  - **add_child:** Adds a child node, ensuring the maximum number of children (`k`) is not exceeded.
  - **get_children:** Returns the children of the node.

### complex.hpp

- **Complex Class:**
  - **Constructor:** Initializes a complex number with given real and imaginary parts.
  - **get_real:** Returns the real part of the complex number.
  - **get_imag:** Returns the imaginary part of the complex number.
  - **operator>:** Compares two complex numbers.
  - **operator==:** Checks if two complex numbers are equal.
  - **operator<<:** Streams the complex number to an output stream.

### main.cpp

- **display_tree:** Displays the tree using SFML.
- **print_traversals:** Prints the tree nodes in various traversal orders (pre-order, post-order, in-order, BFS).
- **main:** Demonstrates the creation and traversal of trees with `double` and `Complex` types, and visualizes the trees.

### test.cpp

- **Unit Tests:** Tests the functionality of the `Tree` class for different data types and ensures that tree operations work correctly.

## Contact

For any questions or suggestions, please contact Sapir Blumshtein at [sapirblumshtein@gmail.com](mailto:sapirblumshtein@gmail.com).

---

Feel free to copy this README content into a README.md file in your project directory. This document provides a comprehensive overview and instructions for your project.
