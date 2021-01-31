
///////1

// Symbol table '.symtab' contains 15 entries:
//    Num:    Value          Size Type    Bind   Vis      Ndx Name
//      0: 0000000000000000     0 NOTYPE  LOCAL  DEFAULT  UND 
//      1: 0000000000000000     0 FILE    LOCAL  DEFAULT  ABS swap.c
//      2: 0000000000000000     0 SECTION LOCAL  DEFAULT    1 //.text
//      3: 0000000000000000     0 SECTION LOCAL  DEFAULT    3 //.data
//      4: 0000000000000000     0 SECTION LOCAL  DEFAULT    4 //.bss
//      5: 0000000000000000     0 SECTION LOCAL  DEFAULT    5 //.data.rel
//      6: 0000000000000000     8 OBJECT  LOCAL  DEFAULT    4 bufp1 //.bss adres poczatku od poczatku sekcji to 0x0 a rozmiar symbolu to 8
//      7: 0000000000000000    22 FUNC    LOCAL  DEFAULT    1 incr //.text jest to pierwszy wpis w skecji wiec adres to 0x0 (od poczatku sekcji)
//      8: 0000000000000008     4 OBJECT  LOCAL  DEFAULT    4 count.1797 //.bss adres od poczatku to 0x8 a rozmiar to 4 jest to nasz int count
//      9: 0000000000000000     0 SECTION LOCAL  DEFAULT    8 //.note-GNU-Stack
//     10: 0000000000000000     0 SECTION LOCAL  DEFAULT    9 //.eh_frame
//     11: 0000000000000000     0 SECTION LOCAL  DEFAULT    7 //.comment
//     12: 0000000000000000     8 OBJECT  GLOBAL DEFAULT    5 bufp0 //.data.rel pierwszy symbol wiec jego adres w sekcji to 0x0 ma rozmiar 8 poniewaz jest wskaznikiem
//     13: 0000000000000000     0 NOTYPE  GLOBAL DEFAULT  UND buf // nie znajduje sie w zadnej sekcji mamy tylko informacje ze istnieje i bedzie dostepny w momencie wykonania pliku 
//     14: 0000000000000016    77 FUNC    GLOBAL DEFAULT    1 swap //nasza glowna fukcja ma rozmiar 77 i jest w miejscu 0x00016 czyli jest przesunieta o 22 adresy (pierwsza jest funkcja incr)


//.strtab - zawiery nazwy wszystkich symboli 
//.shstrtab - zawiera nazwy sekcji 


////////2 

// wystepuje konflikt nazw main w pliku mismatch-a.c odnosi sie do funkcji main a main w mismatch-b.c odnosi sie do zmiennej char 
// poniewaz char main nie jest zainicjalizowany odnosi sie do wartosci funkcji ktora jest zainicjalizowana w pliku mismatch-a.c i funkcja p2
// pokaze nam wartosc pierwszego bajtu z sekcji w ktorej znajduje sie main 

//gdybysmy pod zmienna globalna char main przypisali wartosc poniewaz
// nazwa mialaby dwie rozne wartosci 

//gdybysmy chcieli zmienic wartosc main w p2 otrzymamy blad seg fault poniewaz chcielibysmy zmienic dane w sekcji ktora nie jest do tego 
//przeznaczona 


//////////3

// ar -t libm-2.27.a | wc -l => 794
// ar -t libc.a | wc -l => 1690

///readelf -d python

//  0x0000000000000001 (NEEDED)             Shared library: [libc.so.6]
//  0x0000000000000001 (NEEDED)             Shared library: [libpthread.so.0]
//  0x0000000000000001 (NEEDED)             Shared library: [libdl.so.2]
//  0x0000000000000001 (NEEDED)             Shared library: [libutil.so.1]
//  0x0000000000000001 (NEEDED)             Shared library: [libz.so.1]
//  0x0000000000000001 (NEEDED)             Shared library: [libm.so.6]

///opcja -g generuje informacje dla gdb 



/////////6

// objdump -f main 

// main:     file format elf64-x86-64
// architecture: i386:x86-64, flags 0x00000112:
// EXEC_P, HAS_SYMS, D_PAGED
// start address 0x000000000040009b <- adres pierwszej instrukcji 




// objdump -D main


// 0000000000400078 <is_even>:
//   400078:	48 85 ff             	test   %rdi,%rdi  
//   40007b:	74 08                	je     400085 <is_even+0xd>
//   40007d:	48 ff cf             	dec    %rdi
//   400080:	e9 06 00 00 00       	jmpq   40008b <is_odd>
//   400085:	b8 01 00 00 00       	mov    $0x1,%eax
//   40008a:	c3                   	retq   

// 000000000040008b <is_odd>:
//   40008b:	48 85 ff             	test   %rdi,%rdi
//   40008e:	74 08                	je     400098 <is_odd+0xd>
//   400090:	48 ff cf             	dec    %rdi
//   400093:	e9 e0 ff ff ff       	jmpq   400078 <is_even>
//   400098:	31 c0                	xor    %eax,%eax
//   40009a:	c3                   	retq   

// 000000000040009b <_start>:
//   40009b:	48 83 ec 08          	sub    $0x8,%rsp <- jest tutaj ! 
//   40009f:	bf 2a 00 00 00       	mov    $0x2a,%edi
//   4000a4:	e8 cf ff ff ff       	callq  400078 <is_even>
//   4000a9:	89 c7                	mov    %eax,%edi
//   4000ab:	b8 3c 00 00 00       	mov    $0x3c,%eax
//   4000b0:	0f 05                	syscall 
//   4000b2:	58                   	pop    %rax
//   4000b3:	c3                   	retq   


//objdump -h main 


// main:     file format elf64-x86-64

// Sections:
// Idx Name          Size      VMA               LMA               File off  Algn
//   0 .text         0000003c  0000000000400078  0000000000400078  00000078  2**0
//                   CONTENTS, ALLOC, LOAD, READONLY, CODE


//ld --verbose 
//skrypt linkera to zbior komend dla programu ktore mowia jak i gdzie umiescic sekcje w pamieci 




/////////////////////7
//te sekcje przechowuja informacje dla linkera jak zmodyfikowac 
//referencje do tych obiektow podczas scalania plikow do pliku wykonywalnego