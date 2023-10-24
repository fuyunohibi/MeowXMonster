.bss                     ; section for uninitialized data
    character_array: .skip 88                 ; reserve space for 4 doubles (4*8 = 32 bytes)

    monster_array:  .skip 120


create_character:
    push {r8,r9,r10,lr}
    ldr r8 ,=character_array
    cmp r8, #1


isLaika:
    



