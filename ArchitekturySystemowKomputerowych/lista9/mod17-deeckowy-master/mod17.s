	.text
	.globl	mod17
	.type	mod17, @function

mod17:
	/*na poczatku wycinamy parzyste i nieparzyste liczby hex*/
	xor		%eax,%eax
	mov 	%rdi,%rdx
	mov 	%rdi,%rcx
	mov		$0x0f0f0f0f0f0f0f0f,%r9
	and		%r9,%rcx
	mov 	$0xf0f0f0f0f0f0f0f0,%r9
	and		%r9,%rdx

	/*nastepnie wykonujemy dodawanie i odejmowanie wedlug przykladu tj parzyste liczby dodajemy a nieparzyste odejmujemy 
	(oszczedza to jedna instrukcje ~ odejmowanie dwoch sum na koncu) - dzialamy na rejestrach 8-bitowych poniewaz skrajny przypadki to 120 oraz -120*/ 
	add		%cl,%al
	shr 	$4,%rdx
	sub		%dl,%al
	
	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al

	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al

	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al

	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al

	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al

	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al

	shr		$8,%rcx
	shr 	$8,%rdx
	add		%cl,%al
	sub		%dl,%al
	/*w tym momencie w rejestrze %al mamy liczbe zapisana na dwoch cyfrach hex ktora ma taka sama reszte z dzielenia przez 17 jak nasza liczba 64-bitowa
	powtarzamy wiec operacje z odejmowaniem dwoch liczb jednak teraz zachowujemy nasz znak w rezultacie dostaniemy liczby od -7 do 30*/ 
	mov		%al,%dl
	mov		$0xF,%rdi
	and		%rdi,%rax
	sar		$4,%dl
	sub		%dl,%al
	/*na samym koncu chcemy policzyc reszte z liczby ktora otrzymalismy (-7..30)
	najpierw odejmujemy zeby wykluczyc liczby od 17 do 30*/
	sub 	$0x11,%al
	jge 	.L0  /*jesli po odjeciu dostanemy liczbe dodatnia to jest ona naszym wynikiem */
	add 	$0x11,%al /*nastepnie dodajemy 17 aby wykluczyc liczby od 0 do 16 (x-17+17=0)*/
	jns 	.L0 /*jesli liczba liczba nie jest ujemna to jest naszym wynikiem*/
	add		$0x11,%al/*na samym koncu liczymy modulo 17 z liczb (-7...-1)*/
.L0:
	ret
	.size	mod17, .-mod17
