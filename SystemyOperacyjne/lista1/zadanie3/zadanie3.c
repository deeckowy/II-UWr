/**
 * aby znalezc pid x-serwera 
 * uzywamy 
 * ps ax|grep X 
 * 
 * majac pid uzywamy 
 * pmap -x pid
 * 
 * lub proc/pid/maps~ to pokaze sterte 
 * 
 * pamiec anonimowa ~ pamiec ktora nie jest powiazana z zadnym plikiem ani obiektem 
 * np stos lub sterta 
 * 
 * pliki odwzorowane w pamiec segment pamieci wirtualnej, ktory jest przypisany 
 * bezposrednio do pliku w postaci 1:1 pozwala ominac bufory read() i write()
 * 
 * kolumny :
 * adress - adres poczatku 
 * size -rozmiar
 * RSS - rozmiar fizycznej pamieci 
 * mode - pozwolenie na czytanie/pisanie/wykonywanie 
 * mapping - plik na jaki zmapowana jest pamiec 
 * /