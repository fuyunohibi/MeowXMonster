.data

.text
; .global main
.global reduce_HP
.global score_kill
.global check_price

reduce_HP:
    SUB R0, R0, R1      ;R0 current HP, R1 attack HP
    BX LR

score_kill:
    ADD R0, R0, #1
    BX LR

check_price:
    CMP R0, R1          ;R0 current money, cat price
    BGT return_true
    return_false

return_true:
    MOV R0, #1
    BX LR

return_false:
    MOV R0, #0
    BX LR






 




    
