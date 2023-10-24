.data
    seed:   .word 42 
.bss
    result: .space 4

.text
    .global calculate_center
    .global random_number
    .global findRow
    .global loop
    .global done

calculate_center:
    mov r2, r0  
    sub r2, r2, r1  
    mov r0, r2  
    asr r0, r0, #1

    bx lr

@ random_number:
@     ldr r0, =seed
@     bl srand
@     bl rand
@     mov r1, #101   
@     umull r2, r3, r0, r1 
@     lsr r2, r2, #31   

@     str r0, [result]

@     bx lr

findRow:
    
    cmp r0, #2       
    ble end          

loop:
    sub r0, r0, #3   
    cmp r0, #2       
    bgt loop         


