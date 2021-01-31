	.text
	.globl	clz
	.type	clz, @function

clz:
 /* najpierw rozszerzamy pierwsze wsytapienie jedynki na wszytskie dolne bity*/
 /*przyklad 0001000 zamieniamy na 00011111*/
	mov 	%rdi,%rsi
	shr		$1,%rsi
	or 		%rsi,%rdi
	mov 	%rdi,%rsi
	shr		$2,%rsi
	or 		%rsi,%rdi
	mov 	%rdi,%rsi
	shr		$4,%rsi
	or 		%rsi,%rdi
	mov 	%rdi,%rsi
	shr		$8,%rsi
	or 		%rsi,%rdi
	mov 	%rdi,%rsi
	shr		$16,%rsi
	or 		%rsi,%rdi
	mov 	%rdi,%rsi
	shr		$32,%rsi
	or 		%rsi,%rdi
	
/*zamieniamy jedynki na zera i na odwrot dzieki czemu w miejscu wiodacych zer mamy jedynki a w kazdym innym miejscu dostajemy 0 */
/*dla przykladu z wyzej 00011111 zamieniamy na 11100000*/
	not 	%rdi 

/* cala reszta to skrocona wersja popcounta zapozyczona z https://en.wikipedia.org/wiki/Hamming_weight */
	
	mov 	%rdi,%rax
	mov 	$0x5555555555555555,%r9
	shr 	$1,%rdi
	and 	%r9,%rdi
	and 	%r9,%rax
	add 	%rdi,%rax

	mov 	%rax,%rdi
	mov 	$0x3333333333333333,%r9
	shr 	$2,%rdi
	and 	%r9,%rdi
	and 	%r9,%rax
	add 	%rdi,%rax

	mov 	%rax,%rdi
	mov 	$0x0f0f0f0f0f0f0f0f,%r9
	shr 	$4,%rdi
	and 	%r9,%rdi
	and 	%r9,%rax
	add 	%rdi,%rax

	mov		$0x0101010101010101,%r9
	imul	%r9,%rax
	shr		$56,%rax

	ret
	.size	clz, .-clz
