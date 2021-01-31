	.file	"sample.c"
	.text
	.globl	foobar
	.type	foobar, @function
foobar:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	movl	%edi, -4(%rbp)
	movl	-4(%rbp), %eax
	popq	%rbp
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	foobar, .-foobar
	.section	.rodata
	.align 16
	.type	baz, @object
	.size	baz, 24
baz:
	.ascii	"abc"
	.zero	1
	.long	42
	.quad	-3
	.long	1068827777
	.zero	4
	.globl	array
	.bss
	.align 32
	.type	array, @object
	.size	array, 800
array:
	.zero	800
	.ident	"GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0"
	.section	.note.GNU-stack,"",@progbits
