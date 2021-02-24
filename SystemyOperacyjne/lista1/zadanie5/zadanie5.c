/**
 * czas wykonania - czas spędzony na wykonywaniu zadania.
    
    ograniczenie czasu wykonania - limit czasu jaki proces ma na
    wykonanie się.

    time find /usr > plik

    real	0m1,344s
    user	0m0,388s
    sys  	0m0,883s

    a) user - czas CPU spędzony w trybie użytkownika podczas
    wykonywania tego konkretnego procesu.
       sys - czas spędzony przez CPU na wykonywaniu syscalli
    przez jądro. Liczy się tylko czas dla tego konkretnego
    procesu.
       real - czas realny od uruchomienia procesu do jego zakończenia.

    b) Tak. User time jest sumowany po wszystkich rdzeniach. Używanie 
    dwóch rdzeni po 1s każdy daje łączny czas usera 2s podczas gdy
    realny to 1s.

    jak nałożyć ograniczenie?:

    ulimit -t [czas w sekundach]
   
    Program otrzymuje sygnał SIGKILL
*/