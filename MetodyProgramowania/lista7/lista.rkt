#lang racket

; --------- ;
; Wyrazenia ;
; --------- ;

(struct const    (val)      #:transparent)
(struct binop    (op l r)   #:transparent)
(struct var-expr (id)       #:transparent)
(struct let-expr (id e1 e2) #:transparent)
(struct sym-expr (tp fr to f)#:transparent)


(define (type? x)
    (or(= x "sum") (= x "int") (= x "min")))

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(let-expr x e1 e2) (and (symbol? x) (expr? e1) (expr? e2))]
    [(sym-expr tp x y f) (and (type? tp)(expr? x)(expr? y)(expr f))]
    [_ false]))

(define (parse q)
  (cond
    [(number? q) (const q)]
    [(symbol? q) (var-expr q)]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'let))
     (let-expr (first (second q))
               (parse (second (second q)))
               (parse (third q)))]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]
    [(and (list? q)(eq? (length q)4)(type? (first q)))
        (sym-expr 
            (first q)
            (parse (secong q))
            (parse (third q))
            (parse (fourth q)))]))

(define (test-parse) (parse '(let [x (+ 2 2)] (+ x 1))))

; ----------------------- ;
; Podstawienie za zmienna ;
; ----------------------- ;

(define (subst e1 x e2)
  (match e2
    [(var-expr y) (if (eq? x y) e1 (var-expr y))]
    [(const n) (const n)]
    [(binop op l r)
     (binop op (subst e1 x l) (subst e1 x r))]
    [(let-expr y e3 e4)
     (let-expr y (subst e1 x e3) 
                 (if (eq? x y) e4 (subst e1 x e4)))]))

(define (test-subst)
  (subst (parse '(+ 2 2))
         'x
         (parse '(let [y (+ x 1)] (let [x (+ x y)] (+ y x))))))

; --------- ;
; Ewaluacja ;
; --------- ;

(define (value? v)
  (number? v))

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

(define (eval e)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]
    [(let-expr x e1 e2)
     (eval (subst (const (eval e1)) x e2))]))

(define (test-eval) (eval (test-subst)))

;;;;;;;1

;;;a
    ;;(^ 2 4)=16
    ;;(bin-op ^ (const 2) (const 4))
    ;;nie potrzeba nowej struktury
    ;;wystarczy rozszerzyc istniejacego binop 

;;;b 
    ;;; tworzymy nowa strukture sym-expr ktora jest lista 4-argumentowa 
    ;;; gdzie 1 argument to typ 2 - poczatek przedzialu 3 - koniec przedzialu
    ;;; 4 - funkcja 

;;;;;2

;;; dla a mamy po prostu (^ 2 3)
;;; dla reszty mamy (sum/int/min x y f())







;;;;;;;2

(struct bins (x s y)#:transparent)
(struct uns (n x)#:transparent)
(struct var (x)#:transparent)
(struct quan (q v f)#:transparent)

(define (parse-form q)
    (cond 
        []
        []
        []))