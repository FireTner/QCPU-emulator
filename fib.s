;fib.s

LIM $1, 0
LIM $2, 1
CND 0

AST $1
ADD $2
RST $1

AST $1
ADD $2
RST $2
JMP 5