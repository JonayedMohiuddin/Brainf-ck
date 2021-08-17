# Brainf-ck
This is a `BRAINF-CK LANGUAGE INTERPRETER` written on c++.It is a minimalist language made by Urban Müller in 1993 just for fun and challenging coders.

## SYNTAX
BRAINF-CK LANGUAGE has `EIGHT SYMBOLS` in total:

- `>` Increment the data pointer (to point to the next cell to the right).
- `<`	Decrement the data pointer (to point to the next cell to the left).
- `+`	Increment (increase by one) the byte at the data pointer.
- `-`	Decrement (decrease by one) the byte at the data pointer.
- `.`	Output the byte data pointer pointing at
- `,`	Accept one byte of input, Store its value in the pointing byte.
- `[`	If the byte at the data pointer is zero, then instead of moving the instruction pointer forward to the next command, jump it forward to the command after the matching ] command.
- `]`	If the byte at the data pointer is nonzero, then instead of moving the instruction pointer forward to the next command, jump it back to the command after the matching [ command.
