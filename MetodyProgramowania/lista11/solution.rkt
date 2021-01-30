#lang racket 

(require racket/contract)


(define with-labels/c 
(parametric->/c [a b] (-> (-> a b) (listof a) (listof (listof (and/c a b))))))


(define/contract (with-labels f xs)
with-labels/c
    (define (make-pair f x)
        (list(list (f x) x)))
        
    (append-map (lambda (x) (make-pair f x)) xs))

(with-labels (lambda (x) (+ x 1)) (list 1 2 3))
