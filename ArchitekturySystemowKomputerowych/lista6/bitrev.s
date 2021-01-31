	.text
	.globl	bitrev
	.type	bitrev, @function

bitrev:
        xor     %eax,%eax
		mov		%rdi,%rax
		mov		$0xAAAAAAAAAAAAAAAA,%r8 /*maska 1010101010*/
		mov		$0x5555555555555555,%r9 /*maska 0101010101*/
		and 	%r8,%rax /*wycinanie bitow wedlug pierwszej maski */
		and		%r9,%rdi /*tak samo jak wyzej z wykorzystaniem drugiej maski*/
		shr		$1,%rax /* przesuniecie wycietych bitow o 1 miejsce w prawo - przesuniecie logiczne nie chcemy 1 na poczatku */ 
		shl		$1,%rdi  /* przesuniecie wycietych bitow o 1 w lewo*/
		or		%rax,%rdi /*zlaczenie przesunietych bitow spowrotem w jedna liczbe */
		/*cala operacja sprawila ze zamienilismy bit 0 z bitem 1 , bit 2 z bitem 3 itp*/
		/*nastepnie powtarzamy to dla par,czworek, osemek, 16 i na koncu zamieniamy dwie polowki 32-bitowe co daje nam odwrocenie bitow */
		mov		%rdi,%rax
		mov		$0xCCCCCCCCCCCCCCCC,%r8
		mov		$0x3333333333333333,%r9
		and 	%r8,%rax
		and		%r9,%rdi
		shr		$2,%rax
		shl		$2,%rdi
		or		%rax,%rdi

		mov		%rdi,%rax
		mov		$0xF0F0F0F0F0F0F0F0,%r8
		mov		$0xF0F0F0F0F0F0F0F,%r9
		and 	%r8,%rax
		and		%r9,%rdi
		shr		$4,%rax
		shl		$4,%rdi
		or		%rax,%rdi

		mov		%rdi,%rax
		mov		$0xFF00FF00FF00FF00,%r8
		mov		$0xFF00FF00FF00FF,%r9
		and 	%r8,%rax
		and		%r9,%rdi
		shr		$8,%rax
		shl		$8,%rdi
		or		%rax,%rdi

		mov		%rdi,%rax
		mov		$0xFFFF0000FFFF0000,%r8
		mov		$0xFFFF0000FFFF,%r9
		and 	%r8,%rax
		and		%r9,%rdi
		shr		$16,%rax
		shl		$16,%rdi
		or		%rax,%rdi

		mov		%rdi,%rax
		shr		$32,%rax
		shl		$32,%rdi
		or		%rdi,%rax

	ret

	.size	bitrev, .-bitrev
