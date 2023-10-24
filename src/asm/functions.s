.data                     ; section for uninitialized data
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

    megachonker_array   .double 3.0
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
