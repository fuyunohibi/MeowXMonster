global add_integers

section .text
add_integers:
    add rdi, rsi
    mov rax, rdi ; result is returned in rax
    ret
