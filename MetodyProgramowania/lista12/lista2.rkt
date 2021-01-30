#lang racket 

;;;;;;;3 - cd nie da sie zrobic dwoch definicji o takiej samej nazwie w jednym pliku 

(require racket/contract)
(require quickcheck)


(define-signature monoid-list^
    ((contracted
        [elem? (-> any/c boolean?)]
        [neutral elem?]
        [oper (-> elem? elem? elem?)])))


(define-unit monoid-list@
    (import)
    (export monoid-list^)
    
    (define (elem? x)
        (list? x))
        
    (define neutral null)
    
    (define (oper x y)
        (append x y)))

(define-values/invoke-unit/infer monoid-list@)

(oper '(1 2 3) '(5 6 3))
(oper '(1 24) neutral)

;;;;;;4 

(quickcheck 
    (property 
        ([l (arbitrary-list arbitrary-real)])
            (and (equal? l (oper l neutral))(equal? (oper l neutral) (oper neutral l)) (equal? l (oper neutral l)))))

(quickcheck 
    (property 
        ([xs (arbitrary-list arbitrary-real)]
        [ys (arbitrary-list arbitrary-real)])
            (and (andmap (lambda (y) (if (boolean? (member y (oper xs ys))) #f #t))xs)
                 (andmap (lambda (y) (if (boolean? (member y (oper ys xs))) #f #t))ys))))


;;;;;5 

(define-signature int-set^ 
    ((contracted
        [set? (-> any/c boolean?)]
        [is-in? (-> set? integer? boolean?)]
        [null-set (and/c set? cons?)]
        [make-sing (-> integer? set?)]
        [sum (-> set? set? set?)]
        [prod (-> set? set? set?)])))

(define-unit int-set@
    (import)
    (export int-set^)
    
    (define (set? x)
        (and 
            (eq? 'set (car x))
            (andmap (lambda (x) (integer? x)) (cdr x))))
        
    (define (is-in? xs y)
        (if (member y (cdr xs)) #t #f))
        
    (define null-set 
        (cons 'set null))

    (define (make-sing x)
        (cons 'set (list x)))

    (define (sum xs ys)
        (cons 'set (append (list (append-map (lambda (x) (if (member x (cdr xs)) null x)) (cdr ys))) (cdr xs))))

    (define (prod xs ys)
        (cons 'set (append-map (lambda (x) (if (member x (cdr ys)) x null)) (cdr xs)))))


(define-values/invoke-unit/infer int-set@)

(define t (make-sing 1))
(define x (make-sing 2))

(sum x t)
(equal? (prod t x) null-set)



;;;;;;;6 

(define arbitrary-set
    (cons 'set (arbitrary-list arbitrary-integer)))

(quickcheck 
    (property 
        ([s (arbitrary-set)])
        (display s)))











