#lang racket 

(require quickcheck)
(require racket/contract)
;;;;;;1
(define (average y z)
    (/ (+ y z) 2))

(define (square x)
    (* x x))

(define (dist x y)
    (abs (- x y)))


(define sqrt/c 
    (->i ([x (and/c real? positive?)])
        [result (x) (and/c real? positive?)]
        #:post (x result)
            (< (dist x (* result result)) 0.00001)))


(define/contract (sqrt x)
sqrt/c
    (define (improve guess)
        (average guess (/ x guess)))

    (define (good-enough? g)
        (< (dist x (square g))
            0.00001))

    (define (iter guess)
        (if (good-enough? guess)
            guess
            (iter (improve guess))))
    (iter 1.0))


(sqrt 2)


;;;;;2 

(define filter/c 
    (parametric->/c [a] (-> (-> a boolean?) (listof a) (listof a))))


(define/contract (filter p xs)
    filter/c
    (cond 
        [(null? xs) null]
        [(p (car xs)) (cons (car xs) (filter p (cdr xs)))]
        [else (filter p (cdr xs))]))


(filter positive? '(-1 2 3 4 1))

(define filter2/c
    (->i ([p (-> any/c boolean?)]
          [x (or (listof any/c) any/c)])
          [result (p x) (listof any/c)]
          #:post (x result)
          (and/c (andmap (lambda (y) (if (boolean? (member y x)) #f #t)) result) 
                 (>= (length x) (length result)))))


(define/contract (filter2 p xs)
    filter2/c
    (cond 
        [(null? xs) null]
        [(p (car xs)) (cons (car xs) (filter p (cdr xs)))]
        [else (filter p (cdr xs))]))

(filter2 positive? '(-1 2 3 4 1))

;;;;;;;;;;3
(define-signature monoid-int^ 
    ((contracted 
        [elem? (-> any/c boolean?)]
        [neutral elem?]
        [oper (-> elem? elem? elem?)])))





(oper 1 2)
(oper 2 neutral)


;;;;;;4 

;;;sprawdzamy 1 warunek 
