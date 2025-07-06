# Supermarket Invoice Generator

A command-line based invoice generation and management system for supermarkets, developed in C.

## Project Overview

This Supermarket Invoice Generator is a comprehensive system designed for cashiers to create, manage, search, and delete customer invoices. The application features a user-friendly interface with colored text output, typewriter effects, and structured invoice formatting.

## Features

- **Cashier Authentication**: Secure login with ID verification
- **Invoice Generation**: Create detailed customer invoices with multiple items
- **Invoice Management**: View, search, and delete saved invoices
- **Data Persistence**: Store invoice data in binary files
- **User-friendly Interface**: Colored text output and typewriter effects
- **Input Validation**: Comprehensive error handling for all user inputs
- **Time-based Shift Detection**: Automatically detects cashier's shift based on system time

## Technologies Used

- **Language**: C
- **Libraries**:
  - `stdio.h`: Standard input/output operations
  - `string.h`: String manipulation functions
  - `stdlib.h`: Memory allocation, random numbers, etc.
  - `ctype.h`: Character type checking
  - `time.h`: Date and time functions
  - `stdbool.h`: Boolean data type
  - `windows.h`: Windows-specific functions (for console manipulation)
- **Data Storage**: Binary file I/O
- **Build Environment**: GCC compiler

## Programming Concepts Implemented

### Core C Programming Concepts
- **Structured Programming**: Modular code organization with functions
- **Control Structures**: `if-else`, `switch-case`, `while`, `do-while`, `for` loops
- **Data Types**: Primitive types (int, float, char) and derived types
- **Operators**: Arithmetic, relational, logical, and assignment operators
- **Arrays**: Single and multi-dimensional arrays for data storage
- **Pointers**: Memory address manipulation and dynamic memory allocation
- **Functions**: User-defined functions with various parameter passing methods
- **File I/O**: Binary file operations for data persistence

### Advanced Programming Concepts
- **Structures**: Complex data types for organizing related data
- **Nested Structures**: Structures within structures for hierarchical data
- **Dynamic Memory Management**: Allocation and deallocation of memory
- **String Manipulation**: Advanced string handling and validation
- **Error Handling**: Input validation and graceful error recovery
- **Time and Date Processing**: Working with system time functions


## How to Use

1. Compile the program using a C compiler:
   ```
   gcc Project.c -o Project
   ```

2. Run the executable:
   ```
   ./Project
   ```

3. Follow the on-screen instructions:
   - Enter cashier details (ID and name)
   - Choose from available options:
     1. Generate Invoice
     2. Show Previous Invoices
     3. Search Invoice
     4. Delete Invoice
     5. Return to Home Page

## Screenshots

### Main Interface
![Main Interface](Screenshots/Screenshot%202025-07-06%20133505.png)

### Functionalities
![Functionalities](Screenshots/Screenshot%202025-07-06%20133551.png)

### Invoice Manual Creation
![Invoice Manual Creation](Screenshots/Screenshot%202025-07-06%20133811.png)

### Invoice Generation
![Invoice Generation](Screenshots/Screenshot%202025-07-06%20134046.png)


## Author

[Syed Fawwad Ahmed]

## Acknowledgements

This project was developed as part of the "Fundamentals of Computer Programming" course.