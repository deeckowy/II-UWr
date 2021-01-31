
///////////1

// Czas przeczytania jednego sektora ~
// Mamy 360 obr/min czyli w ciagu sekundy przeczytamy sciezke 6 razy co daje nam 6/s  
// Mnozymy wynik przez ilosc sektorow na sciezke  ~ 96 sektorow/sciezke mamy 576 sektorow przeczytanych w ciagu jednej sekundy
// Mnozymy razy liczbe bajtow w sektorze co daje nam 294912B/s = 294.912B/ms =0,294912 B/us  
// czyli do przeczytanie jedengo bajtu potrzebujemy ok.3,4 us wtedy zglaszamy przerwanie ktore procesor obsluzy w 
// 2,5 us aby obliczyc % czasu prosecora stosujemy 2,5/3,4 * 100 = 73%  

// Jesli przerwanie bedzie trwalo tyle samo i zglosimy je tylko raz po przeczytaniu sektora to przeczytanie sektora zajmie nam 
// 1740.8 us co daje nam % czasu procesora na poziomie 2.5/1740.8*100 =  ok. 1,4%

///////////2

// Szyna 32-bitowa ktora ma przepustowosc 10 milionow transferow to
// 32 miliony bitow przeslane w ciagu 1 sekundy daje to 32 Mbit/s czyli 4MB/s
// Wiec nasza przepustowosc zmiejszy sie 2 razy co w trybie cycle stealing oznacza ze procesor 
// bedzie korzystal z pamieci 2 razy rzadziej niz wczesniej wiec ilosc dostepow do pamieci to 20%


////////3

// Mamy procesor i7-6700 i czasy dostepu do pamieci :
// L1:4 cykle ~ 90% danych 
// L2:12 cykli ~ 95% danych 
// L3:40 cykli ~ 98% danych
// DRAM :200 cykli ~ 100% danych 

// uzywamy sredniej wazonej aby obliczyc srednia 
// 90 * 4 + 9.5 * 12 + 0.49 * 40 + 0.01 * 200 = 495.6/100 = 4.956 cyklu 
// pesymistyczny przypadek to taki w ktorym wszystkie potrzebne dane znajduja sie w pamieci DRAM czyli 200 cykli

////////4



//////////77777

// Stary procesor - AMD A8-6500 APU ~ 4 rdzenie
// CPU Clk: 3494 MHz 
// L1 Cache: 80K 32110 MB/s ~ 64/32110000000 = 1.99 us = 6.99  
// L2 Cache: 2048K 24020 MB/s ~ 64/24020000000 = 2.66 us = 9.31
// L3 Cache: None
// Memory: 3110M 4148 MB/s ~ 64/4184000000 = 15.42 us = 53.97

// Nowszy procesor - AMD Ryzen 5 3500U ~ 8 rdzeni
// CPU Clk: 2096 MHz 
// L1 Cache: 96K 50197 MB/s ~ 64/50197000000 = 1.27 us = 2.54
// L2 Cache: 512K 47525 MB/s ~ 64/47525000000 = 1.34 us = 2.68
// L3 Cache: 4096K 18530 MB/s ~ 64/18530000000 = 3.45 us = 6.9 
// Memory: 6083M 12375 MB/s ~ 64/12375000000 = 5.17 us = 10.34
