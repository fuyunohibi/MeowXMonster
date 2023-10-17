section .data
seed:   .word 42       @ Initial seed for random number generator

.section .bss
result: .space 4       @ Storage for the random number

section .text
.global reduce_HP
.global score_kill
.global check_price
.global random_number
.global findRow

reduce_HP:
    SUB R0, R0, R1      @ R0 current HP, R1 attack HP
    BX LR

score_kill:
    ADD R0, R0, #1
    BX LR

check_price:
    CMP R0, R1          @ R0 current money, cat price
    BGT return_true
    return_false

return_true:
    MOV R0, #1
    BX LR

return_false:
    MOV R0, #0
    BX LR

random_number:
    @ Load the seed into r0
    ldr r0, =seed

    @ Call the srand function to initialize the random number generator
    bl srand

    @ Call the rand function to generate a random number between 0 and RAND_MAX
    bl rand

    @ Calculate the random number modulo 101 to get a value between 0 and 100
    mov r1, #101      @ 101 is one more than the desired range
    umull r2, r3, r0, r1   @ r2:r3 = r0 * r1
    lsr r2, r2, #31   @ r2 = r2 >> 31 (get the remainder)

    @ Store the result in memory
    str r0, [result]

    BX LR

findRow:
    ; Function prologue
    push {r1, lr}   ; Save r1 and link register (lr) on the stack
    mov r1, r0      ; Copy the value of r0 (i) to r1

    ; Compare i with 2
    cmp r1, #2
    ble done  ; Branch to done if i <= 2

loop:
    ; Subtract 3 from i
    sub r1, r1, #3
    ; Compare i with 2 again
    cmp r1, #2
    bgt loop  ; If i > 2, continue looping

done:
    ; Function epilogue
    pop {r1, pc}  ; Restore r1 and return by branching to the link register (lr)






 




    
