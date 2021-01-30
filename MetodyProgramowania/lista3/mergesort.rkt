#lang racket 

(provide merge split mergesort)

(define (split l)
    
    (define (split-iter n l1 l2)
        (if (>= n (/ (length l) 2))
            (append (list l1) l2)
            (split-iter (+ n 1) (append l1 (list (car l2))) (cdr l2))))
    (split-iter 0 null l))

(define (merge k l)
    (cond 
        [(and (null? k)(null? l)) null]
        [(null? k) (cons (car l)(merge null (cdr l)))]
        [(null? l) (cons (car k)(merge (cdr k) null))]
        [(> (car l)(car k)) (cons (car k)(merge (cdr k) l))]
        [else (cons (car l)(merge k (cdr l)))]))


(define (mergesort l)
    (if (= 1 (length l))
        l
        (merge (mergesort (car(split l)))(mergesort (cdr(split l))))))

(mergesort(list 0 9 3 4 5 1 -9 32 69 -2 9 21 683 392 490))
(mergesort(list 0 0 0 0 0 0 0 1 2 3 4 4 5))
(mergesort(list 9 8 7 6 5 4 3 2 1 0))
(mergesort(list 0 9 8 3 4 8 89 23 67 32 12 23))
