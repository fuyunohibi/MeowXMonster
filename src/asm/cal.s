.data
    total_score: .word 0 
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
                    .double 37500.0
                    .double 0.45
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

    jelly_array:    .double 1.0
                    .double 25.0
                    .double 150000.0
                    .double 1.0
                    .double 80.0
                    .double 0.0
                    .double 60.0

    ufo_array:      .double 2.0
                    .double 50.0
                    .double 250000.0
                    .double 1.0
                    .double 120.0
                    .double 0.0
                    .double 5.5

    muscle_array:   .double 3.0
                    .double 80.0
                    .double 500000.0
                    .double 1.0
                    .double 150.0
                    .double 0.0
                    .double 5.0

    longleg_array:  .double 4.0
                    .double 120.0
                    .double 600000.0
                    .double 1.0
                    .double 200.0
                    .double 0.0
                    .double 4.5

.bss
    result: .space 4

.text
    .global add_function
    .global calculate_center
    .global random_number
    .global set_total_score
    .global get_total_score
    .global findRow
    .global loop
    .global end_loop
    .global laika
    .global fartcat
    .global megachonker
    .global bomb
    .global create_character
    .global create_monster
    .global jelly
    .global ufo
    .global muscle
    .global longleg

add_function:
    add r0, r0, r1 
    bx lr

set_total_score:
    ldr r1, =total_score
    str r0, [r1]
    bx lr

get_total_score:
    ldr r0, =total_score
    ldr r0, [r0]  
    bx lr

calculate_center:
    mov r2, r0  
    sub r2, r2, r1  
    mov r0, r2  
    asr r0, r0, #1

    bx lr

random_number:
    @ Inputs:
    @ r0: Dividend (n)
    @ r1: Divisor
    @ Outputs:
    @ r0: Remainder (result of n % divisor)

    add r1, r1, #1
    udiv r2, r0, r1      @ r0 = r0 / r1 (unsigned division)
    mul r3, r2, r1      @ r0 = r0 * r1
    sub r0, r0, r3  @ r0 = r0 - (r0 * r1) (remainder in r0)

    bx lr                @ Return

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

jelly:
    ldr r0, =jelly_array
    bx lr

ufo:
    ldr r0, =ufo_array
    bx lr

muscle:
    ldr r0, =muscle_array
    bx lr

longleg:
    ldr r0, =longleg_array
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

create_monster:
    cmp r0, #1
    beq jelly

    cmp r0, #2
    beq ufo

    cmp r0, #3
    beq muscle

    cmp r0, #4
    beq longleg
