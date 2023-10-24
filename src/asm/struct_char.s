.data
    Laika:  .space 50       @ name[50]
            .int 0          @ price
            .int 0          @ HP
            .byte 0         @ isAlive
            .float 0.0      @ attackDamage
            .float 0.0      @ attackPerSecond
            .float 0.0       @ attackTimer
            .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
            .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
            .int 0           @ blockPosition
            .float 0.0      @ rightBoundery
    laika_string:    .asciz "Laika"

    FartCat:   .space 50        @ name[50]
               .int 0           @ price
               .int 0           @ HP
               .byte 0          @ isAlive
               .float 0.0       @ attackDamage
               .float 0.0       @ attackPerSecond
               .float 0.0       @ attackTimer
               .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
               .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
               .int 0           @ blockPosition
               .float 0.0       @ rightBoundery
    fartCat_string: .asciz "FartCat"

    MegaChonker:    .space 50        @ name[50]
                    .int 0           @ price
                    .int 0           @ HP
                    .byte 0          @ isAlive
                    .float 0.0       @ attackDamage
                    .float 0.0       @ attackPerSecond
                    .float 0.0       @ attackTimer
                    .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
                    .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
                    .int 0           @ blockPosition
                    .float 0.0       @ rightBoundery
    megaChonker_string:  .asciz "MegaChonker"

    Bomb:       .space 50        @ name[50]
                .int 0           @ price
                .int 0           @ HP
                .byte 0          @ isAlive
                .float 0.0       @ attackDamage
                .float 0.0       @ attackPerSecond
                .float 0.0       @ attackTimer
                .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
                .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
                .int 0           @ blockPosition
                .float 0.0       @ rightBoundery
    bomb_string:    .asciz "Bomb"


    Jelly:      .space 50      @ name[50]
                .int 0         @ killReward
                .float 0.0     @ rateOfSpawn
                .int 0         @ HP
                .byte 0        @ isAlive
                .int 0         @ attackDamage
                .float 0.0     @ attackPerSecond
                .float 0.0     @ attackTimer
                .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
                .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
                .space 8       @ assuming Vector2 consists of two floats, so 8 bytes in total
                .byte 0        @ active
                .float 0.0     @ animationTimer
                .float 0.0     @ walkSpeed
                .int 0         @ row
    jelly_string: .asciz "Jelly The Monster"

    Ufo:        .space 50      @ name[50]
                .int 0         @ killReward
                .float 0.0     @ rateOfSpawn
                .int 0         @ HP
                .byte 0        @ isAlive
                .int 0         @ attackDamage
                .float 0.0     @ attackPerSecond
                .float 0.0     @ attackTimer
                .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
                .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
                .space 8       @ assuming Vector2 consists of two floats, so 8 bytes in total
                .byte 0        @ active
                .float 0.0     @ animationTimer
                .float 0.0     @ walkSpeed
                .int 0         @ row
    ufo_string: .asciz "Ufo The Monster"

    Muscle:     .space 50      @ name[50]
                .int 0         @ killReward
                .float 0.0     @ rateOfSpawn
                .int 0         @ HP
                .byte 0        @ isAlive
                .int 0         @ attackDamage
                .float 0.0     @ attackPerSecond
                .float 0.0     @ attackTimer
                .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
                .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
                .space 8       @ assuming Vector2 consists of two floats, so 8 bytes in total
                .byte 0        @ active
                .float 0.0     @ animationTimer
                .float 0.0     @ walkSpeed
                .int 0         @ row
    muscle_string: .asciz "Muscle The Monster"

    Longleg:    .space 50      @ name[50]
                .int 0         @ killReward
                .float 0.0     @ rateOfSpawn
                .int 0         @ HP
                .byte 0        @ isAlive
                .int 0         @ attackDamage
                .float 0.0     @ attackPerSecond
                .float 0.0     @ attackTimer
                .space NUM_FRAMES*4  @ assuming Texture2D is 4 bytes each
                .space NUM_BLOCKS    @ shouldDrawAnimation[NUM_BLOCKS]
                .space 8       @ assuming Vector2 consists of two floats, so 8 bytes in total
                .byte 0        @ active
                .float 0.0     @ animationTimer
                .float 0.0     @ walkSpeed
                .int 0         @ row
    longleg_string: .asciz "Longleg The Monster"


.text
.global createLaika
.global createFartCat
.global createMegaChonker
.global createBomb
.global createJelly
.global createUfo
.global createMuscle
.global createLongleg


strcpy:
    @ Simple strcpy implementation
    1: ldrb r2, [r1], #1
       strb r2, [r0], #1
       cmp r2, #0
       bne 1b
       bx lr


@ =================== LAIKA ===================
createLaika:
    @ Initialize `name` field
    ldr r0, =Laika
    ldr r1, =laika_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `price` field
    ldr r0, =Laika+50  @ address of price
    mov r1, #100
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =Laika+54
    ldr r1, =50000 @ NOTE: changed from 15,000
    str r1, [r0]


    @ Initialize `isAlive` field
    ldr r0, =Laika+58
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =Laika+59
    ldr r1, =50000    @ Assuming this fits within a 32-bit immediate
    str r1, [r0]

    @ Initialize `attackPerSecond` field
    ldr r0, =Laika+63
    ldr r1, =0x3f000000  @ IEEE 754 representation of 0.5 in float
    str r1, [r0]

@ =================== FARTCAT ===================
createFartCat:
    @ Initialize `name` field
    ldr r0, =FartCat
    ldr r1, =fartCat_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `price` field
    ldr r0, =FartCat+50  @ address of price
    mov r1, #250
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =FartCat+54
    ldr r1, =300000
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =FartCat+58
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =FartCat+59
    ldr r1, =150      @ This should fit within a 32-bit immediate
    str r1, [r0]

    @ Initialize `attackPerSecond` field
    ldr r0, =FartCat+63
    ldr r1, =0x3d4ccccd  @ IEEE 754 representation of 0.05 in float
    str r1, [r0]


