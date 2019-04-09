#!/bin/bash

C_FILE=$(tree -f  src | egrep -o '[/a-zA-Z0-9]{1,}\.c$' | tr "\n" " ")

echo $C_FILE

# -g gdb   -lcurses ncurses 库
`gcc -g $C_FILE  -lcurses -lm -o bin/snake`
