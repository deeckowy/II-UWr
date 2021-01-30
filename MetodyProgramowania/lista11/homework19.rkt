#lang racket 

(require racket/contract)

(provide (contract-out
            [with-labels  with-labels/c]
            [foldr-map  foldr-map/c]
            [pair-from  pair-from/c ]))
(provide with-labels/c  foldr-map/c  pair-from/c)

(define with-labels/c 
(parametric->/c [a b] (-> (-> a b) (listof a) (listof (listof (or/c a b))))))

(define foldr-map/c 
  (parametric->/c [a acc xs] (-> (-> a acc (cons/c xs acc)) acc (listof a) (cons/c (listof xs) acc))))

(define pair-from/c 
(parametric->/c [a b c] (-> (-> a b) (-> a c) (-> a (cons/c b c)))))

(define/contract (with-labels f xs)
with-labels/c
    (define (make-pair f x)
        (list(list (f x) x)))
        
    (append-map (lambda (x) (make-pair f x)) xs))

(with-labels (lambda (x) (+ x 1)) (list 1 2 3))


(define/contract (foldr-map f a xs)
foldr-map/c
  (define (it a xs ys)
    (if (null? xs)
        (cons ys a)
        (let [(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a (reverse xs) null))


(foldr-map (lambda (x a) (cons a (+ a x))) 0 (list 1 2 3))


(define/contract (pair-from f g)
pair-from/c
    (lambda (x) (cons (f x) (g x))))

((pair-from (lambda (x) (+ x 1)) (lambda (x) (* x x))) 2)