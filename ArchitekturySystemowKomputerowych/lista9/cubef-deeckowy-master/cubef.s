	.text
	.globl	cubef
	.type	cubef, @function

cubef:
	mov 	$0x7F800000,%r8 #exponent mask
	mov 	$0x7FFFFF,%r9 #mantisa mask
	
	#dont care about sign ~ cause i want to take my %rdi till the end of execution

	#dealing with exponent
	and 	%rdi,%r8
	sub 	$0x3f800000,%r8
	add 	%r8,%r8
	add 	$0x3f800000,%r8

	#dealing with mantisa
	and 	%rdi,%r9
	or 		$0x800000,%r9
	imul 	%r9,%r9
	shr 	$23,%r9
	
	#normalization 
	mov 	$0xff000000,%rcx
	and 	%r9,%rcx
	shr 	$1,%rcx
	add		%rcx,%r8
	shr		$23,%rcx
	shr 	%cl,%r9
	mov 	$0x007fffff,%rcx
	and 	%rcx,%r9

	#putting every part in one register
	or 		%r9,%r8
	mov 	$0x80000000,%rcx
	and 	%rdi,%rcx
	or 		%r8,%rcx
	mov 	%rcx,%rax

#same but now we have two diffrent numbers so we need to do more actions
	mov 	$0x7F800000,%r8 #exponent mask
	mov 	$0x7FFFFF,%r9 #mantisa mask
	mov 	%rdi,%rsi

	#dealing with exponents
	and 	%r8,%rdi
	and 	%rax,%r8
	sub 	$0x3f800000,%r8
	sub 	$0x3f800000,%rdi
	add 	%rdi,%r8
	add 	$0x3f800000,%r8

	#dealing with mantisas
	and 	%r9,%rsi
	and 	%rax,%r9
	or 		$0x800000,%rsi
	or 		$0x800000,%r9
	imul 	%rsi,%r9
	shr 	$23,%r9

	#normalization 
	mov 	$0xff000000,%rcx
	and 	%r9,%rcx
	shr 	$1,%rcx
	add		%rcx,%r8
	shr		$23,%rcx
	shr 	%cl,%r9
	mov 	$0x007fffff,%rcx
	and 	%rcx,%r9

	#putting every part in one register
	or 		%r9,%r8
	mov 	$0x80000000,%rcx
	and 	%rax,%rcx
	or 		%r8,%rcx
	mov 	%rcx,%rax

	ret

	.size	cubef, .-cubef
