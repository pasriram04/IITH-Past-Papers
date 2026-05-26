# Advanced C Programming Notes

This document summarizes advanced features, trivia, and nitty-gritty details from the provided C programming lecture slides, skipping basic concepts.

## 1. Strings

While the basics of C strings are straightforward, here are some noteworthy details:

*   **`char *p` vs. `char a[]`**:
    *   `char a[] = "hello";` creates a mutable array on the stack, initialized with "hello". You can change its contents (e.g., `a[0] = 'H';`).
    *   `char *p = "hello";` creates a pointer to a *string literal*, which is typically stored in a read-only section of memory. Attempting to modify it (e.g., `p[0] = 'H';`) results in undefined behavior, often a segmentation fault.

*   **`strncpy()` Pitfall**:
    *   The `strncpy(dest, src, n)` function is a common source of bugs.
    *   **Case 1**: If `strlen(src) < n`, it copies the string and pads the rest of `dest` with null bytes up to `n` characters.
    *   **Case 2 (The Pitfall)**: If `strlen(src) >= n`, it copies exactly `n` characters but **does not** null-terminate the destination string. You must manually add the null terminator: `dest[n-1] = '\0';` (if you have space) or `dest[n] = '\0';` if your buffer is size `n+1`.

*   **In-Memory Formatting**:
    *   `sprintf(char *str, ...)`: Prints formatted data to a string instead of the console. Useful for building strings dynamically.
    *   `sscanf(const char *str, ...)`: Reads formatted data from a string instead of the console. Useful for parsing strings.

## 2. Structures, Unions, and Enums

### Structures (`struct`)

*   **Memory Alignment and Padding**:
    *   Struct members are not always stored in consecutive memory locations. Compilers often add "holes" or **padding** between members to align them on specific memory boundaries (e.g., aligning a 4-byte `int` on a 4-byte boundary).
    *   This improves CPU access speed but means `sizeof(struct)` can be greater than the sum of the sizes of its members.
    *   **Trivia**: Because of this padding, you cannot reliably compare two structs using `memcmp()` if you only care about the member values, as the padding bytes can contain garbage.

*   **Direct Comparison (`==`)**:
    *   You **cannot** compare two structs directly using the `==` operator (e.g., `if (struct1 == struct2)`). This is because it's unclear what the comparison should mean (member-wise equality? pointer equality?). You must compare them member by member.

*   **Self-Referential Structures**:
    *   A `struct` cannot contain an instance of itself (e.g., `struct list { int data; struct list node; };` is illegal because the size would be infinite).
    *   However, it **can** contain a *pointer* to itself, which is the foundation of data structures like linked lists and trees:
        ```c
        struct list_node {
            int data;
            struct list_node *next; // Pointer to the same struct type
        };
        ```

### Unions

*   **Shared Memory**: Unlike structs, all members of a `union` share the **same memory space**. The size of the union is the size of its largest member.
*   **One Member at a Time**: You can only store a value in one member at a time. If you assign a value to a new member, the old member's value is overwritten and may be interpreted as garbage if read.
    ```c
    union Number {
        int x;
        double y;
    };
    union Number n;
    n.y = 100.0;
    // At this point, n.x contains garbage because the memory holds a double.
    printf("int: %d, double: %f\n", n.x, n.y);
    ```

### Bit-Fields

*   For situations requiring memory conservation (e.g., embedded systems), you can define struct members with a specific number of bits.
*   This allows packing data tightly. The members must be of type `int` or `unsigned int`.
    ```c
    struct BitCard {
        unsigned int face : 4; // 4 bits (0-15)
        unsigned int suit : 2; // 2 bits (0-3)
        unsigned int color: 1; // 1 bit (0-1)
    };
    // The total size is implementation-defined but packs these
    // 7 bits efficiently.
    ```
*   **Limitation**: You cannot take the address (`&`) of a bit-field member.

## 3. Bitwise Operations

Bitwise operators are used for low-level manipulation of bits within integral types. They are often faster than standard arithmetic.

*   **Operators**: `&` (AND), `|` (OR), `^` (XOR), `~` (NOT), `<<` (left shift), `>>` (right shift).
*   **Common Use Cases**:
    *   **Set a bit**: `number |= (1 << n);` (Sets the nth bit)
    *   **Clear a bit**: `number &= ~(1 << n);` (Clears the nth bit)
    *   **Toggle a bit**: `number ^= (1 << n);` (Toggles the nth bit)
    *   **Check a bit**: `if (number & (1 << n))` (Checks if the nth bit is set)
*   **Performance Trivia**:
    *   **Even/Odd Check**: `(num & 1)` is a fast way to check for oddness. If it's 1, the number is odd.
    *   **Multiply/Divide by 2**: `x << 1` is equivalent to `x * 2`. `x >> 1` is equivalent to `x / 2` for non-negative integers.
