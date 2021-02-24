/**
 *
 * 
 * 
 * proc(5) - wirtualny system plików, który udostępnia interfejs do struktur
        danych jądra. Zwyczajowo znajduje się w /proc. 
        procfs - wirtualny system plików pozwalający na komunikację z
        jądrem uniksowego systemu. Jego struktura występuje jedynie
        w pamięci operacyjnej komputera.
        System plików procfs montowany jest w katalogu /proc. Większość
        plików ma rozmiar 0 bajtów (wywołanie programu file zwraca empty, gdyż
        file wywołuje syscall stat(), który wykrywa specjalne pliki (można
        to wyłączyć flagą -s)).








    /proc/pid  - zawiera informacje związane z procesami o danym pid

    argumenty programu - parametry przekazane do programu w momencie
    jego wywołania.
        argc - liczba argumentów (włącznie z nazwą polecenia)
        argv[] - argumenty (argv[0] to nazwa polecenia)
    
    zmienne środowiskowe - zmienne, których wartości są ustawianie
        poza programem. Nazwane wartości, przechowywane i zarządzane
        przez powłokę. Każdy proces poswiada swój zestaw zmiennych
        środowiskowych, które dziedziczy po rodzicu.

    zmienne środowiskowe: /proc/[pid]/environ
    argumenty programu:   /proc/[pid]/cmdline

    pola w pliku status :

    UID-user ID - identyfikator uzytkownika 0-root 
    1-99 - dla demonow
    od 1000 dla uzytkownikow 
    GID- grupa 0-root -||-
    Groups - wspomagajace grupy procesu; dziedziczone po rodzicu
        (np. shellu); mówią o tym jakie uprawnienia ma proces
    VmPeak - największy rozmiar pamięci wirtualnej (do pamięci
        wirtualnej wliczają się też strony, które nie są wtoczone)
    VmSize - aktualny rozmiar pamięci wirtualnej
    VmRSS - resident set size; fizyczny rozmiar pamięci używanej
        przez proces; (zbiór roboczy procesu)
    Threads - liczba wątków w procesie zawierającym ten wątek
    voluntary_ctxt_switches - liczba dobrowolnych zmian kontekstu
        (jest wtedy kiedy proces opuszcza CPU bo nie ma nic
        do robienia (np. oczekuje na IO)).
    nonvoluntary_ctxt_switches - liczba zmian kontestu wywołanych
        przez wywłaszczenie procesu.
 * 
 * 
 * 
*/