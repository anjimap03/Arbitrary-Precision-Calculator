# Arbitrary-Precision-Calculator
Arbitrary Precision Calculator in C for performing arithmetic operations on very large numbers beyond standard data type limits.

The Arbitrary Precision Calculator (APC) is a C-based application designed to perform arithmetic operations on numbers that exceed the limits of standard C data types. The project uses custom data structures to represent and manipulate large integers, enabling accurate computation of extremely large values.

This project demonstrates advanced C programming concepts such as dynamic memory management, linked lists, data structures, and algorithm design.

## Features

* Addition of large integers
* Subtraction of large integers
* Multiplication of large integers
* Division of large integers
* Handles numbers of arbitrary length
* Efficient digit-by-digit arithmetic operations
* Command-line based implementation

## Technologies Used

* C Programming
* Linked Lists
* Dynamic Memory Allocation
* Data Structures
* Pointer Manipulation

## Project Structure

main.c      - Program execution and user interface
apc.c       - Arithmetic operation implementations
apc.h       - Function declarations and data structures

## How It Works

* Large numbers are stored using linked lists.
* Each node stores a single digit of the number.
* Arithmetic operations are performed digit by digit, similar to manual calculations.
* Results are generated without being limited by built-in integer data types.

## Compilation

gcc *.c -o apc

## Execution

./apc

## Learning Outcomes

* Understanding arbitrary precision arithmetic
* Implementation of linked lists in real-world applications
* Dynamic memory management
* Pointer operations and data manipulation
* Development of efficient algorithms for large-number computations

## Future Enhancements

* Support for negative numbers
* Floating-point arbitrary precision arithmetic
* Exponentiation and modulo operations
* Expression evaluation with multiple operators
* Improved user interface
