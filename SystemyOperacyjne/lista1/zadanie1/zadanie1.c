/*
relacja rodzic-dzieko - wszystkie procesy sa tworzone na wzor innych procesow (rodzicow) 
dzieko dziedziczy po rodzicu pamiec 

identyfikator procesu - pid ~ unikalny numer dla kazdego procesu

PGID = "Process Group ID"; identyfikator grupy procesów, do której ten proces należy; 
na początku proces potomny należy do tej samej grupy co 
proces macierzysty (może jednak założyć własną grupę procesów i stać się jej przywódcą, 
czyli może mieć PID=PGID). 
Jakie są zastosowania grup procesów ?
np można wysyłać sygnały do całych grup procesów a nie tylko do pojedynczych procesów.

identyfikator rodzica ~ wskazuje na pochodzenie procesu 

rodzic procesu init ~ proces 0 jest to szablon procesu init ~ tak naprawde nie istnieje 

watki jadra ~ lekkie procesy odpowiadajace za wspomaganie dzialania jadra 
np. migration ~ odpowiada za przenoszenie procesow miedzy procesorami 
ich rodzicem jest kthread i sa oznaczone nawiasami []

PROCESS STATE CODES
       Here are the different values that the s, stat and state output specifiers (header "STAT" or "S") will display to describe the state of a process:
       D    uninterruptible sleep (usually IO)
       R    running or runnable (on run queue)
       S    interruptible sleep (waiting for an event to complete)
       T    stopped, either by a job control signal or because it is being traced.
       W    paging (not valid since the 2.6.xx kernel)
       X    dead (should never be seen)
       Z    defunct ("zombie") process, terminated but not reaped by its parent.

       For BSD formats and when the stat keyword is used, additional characters may be displayed:
       <    high-priority (not nice to other users)
       N    low-priority (nice to other users)
       L    has pages locked into memory (for real-time and custom IO)
       s    is a session leader
       +    is in the foreground process group.
       l    is multi-threaded (using CLONE_THREAD, like NPTL pthreads do)
*/