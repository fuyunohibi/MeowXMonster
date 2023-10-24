.data
    seed:   .word 42   
    @ name
    @ price
    @ HP
    @ isalive
    @ attack damage
    @ attack per second
    @ right boundary
    @ attack timer
    laika_array:    .double 1.0
                    .double 100.0
                    .double 150000.0
                    .double 1.0
                    .double 50000.0
                    .double 0.5
                    .double 180.0
                    .double 0.0

    fartcat_array:  .double 2.0
                    .double 250.0
                    .double 300000.0
                    .double 1.0
                    .double 150.0
                    .double 0.05
                    .double 0.0
                    .double 0.0

    megachonker_array:   .double 3.0
                        .double 200.0
                        .double 400000.0
                        .double 1.0
                        .double 0.0
                        .double 0.0
                        .double 180.0
                        .double 0.0

    bomb_array:     .double 4.0
                    .double 400.0
                    .double 1.0
                    .double 1.0
                    .double 500000.0
                    .double 0.0
                    .double 180.0
                    .double 0.0

    monster_array:  .skip 120
.bss
    result: .space 4

.text
    .global add_function
    .global calculate_center
    .global random_number
    .global findRow
    .global loop
    .global end_loop
    .global laika
    .global fartcat
    .global megachonker
    .global bomb
    .global create_character

add_function:
    add r0, r0, r1 
    bx lr

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
    // Function prologue
    push {lr}

    // Initialize the loop variable
    mov r1, r0

loop:
    // Check if i > 2
    cmp r1, #2
    ble end_loop

    // Subtract 3 from i
    sub r1, r1, #3
    b loop

end_loop:
    // Return the final value of i
    mov r0, r1

    // Function epilogue
    pop {pc}



laika:
    ldr r0, =laika_array
    bx lr

fartcat:
    ldr r0, =fartcat_array
    bx lr

megachonker:
    ldr r0, =megachonker_array
    bx lr

bomb:
    ldr r0, =bomb_array
    bx lr

create_character:
    cmp r0, #1
    beq laika

    cmp r0, #2
    beq fartcat

    cmp r0, #3
    beq megachonker

    cmp r0, #4
    beq bomb


