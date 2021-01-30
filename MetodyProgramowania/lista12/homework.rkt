#lang racket

(require "graph.rkt")
(provide bag-stack@ bag-fifo@)

;; struktura danych - stos
(define-unit bag-stack@
  (import)
  (export bag^)
    
    (define (bag? b)
        (and
            (pair? b)
            (list? (car b))
            (eq? 'bag-stack (cdr b))))

    (define empty-bag 
        (cons null 'bag-stack))

    (define (bag-empty? b)
        (null? (car b)))

    (define (bag-insert b e)
        (cons (cons e (car b)) (cdr b)))

    (define (bag-peek b)
        (caar b))

    (define (bag-remove b)
        (cons (cdar b) (cdr b)))

)

;; struktura danych - kolejka FIFO
(define-unit bag-fifo@
  (import)
  (export bag^)

    (define (bag? b)
        (and 
            (list? b)
            (eq? (length b) 3)
            (eq? 'bag-fifo (car b))
            (list? (second b))
            (list? (third b))))

    (define empty-bag   
        (list 'bag-fifo null null))

    (define (bag-empty? b)
        (and (null? (second b)) (null? (third b))))

    (define (bag-insert b e)
    (let ([new (cons e (second b))])
        (list (car b) new (reverse new))))

    (define (bag-peek b)
        (if(null? (third b))
            null
            (car (third b))))
    
    (define (bag-remove b)
        (let ([li (cdr (reverse (second b)))])
            (list (car b) (reverse li) li)))
)

;; otwarcie komponentów stosu i kolejki

(define-values/invoke-unit bag-stack@
  (import)
  (export (prefix stack: bag^)))

(define-values/invoke-unit bag-fifo@
  (import)
  (export (prefix fifo: bag^)))

;; testy w Quickchecku
(require quickcheck)

;; testy kolejek i stosów
(define-unit bag-tests@
  (import bag^)
  (export)
  
  ;; test przykładowy: jeśli do pustej struktury dodamy element
  ;; i od razu go usuniemy, wynikowa struktura jest pusta
  (quickcheck
   (property ([s arbitrary-symbol])
             (bag-empty? (bag-remove (bag-insert empty-bag s)))))
    
    ;;test 1: dodajemy dwa takie same elementy do pierwszej struktury
    ;; i jeden do drugiej i sprawdzamy czy po wyciagnieciu sa takie same 
    (quickcheck
        (property ([s arbitrary-symbol])
            (eq? 
                (bag-peek (bag-insert (bag-insert empty-bag s) s)) 
                (bag-peek (bag-insert empty-bag s)))))

    ;;test 2: sprawdzamy czy po dodaniu elementu struktury sa takie same
    (quickcheck 
        (property ([s arbitrary-symbol])
            (equal? (bag-insert empty-bag s) (bag-insert empty-bag s))))


)

;; uruchomienie testów dla obu struktur danych

(invoke-unit bag-tests@ (import (prefix stack: bag^)))
(invoke-unit bag-tests@ (import (prefix fifo: bag^)))

(define-unit stack-tests@ 
    (import bag^)
    (export)


    ;; sprawdzamy kolejnosc dla stosu
    (quickcheck 
        (property 
            ([x arbitrary-integer]
            [s arbitrary-symbol])
                (let ([full (bag-insert (bag-insert empty-bag x) s)])
                     (let* ([last (bag-peek full)]
                            [first (bag-peek (bag-remove full))])
                            (and (eq? last s) (eq? first x))))))    
    
)

(define-unit fifo-tests@ 
    (import bag^)
    (export)


    ;; sprawdzamy kolejnosc dla fifo 
    (quickcheck 
        (property 
            ([x arbitrary-integer]
            [s arbitrary-symbol])
                (let ([full (bag-insert (bag-insert empty-bag x) s)])
                     (let* ([first (bag-peek full)]
                            [last (bag-peek (bag-remove full))])
                            (and (eq? last s) (eq? first x))))))    
    
)
(invoke-unit stack-tests@ (import (prefix stack: bag^)))
(invoke-unit fifo-tests@ (import (prefix fifo: bag^)))


;; otwarcie komponentu grafu
(define-values/invoke-unit/infer simple-graph@)

;; otwarcie komponentów przeszukiwania 
;; w głąb i wszerz
(define-values/invoke-unit graph-search@
  (import graph^ (prefix stack: bag^))
  (export (prefix dfs: graph-search^)))

(define-values/invoke-unit graph-search@
  (import graph^ (prefix fifo: bag^))
  (export (prefix bfs: graph-search^)))

;; graf testowy
(define test-graph
  (graph
   (list 1 2 3 4)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4))))


(define big-graph
  (graph
   (list 1 2 3 4 5 6 7 8 9 10)
   (list (edge 1 3)
         (edge 1 2)
         (edge 2 4)
         (edge 6 3)
         (edge 8 1)
         (edge 1 10)
         (edge 10 3)
         (edge 4 5)
         (edge 6 7)
         (edge 9 7)
         (edge 4 2)
         (edge 9 6))))

(define empty-graph
    (graph
        null
        null))



;; uruchomienie przeszukiwania na przykładowym grafie
(bfs:search test-graph 1)
(dfs:search test-graph 1)


;;test dla big-graph
(bfs:search big-graph 1)
(dfs:search big-graph 1)

;;test dla empty-graph 
(bfs:search empty-graph 1)
(dfs:search empty-graph 1)
