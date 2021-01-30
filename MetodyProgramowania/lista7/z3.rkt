#lang racket
(require racket/set)


;;;;;;;;3
(struct bins (x s y)#:transparent)
(struct neg (x)#:transparent)
(struct var-form (x)#:transparent)
(struct quan (q v f)#:transparent)
(struct myset (xs) #:transparent)

(define (empty-set? x)
    (= null x))

(define (new-set)
    (myset null))

(define (add-elem-set x ss)
    (myset (list x (myset-xs ss))))

(define (look-for x ss)
    (define (look-iter s)
        (cond   
            [(null? s)#f]
            [(eq? x (first s))(second s)]
            [else (look-iter (cdr s))]))
            
    (look-iter (myset-xs ss)))



(define (qu? q)
    (or (eq? q 'E)(eq? q 'A)))


(define (parse-form q)
    (cond 
        [(symbol? q)(var-form q)]
        [(and (list? q) (= 3 (length q)) (qu? (first q)))
            (quan 
                (first q)
                (second q)
                (parse-form (third q)))]      
        [(and (list? q) (= (length q)3))
            (bins 
                (parse-form (first q))
                (second q)
                (parse-form (third q)))]
        [(and (list? q)(= 2 (length q)) (eq? (first q) '~))
            (neg 
                (parse-form (second q)))]))

;;(parse-form '(A x (x <=> y)))


;;;;;;;;;;;;4



(define(free-vars q e)
    (match q
        [(quan g v f)
            (if(set-member? e v)
                (free-vars f e)
                (set-union (free-vars v e)(free-vars f e)))]
        [(var-form x) 
            (if (set-member? e x)
                (set)
                (set-add e x))]
        [(bins x u v)
            (set-union 
                (free-vars x e)
                (free-vars v e))]
        [(neg f)(free-vars f e)]
        ))

(define (conn->proc x)
    (match x 
        ['=> (lambda (z y)(implies z y))]
        ['|| (lambda (z y)(or z y))]
        ['& (lambda (z y) (and z y))]
        ['<=> eq?]))



(define (eval-form q)
    
    (define (eval-iter q s)
        (match q
            [(var-form x)(look-for x s)]
            [(neg f)(not(eval-iter f s))]
            [(bins x u v)((conn->proc u) (eval-iter x s) (eval-iter v s))]
            [(quan g v f) 
                (if (eq? g 'A)
                    (and (eval-iter f (add-elem-set (list v #t) s)) (eval-iter f (add-elem-set (list v #f) s)))
                    (or (eval-iter f (add-elem-set (list v #t) s)) (eval-iter f (add-elem-set (list v #f) s))))]))

    (eval-iter q (new-set)))
    
(parse-form '(A y (y || (~ y))))
(parse-form '(E x (A y ((y || (~ y)) || x))))
(eval-form (parse-form '(E x (A y ((y || (~ y)) & x)))))