*   **Right Shift Behavior**: The behavior of right-shifting (`>>`) a *signed* negative number is implementation-defined. It might perform an *arithmetic shift* (preserving the sign bit) or a *logical shift* (filling with zeros). Use `unsigned` integers for predictable bitwise operations.

## 4. File Processing

*   **`FILE` Pointer, Descriptors, and FCBs**:
    *   When you `fopen()`, you get a `FILE *`. This is a pointer to a struct that acts as a high-level abstraction for the file stream.
    *   This `FILE` struct contains a **file descriptor** (a small integer, e.g., 3, 4, 5...), which is an index into the OS's per-process table of open files.
    *   The OS uses this descriptor to find the **File Control Block (FCB)**, which holds the low-level details about the file (e.g., permissions, disk location). Your program does not directly access the FCB.

*   **Sequential vs. Random Access**:
    *   **Sequential**: The default mode. You read/write data in order, from beginning to end.
    *   **Random Access**: Allows you to jump to any location in a file to read or write. This is only practical with fixed-length records.

*   **Text vs. Binary Mode**:
    *   **Text Mode (`"w"`, `"r"`)**: The library may perform character translations (e.g., converting `\n` to `\r\n` on Windows).
    *   **Binary Mode (`"wb"`, `"rb"`)**: No translations are performed. Every byte is read/written as-is. This is **essential** for random access and non-text data.

*   **Functions for Random Access**:
    *   `fseek(file_ptr, offset, origin)`: Moves the file position pointer.
        *   `origin`: `SEEK_SET` (from start), `SEEK_CUR` (from current position), `SEEK_END` (from end).
    *   `ftell(file_ptr)`: Returns the current byte offset of the file position pointer.
    *   `rewind(file_ptr)`: Resets the file position pointer to the beginning (equivalent to `fseek(ptr, 0, SEEK_SET)`).

*   **`fwrite` and `fread`**:
    *   These functions perform unformatted I/O, writing raw bytes from memory to a file.
    *   This is the standard way to work with random-access files, as it ensures that a `struct` written to a file has a consistent, fixed size, making it possible to calculate offsets.
        ```c
        // To write a record
        fwrite(&myRecord, sizeof(struct clientData), 1, fptr);
        // To jump to the Nth record
        fseek(fptr, (N - 1) * sizeof(struct clientData), SEEK_SET);
        ```

## 5. The C Preprocessor

The preprocessor runs before the compiler, performing text-based substitutions and operations.

*   **`#include <...>` vs. `#include "..."`**:
    *   `<filename>`: Searches in standard system directories only. Used for standard library headers.
    *   `"filename"`: Searches in the current directory first, *then* in standard system directories. Used for your own project's header files.

*   **Macro Pitfalls**:
    *   Macros are simple text replacements, which can violate operator precedence.
    *   **Rule of Thumb**: Always enclose the entire macro definition in parentheses, and enclose every macro argument in parentheses.
        ```c
        // Bad:
        #define CIRCLE_AREA(x) 3.14 * x * x
        // CIRCLE_AREA(c + 2) becomes 3.14 * c + 2 * c + 2, which is wrong.

        // Good:
        #define CIRCLE_AREA(x) (3.14 * (x) * (x))
        ```

*   **Conditional Compilation**:
    *   Allows you to include or exclude code blocks based on preprocessor conditions.
    *   `#ifdef DEBUG`: A common pattern to include debugging code (like `printf` statements) that can be turned off in the final build by not defining `DEBUG`.
    *   `#if defined(WINDOWS) ... #elif defined(LINUX) ... #endif`: Used for platform-specific code.

*   **`#` and `##` Operators**:
    *   `#` (Stringizing Operator): Converts a macro argument into a string literal.
        ```c
        #define PRINT_VAR(x) printf(#x " = %d\n", x)
        // PRINT_VAR(my_var); becomes printf("my_var" " = %d\n", my_var);
        ```
    *   `##` (Token-Pasting Operator): Concatenates two tokens into a single token.
        ```c
        #define CMD(name) cmd_##name
        // void CMD(new)(); becomes void cmd_new();
        ```

*   **Predefined Constants**:
    *   `__FILE__`: The name of the current source file (a string).
    *   `__LINE__`: The current line number (an integer).
    *   `__DATE__`: The compilation date (a string).
    *   `__TIME__`: The compilation time (a string).
    *   `__STDC__`: `1` if the compiler conforms to the C standard.

*   **`assert` Macro**:
    *   `assert(expression)` is a debugging aid defined in `<assert.h>`.
    *   If `expression` is false (0), it prints an error message (including the file and line number) to `stderr` and terminates the program by calling `abort()`.
    *   **Disabling Asserts**: If you `#define NDEBUG` *before* including `<assert.h>`, all `assert` calls in that file will be compiled into nothing, effectively removing them from the release build.
