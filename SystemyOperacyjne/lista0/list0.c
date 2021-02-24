/*1111
hardware interrupt - wywolywany przez zewnetrzne urzadzenie (dysk, klawiatura, myszka)
urzadzenia wysylaja przerwanie z zadaniem obsluzenia przez procesor 
asynchroniczne - niezalezne od wykonywanych instrukcji 
powraca do nastepnej instrukcji   
przyklady :
- wczytanie strony z dysku
- wcisniecie klawisza na klawiaturze 
- klikniecie myszka 

exception - blad spowodowany wykonywaniem instruckji synchroniczny - wywolywany przez instrukcje 
moze powrocic do wykonywanej instrukcji jesli uda sie naprawic blad 
np:
- dzielenie przez 0 
- page fault 
- segmentation fault - General protection fault 

trap - celowe przerwanie wywolane przez instrukcje, zazwyczaj zamierzone przez uzytkownika 
np: 
- odczyt pliku 
- zapisanie do pliku 
- zakonczenie aktualnego procesu 
- stworzenie nowego procesu 

wyjatek procesora nie oznacza bledu czasu wykonania programu to page fault 
pulapka jest generowana np kiedy program chce odczytac plik 
*/

