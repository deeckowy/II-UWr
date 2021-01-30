#lang racket 

(provide heapsort)(require "homework7.rkt")

;;///////////////////////

;;ex8

(define (heapsort l)
    
    (define (sort-iter l h)
        (if(null? l)
            (unheap h null)
            (sort-iter (cdr l) (heap-insert (make-elem (car l)(car l)) h))))

    (define (unheap h l)
        (if(heap-empty? h)
            l   
            (unheap (heap-pop h) (append l (list (elem-val (heap-min h)))))))

    (sort-iter l empty-heap))

(heapsort (list 9 7 5 3 1 2))