@ =================== MEGACHONKER ===================
createMegaChonker:
    @ Initialize `name` field
    ldr r0, =MegaChonker
    ldr r1, =megaChonker_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `price` field
    ldr r0, =MegaChonker+50  @ address of price
    mov r1, #200
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =MegaChonker+54
    ldr r1, =400000
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =MegaChonker+58
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field with 0 (already set by default)

    @ Initialize `attackPerSecond` field with 0.0 (already set by default)

    @ Initialize `rightBoundery` field
    ldr r0, =MegaChonker+67  @ Assuming 3 floats (3 * 4 bytes) after the isAlive byte
    ldr r1, =0x43c00000  @ IEEE 754 representation of 180.0 in float
    str r1, [r0]


@ =================== BOMB ===================
createBomb:
    @ Initialize `name` field
    ldr r0, =Bomb
    ldr r1, =bomb_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `price` field
    ldr r0, =Bomb+50  @ address of price
    mov r1, #400
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =Bomb+54
    mov r1, #1
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =Bomb+58
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =Bomb+59
    ldr r1, =500000   @ This should fit within a 32-bit immediate
    str r1, [r0]

    @ Initialize `attackPerSecond` field with 0.0 (already set by default)

    @ Initialize `rightBoundery` field
    ldr r0, =Bomb+67  @ Assuming 3 floats (3 * 4 bytes) after the isAlive byte
    ldr r1, =0x43c00000  @ IEEE 754 representation of 180.0 in float
    str r1, [r0]


@ =================== JELLY ===================
createJelly:
    @ Initialize `name` field
    ldr r0, =Jelly
    ldr r1, =jelly_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `killReward` field
    ldr r0, =Jelly+50  @ address of killReward
    mov r1, #25
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =Jelly+58
    ldr r1, =150000
    str r1, [r0]

    @ Initialize `rateOfSpawn` field
    ldr r0, =Jelly+54
    ldr r1, =0x42200000  @ IEEE 754 representation of 40.0 in float
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =Jelly+62
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =Jelly+63
    mov r1, #80
    str r1, [r0]

    @ Initialize `attackPerSecond` field with 0.0 (already set by default)

    @ Initialize `walkSpeed` field
    add r0, r0, #74  @ Adjusting to reach the walkSpeed, skipping the previous fields
    ldr r1, =0x40c00000  @ IEEE 754 representation of 6.0 in float
    str r1, [r0]

@ =================== UFO ===================
createUfo:
    @ Initialize `name` field
    ldr r0, =Ufo
    ldr r1, =ufo_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `killReward` field
    ldr r0, =Ufo+50  @ address of killReward
    mov r1, #50
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =Ufo+58
    ldr r1, =250000
    str r1, [r0]

    @ Initialize `rateOfSpawn` field
    ldr r0, =Ufo+54
    ldr r1, =0x41c80000  @ IEEE 754 representation of 25.0 in float
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =Ufo+62
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =Ufo+63
    mov r1, #120
    str r1, [r0]

    @ Initialize `attackPerSecond` field with 0.0 (already set by default)

    @ Initialize `walkSpeed` field
    add r0, r0, #74  @ Adjusting to reach the walkSpeed, skipping the previous fields
    ldr r1, =0x40b00000  @ IEEE 754 representation of 5.5 in float
    str r1, [r0]


@ =================== MUSCLE ===================
createMuscle:
    @ Initialize `name` field
    ldr r0, =Muscle
    ldr r1, =muscle_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `killReward` field
    ldr r0, =Muscle+50  @ address of killReward
    mov r1, #80
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =Muscle+58
    ldr r1, =400000
    str r1, [r0]

    @ Initialize `rateOfSpawn` field
    ldr r0, =Muscle+54
    ldr r1, =0x41900000  @ IEEE 754 representation of 20.0 in float
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =Muscle+62
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =Muscle+63
    mov r1, #100
    str r1, [r0]

    @ Initialize `attackPerSecond` field with 0.0 (already set by default)

    @ Initialize `walkSpeed` field
    add r0, r0, #74  @ Adjusting to reach the walkSpeed, skipping the previous fields
    ldr r1, =0x40a00000  @ IEEE 754 representation of 5.0 in float
    str r1, [r0]


@ =================== LONGLEG ===================
createLongleg:
    @ Initialize `name` field
    ldr r0, =Longleg
    ldr r1, =longleg_string
    bl strcpy      @ Assuming strcpy function available

    @ Initialize `killReward` field
    ldr r0, =Longleg+50  @ address of killReward
    mov r1, #120
    str r1, [r0]

    @ Initialize `HP` field
    ldr r0, =Longleg+58
    ldr r1, =600000
    str r1, [r0]

    @ Initialize `rateOfSpawn` field
    ldr r0, =Longleg+54
    ldr r1, =0x41700000  @ IEEE 754 representation of 15.0 in float
    str r1, [r0]

    @ Initialize `isAlive` field
    ldr r0, =Longleg+62
    mov r1, #1
    strb r1, [r0]     @ Using strb for byte-wide store

    @ Initialize `attackDamage` field
    ldr r0, =Longleg+63
    mov r1, #200
    str r1, [r0]

    @ Initialize `attackPerSecond` field with 0.0 (already set by default)

    @ Initialize `walkSpeed` field
    add r0, r0, #74  @ Adjusting to reach the walkSpeed, skipping the previous fields
    ldr r1, =0x40900000  @ IEEE 754 representation of 4.5 in float
    str r1, [r0]