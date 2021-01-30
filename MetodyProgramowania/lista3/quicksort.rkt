#lang racket

(provide partition quicksort)

(define (partition n xs)
    
    (define (part-iter lx ux fx)
        (cond
            [(null? fx) (cons lx ux)]
            [(> (car fx) n) (part-iter lx (append (list (car fx)) ux) (cdr fx))]
            [else (part-iter (append (list (car fx)) lx) ux (cdr fx))]))
    (part-iter null null xs))

(define (quicksort l)
    (cond
        [(null? l) null]
        [(= 1 (length l)) l]
        [else (append (quicksort(car(partition (car l)(cdr l)))) (append (list (car l)) (quicksort (cdr(partition (car l)(cdr l))))))]))

(quicksort (list 2 2 8 3 4 2 1 2 3))
(quicksort (list 1 2 3 4 5 6 7 8 9))
(quicksort (list 9 8 7 6 5 4 3 2 1))
(quicksort (list 98889 3232 37216 367216 4897 4937 349827 478 438 3402 4023 34802 192 4830 32047 3284 3482 4 21))
