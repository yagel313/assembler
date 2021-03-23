; file ps.as
.entry
.entry L3
.extern W
MAIN: add r3, LIST1
LOOP: prn 48
lea r3, r0
inc
mov r3, K
sub r1, r4, r6
bne END1
cmp K, #-6.5
bne %LIST
dec W,
.entry MAIN
jmp %LOOP
add L3
add L3,
END: stop
STR: .string "abcd"
LIST: .data 6, -9
.data -100
K: .data 31
.extern L3
