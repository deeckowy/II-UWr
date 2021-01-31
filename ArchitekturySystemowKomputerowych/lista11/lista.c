//////111111

///pamiec mapowana bezposrednio to pamiec w ktorej mamy jeden wiersz na zbior 
///~ rozmiar bloku w naszej pamieci to 32 B
///~ ilosc wierszy w naszej pamieci to 32
///~ w naszym wierszu mamy 1 vaild bit 20 bitow na tag oraz 32*8 bitow na dane 
//mamy wiec 7 % wszystki bitow na metadane i 93 % bitow na wlasciwe dane 
//stosunek 21:256

////////222222

//nasze adresy beda mialy 12 bitow blok ma 4 bajty tag to 8 bitow 
/// adres jest wiec postaci TTTT TTTT SS BB


//dla adresu 832 mamy tag = 83 S = 0 B = 2 
//w secie nr 0 istnieje blok o tagu 83 i jest wazny wiec odczytujemy CC

//dla adresu 835 mamy tag = 83 S = 1 B = 1 
//w secie nr 1 istnieje blok o tagu 83 i jest nie wazny wiec mamy chyebienie 

//dla adresu FFD mamy tag = FF S = 3 B = 1 
//w secie nr 3 istnieje blok o tagu FF i jest wazny wiec odczytujemy C0

//////3 

// 0 - tag = 00 s = 0 b = 0 cold miss  

// 4 -  tag = 00 s = 1 b = 0 cold miss

// 10 - tag = 01 s = 0 b = 0 cold miss 

// 84 - tag = 08 s = 1 b = 0  cold miss

// E8 - tag = 0E s = 2 b = 0 cold miss

// A0 - tag = 0A s = 0 b = 0 conflict miss 

// 400 - tag = 40 s = 0 b = 0 - conflict miss

// 1C - tag = 01 s = 3 b = 0 cold miss

// 8C - tag = 08 s = 3 b = 0 cold miss

// C1C - tag = C1 s = 3 b = 0 cold miss 

// B4 - tag = 0B s = 2 b = 0 cold miss 

// 884 - tag = 88 s = 2 b = 0 conflict miss
 
// przyjmujac ze poswiecamy dane ktore sa w pamieci najdluzej nasza pamiec moze wygladac w ten sposob

//   S    |       TT       |
//   0    |       0A       |
//        |       40       |
// --------------------------
//   1    |       00       |
//        |       08       |
// --------------------------
//   2    |       88       |
//        |       0B       |
// --------------------------
//   3    |       08       |
//        |       C1       |
// --------------------------


// efektywnosc = 0%

/////////////444444

////////////5 to chill i tylko duzo pisania a nie chce mi sie kopiowac tu wikipedii XD

//////////6 

// saveword(address)
// is in ? L1 y-> is dirty? y-> is free space ? L2 y-> send it to L2 !
// |              |                 |n                    ^
// |              |                 v                     |
// |              |                 saveword(smthfrom L2)-|
// |              |                         
// |              |
// | n            |n
// |              v
// |              don't care just throw it out!
// |                ^
// |                |n
// v                |
// is in ? L2 y-> is dirty? y-> send it to RAM!

///////////7777777
////~ tylko pamiec L1 
//// mamy 0.92 * 0.66 + 0.08 * 70 = 6.20 ns
//// jesli dostep do pamieci trwa srednio 6.2ns = ok 9.5 cyklu to CPI procesora = 0.36 * 9.5 + 0.64 = 4.06

////~ pamiec L1 i L2 
//// mamy 0.92 * 0.66 + 0.0784  * 5.62 + 0.0016 * 70 = 1.16 ns
//// CPI = 0.36 * 1.75 + 0.64 = 1.27  