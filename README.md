# Brainf-ck
This is a `BRAINF-CK LANGUAGE INTERPRETER` written on c++.Brainfuck is a minimalist language made by Urban Müller in 1993 just for fun and challenging coders.

## SYNTAX
BRAINF-CK LANGUAGE has `EIGHT SYMBOLS` in total:

| SYMBOL | ACTION        |
|:------:|:--------------:| 
| `>`  | Increment the data pointer (to point to the next cell to the right).
| `<`    | Decrement the data pointer (to point to the next cell to the left).
| `+`    | Increment (increase by one) the byte at the data pointer.
| `-`    | Decrement (decrease by one) the byte at the data pointer.
| `.`    | Output the byte data pointer pointing at
| `,`    | Accept one byte of input, Store its value in the pointing byte.
| `[`    | If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
| `]`    | If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.

> The file reader ignores everything after # in a line. It is not a brainfuck directive. Simply they are not passed to the interpreter. So you can write comments after #.
## Output Mode
The default output mode of this interpreter is __Memory Format__. In memory format output is printed as follows:
```MEM[12] = 65```
You can change the output mode via a directive using $.Put $ and write the mode name after it. Only writting first letter of the mode also works. All output modes supported yet are 
| Output Type   | Command        | Demo Output  |
| :------------ |:-------------- | :-----------:|
| MEMORY TYPE*  | $M or $MEMORY  | MEM[2] = 65  |
| DECIMAL       | $D or $DECIMAL |      65      |
| ASCII         | $A or $ASCII   |       A      |

\* - is the default output mode

## How to run brainfuck codes
- From terminal:</br>
  - Write `$ g++ brainfuck.cpp -o brainfuck` once to compile the brainfuck interpreter.
  - Write `$ ./brainfuck filename.bf` to interpret the filename.bf brainf-ck code.
  - or Write `$ ./brainfuck` only after that type your code in the terminal output.

## Examples
# Hello World
`$ g++ brainfuck.c -o brainfuck`</br>
`$ ./brainfuck hello.bf`
```
$ASCII
#  Source : Wikipedia
#  This program prints "Hello World!" and a newline to the screen, its
#  length is 106 active command characters. [It is not the shortest.]
#
#  This loop is an "initial comment loop", a simple way of adding a comment
#  to a BF program such that you don't have to worry about any command
#  characters. Any ".", ",", "+", "-", "<" and ">" characters are simply
#  ignored, the "[" and "]" characters just have to be balanced. This
#  loop and the commands it contains are ignored because the current cell
#  defaults to a value of 0; the 0 value causes this loop to be skipped.
++++++++                # Set Cell #0 to 8
[
    >++++               # Add 4 to Cell #1; this will always set Cell #1 to 4
    [                   # as the cell will be cleared by the loop
        >++             # Add 2 to Cell #2
        >+++            # Add 3 to Cell #3
        >+++            # Add 3 to Cell #4
        >+              # Add 1 to Cell #5
        <<<<-           # Decrement the loop counter in Cell #1
    ]                   # Loop until Cell #1 is zero; number of iterations is 4
    >+                  # Add 1 to Cell #2
    >+                  # Add 1 to Cell #3
    >-                  # Subtract 1 from Cell #4
    >>+                 # Add 1 to Cell #6
    [<]                 # Move back to the first zero cell you find; this will
                        # be Cell #1 which was cleared by the previous loop
    <-                  # Decrement the loop Counter in Cell #0
]                       # Loop until Cell #0 is zero; number of iterations is 8
The result of this is:
Cell no :   0   1   2   3   4   5   6
Contents:   0   0  72 104  88  32   8
Pointer :   ^
>>.                     # Cell #2 has value 72 which is 'H'
>---.                   # Subtract 3 from Cell #3 to get 101 which is 'e'
+++++++..+++.           # Likewise for 'llo' from Cell #3
>>.                     # Cell #5 is 32 for the space
<-.                     # Subtract 1 from Cell #4 for 87 to give a 'W'
<.                      # Cell #3 was set to 'o' from the end of 'Hello'
+++.------.--------.    # Cell #3 for 'rl' and 'd'
>>+.                    # Add 1 to Cell #5 gives us an exclamation point
>++.                    # And finally a newline from Cell #6
```
Output: 
```Hello World!```

## `BONUS`:
This interpreter comes with a transpiler which takes a string and outputs a brainf-ck code which prints the givern string.
