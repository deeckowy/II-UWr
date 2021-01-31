        .text
        .globl  addsb
        .type   addsb, @function

addsb:

	mov		%rsi, %rax
	mov		%rsi, %rdx
	mov		$-9187201950435737472, %r9
	or		%rdi, %rax
	and		%rdi, %rdx
	not		%rax
	mov		%rdx, %rcx
	mov		%rax, %r10
	mov		$9187201950435737471, %rax
	and		%r9, %rcx
	and		%rax, %rdi
	and		%rax, %rsi
	add		%rdi, %rsi
	mov		%rsi, %r8
	not		%r8
	and		%rcx, %r8
	mov		%r10, %rcx
	and		%rsi, %rcx
	mov		%r8, %rax
	and		%r9, %rcx
	or		%rcx, %rax
	lea		(%rax,%rax), %rdi
	shr		$7, %rax
	sub		%rax, %rdi
	mov		%rdi, %rax
	mov		%rcx, %rdi
	not		%rax
	shr		$7, %rdi
	and		%rax, %rsi
	mov		%rdx, %rax
	sub		%rdi, %rcx
	or		%r10, %rax
	or		%r8, %rcx
	not		%rax
	and		%r9, %rax
	xor		%rsi, %rax
	or		%rcx, %rax
	ret
        .size   addsb, .-addsb
