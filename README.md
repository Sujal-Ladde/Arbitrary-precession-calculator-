# Arbitrary Precision Calculator

This project is a C-based command-line calculator that can perform arithmetic operations (addition, subtraction, multiplication, and division) on integers of arbitrary size. It overcomes the limitations of standard integer types by using a doubly linked list to store and manipulate numbers, allowing for calculations involving very large integers.

## Features

* **Arbitrary Precision:** Handles integers far larger than standard C data types like `int` or `long long`.
* **Basic Arithmetic Operations:**
    * Addition (`+`)
    * Subtraction (`-`)
    * Multiplication (`x`)
    * Integer Division (`/`)
* **Negative Number Support:** Correctly handles operations with both positive and negative integers.
* **Command-Line Interface:** Easy to use directly from the terminal.

## Data Structure

The core of this calculator is a **Doubly Linked List (DLL)**. Each node in the list stores a single digit of a number. This structure is ideal for arbitrary-precision arithmetic for several reasons:

* **Dynamic Size:** The list can grow to accommodate any number of digits.
* **Efficient Traversal:** The doubly linked nature allows for traversal from both the most significant digit (head) and the least significant digit (tail), which is crucial for arithmetic operations.

The structure of a node is defined as:

```c
typedef struct DLL {
    int data;
    struct DLL *previous_node;
    struct DLL *next_node;
} DLL;
```

Algorithms

The arithmetic operations are implemented to mimic the manual, grade-school methods of calculation, but adapted for the doubly linked list data structure.
Addition (addition)

Addition starts from the least significant digit (tail of the list) and moves towards the most significant digit (head).

    Initialize carry to 0.
    Traverse both number lists from tail to head.
    At each position, calculate sum = digit1 + digit2 + carry.
    The new digit for the result is sum % 10.
    The new carry is sum / 10.
    Insert the new digit at the beginning of the result list.
    Continue until both lists are traversed and the carry is 0.

Subtraction (subtraction)

Subtraction also starts from the least significant digit. The logic assumes the first operand is greater than or equal to the second.

    Initialize borrow to 0.
    Traverse both lists from tail to head.
    Calculate diff = (digit1 - borrow) - digit2.
    If diff is negative, add 10 to it and set borrow to 1 for the next iteration. Otherwise, borrow is 0.
    Insert the diff at the beginning of the result list.
    Continue until the first list is fully traversed.
    Remove any leading zeros from the result.

Multiplication (multiplication)

Multiplication is performed by multiplying each digit of the second number with the entire first number and then adding the intermediate results.

    Initialize a total_result list to 0.
    Iterate through the second number from tail to head (digit by digit).
    For each digit, multiply it with the first number to get a partial_result.
        This inner loop is similar to addition, handling carries.
    Add appropriate trailing zeros (shifting) to the partial_result based on its position in the second number.
    Add the partial_result to the total_result using the addition function.
    Repeat for all digits of the second number.

Division (division)

Integer division is implemented using a long-division approach.

    Handle edge cases: division by zero and dividend being smaller than the divisor.
    Create a current_dividend list, initially empty.
    Iterate through the digits of the main dividend from head to tail.
    "Bring down" one digit at a time to the current_dividend.
    Repeatedly subtract the divisor from the current_dividend until it is smaller than the divisor, counting the number of successful subtractions.
    This count is the next digit of the quotient. Append it to the quotient list.
    Repeat until all digits of the main dividend have been processed.
    Remove any leading zeros from the final quotient.


File Descriptions

    main.c: The entry point of the program. It handles command-line argument parsing, determines which operation to perform based on signs and the operator, and calls the appropriate arithmetic function.
    DLL.c: Contains the implementation of the doubly linked list functions, including insertion, deletion, printing, and comparison of numbers stored in the lists.
    ADD.c: Implements the addition function for adding two large numbers.
    SUB.c: Implements the subtraction function.
    MUL.c: Implements the multiplication function.
    DIV.c: Implements the division function.
    
    *.h: Header files containing the function prototypes and necessary includes for their respective C files.

How to Compile and Run
Compilation

You can compile the project using the makefile present in the project.
```
make clean 
make 
```
Execution

Run the compiled executable from your terminal, providing two numbers and an operator as command-line arguments.
```
./arbitrary_precision_calculator <operand1> <operator> <operand2>
```
Usage Examples
Addition
```
./arbitrary_precision_calculator 98765432109876543210 + 12345678901234567890
Result: 111111111011111111100
```
Subtraction with Negative Result
```
./arbitrary_precision_calculator 100 - 200
Result: -100
```
Multiplication
```
./arbitrary_precision_calculator 123456789 x 987654321
Result: 121932631112635269
```
Division
```
./arbitrary_precision_calculator 11111111111111111111 / 123456789
Result: 900000018
```

Author
Sujal Ladde • laddesujal273@gmail.com 
