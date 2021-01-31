.globl puzzle2

puzzle2:
    movq  %rdi, %rax
.L3:  movb  (%rax), %r9b
    leaq  1(%rax), %r8
    movq  %rsi, %rdx
.L2:  movb  (%rdx), %cl
    incq  %rdx
    testb %cl, %cl
    je    .L4
    cmpb  %cl, %r9b
    jne   .L2
    movq  %r8, %rax
    jmp   .L3
.L4:  subq  %rdi, %rax
    ret
