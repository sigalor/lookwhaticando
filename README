# Prerequisites
You need the Boost C++ library to compile the source. Adjust the include directory in the Makefile accordingly (or remove the -I directive when the Boost include files are in the standard include path).
I tested the source on Linux and Windows, it should work on both (although there may be some warnings about the `%lu` format specifier for `printf` when using 32 instead of 64 bit.

# Syntax
The program's term syntax is the following (the symbols are sorted by their priority):
1. `!` for `NOT`
2. `&` for `AND`
3. `|` for `OR`

These symbols can be adjusted in the beginning of the program's source code. Only single characters are allowed.
Additionally, you may use round brackets normally as well.
When you're using BASH, you have to escape all of these characters, because they otherwise have a special meaning.

# Examples
- `(A&!B)|(!A&B)`: the XOR table
- `!A|B`: the table for logical implication
- `!A|B&(C|!(D|!B))`: some weird expression with four variables

# Meta information
Original date of creation: 03.01.2015
Topics: simple parsing, logical evaluation
