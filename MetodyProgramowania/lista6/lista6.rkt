#lang racket 

;;//////useful things

(define (square x)
    (* x x))

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(unop op l)(and (symbol? op)(expr? l))]
    [(variable) true]
    [_ false]))

(define (value? v)
  (number? v))

(define (pow x n)
    (if (= n 1)
        x
        (* x (pow x (- n 1)))))

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /] ['^ (lambda (x s)(pow x s))] ['|| (lambda (x) (abs x))] ['$ (lambda (x) (deriviative x))]))

(define (eval e x)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval l x) (eval r x))]
    [(unop op v) (eval ((op->proc op) v)x)]
    [(variable) x]))

(define (parse q)
  (cond [(number? q) (const q)]
        [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
            (binop (first q) (parse (second q)) (parse (third q)))]
        [(and (list? q) (eq? (length q) 2) (symbol? (first q)))
            (unop (first q) (parse (second q)))]
        [(eq? q 'x) (variable)]))

(define (test) (eval (parse '(+ (* 2 3) (* 4 5)))1))

;;/////////////1

;;; a)(+ (+ (/ 8 (+ 2 3)) 10) 1) 

;;;             +
;;;         /       \
;;;        +         1
;;;      /   \
;;;     (/)     10   
;;;    /   \
;;;   8     +
;;;        /  \ 
;;;        2   3


;;; b)(+ (+ (+ 1 2) (* 3 4)) 5)

;;;             +
;;;         /       \
;;;        +         5
;;;      /   \
;;;     +     *
;;;    / \   / \
;;;   1  2   3  4  


;;///////////////////2

(struct const (val) #:transparent)
(struct binop (op l r) #:transparent)
(struct unop (op v) #:transparent)
(struct variable () #:transparent)


(define (cont-frac-expr num den i k)
    (if (= k i)
        (const 0)
        (binop '/ 
            (const(num i)) 
            (binop '+ (const (den i)) (cont-frac-expr num den (+ i 1) k)))))

(define (pi-expr n)
    (binop '+ 
        (const 3) 
        (cont-frac-expr (lambda (i) (square (- (* 2 i) 1.0))) (lambda (i) 6.0) 1.0 n)))

;;(define test-pi (eval(pi-expr 1000)))

;;test-pi

;;/////////////////////3

    ;;; (eval (parse '(^ 2 6)))
    ;;; (eval (parse '(|| -5)))


;;;;//////////////////////4
(define (pretty-printing x [flag #f])
    (match x
        [(const val) (number->string val)]
        [(binop op l r)
                (let*( 
                    [n (string-append "( " (pretty-printing l false) " " (symbol->string op) " " (pretty-printing r false) " )" )]
                    [nn (string-append (pretty-printing l false) " " (symbol->string op) " " (pretty-printing r false))]
                    [x (string-append (pretty-printing l true) " " (symbol->string op) " " (pretty-printing r true))])
                    (cond 
                        [(or(eq? op '*)(eq? op '/)(eq? op '^)) x]
                        [(and(or (eq? op '+)(eq? op '-))flag) n]
                        [else nn]))]
        [(unop op v) 
            (string-append "| "(pretty-printing v false)" |")]))

(pretty-printing(pi-expr 5))
(pretty-printing (parse '(|| -5)))
(pretty-printing (parse '(^ 2 6)))

;;;;///////////////////5

(parse '(* x (* x x)))

(define (deriviative x)
    
    (match x
        [(binop op l r)
            (cond
                [(eq? op '+)(binop op (deriviative l)(deriviative r))]
                [(eq? op '*)(binop '+ (binop '* (deriviative l) r)(binop '* l (deriviative r)))])]
        [(const x)(const 0)]
        [(variable) (const 1)]))

(deriviative (parse '(* x (* x x))))

;;;;/////////////////6


(define (simpl e)
    (match e
        [(const x) e]
        [(variable) e]
        [(binop op l r) 
            (cond
                [(and (const? l) (const? r))(parse (eval e 1))]
                [(and (eq? op '+)(variable? l)(const? r)(= 0 (const-val r)))(variable)]
                [(and (eq? op '+)(variable? r)(const? l)(= 0 (const-val l)))(variable)]
                [(and (eq? op '*)(variable? l)(const? r)(= 1 (const-val r)))(variable)]
                [(and (eq? op '*)(variable? r)(const? l)(= 1 (const-val l)))(variable)]
                [else (binop op (simpl l)(simpl r))])]))

(define smpl (binop '+ (const 2) (const 3)))

(simpl smpl)
(simpl (deriviative (parse '(* x (* x x)))))


;;///////////////////7

(eval (parse '( $ (* x (* x x)))) 2)
