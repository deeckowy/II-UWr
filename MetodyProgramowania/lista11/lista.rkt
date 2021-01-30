#lang racket

(require racket/contract)

;;;;;;;;1 ~ little trick with returning list of 1 element

(define/contract (suffixes xs)
(parametric->/c [a] (-> (listof a) (listof (listof a))))
    (if (eq? (length xs) 2)
        (list (cdr xs))
        (cons (cdr xs) (suffixes (cdr xs)))))

(suffixes '(1 2 3 4 5 6 7 8 9 10))

;;;;;;2
(define/contract (sublists xs)
  (parametric->/c [a] (-> (listof a) (listof (listof a))))
  (if (null? xs)
      (list null)
      (append-map
       (lambda (ys)
         (cons (cons (car xs) ys) (list ys)))
       (sublists (cdr xs)))))

(sublists (list 1 2 3 4))



;;;;;;3 

;;#n - od uzytkownika 
;;#p - od programu 


;;(parametric->/c [a b] (-> a#n b#n a#p))

(define/contract (sample1 x y)
(parametric->/c [a b] (-> a b a))
    x)

(sample1 1 2)

;;(parametric->/c [a b c] (-> (-> a#p b#p c#n) (-> a#p b#n) a#n c#p)

(define/contract (sample2 f g x)
(parametric->/c [a b c] (-> (-> a b c) (-> a b) a c))
    (f x (g x)))

(sample2 (lambda (x y) (+ x y)) (lambda (x) (* x x)) 2)
(sample2 + identity 5)

;; (parametric->/c [a b c] (-> (-> b#p c#n) (-> a#p b#n) (-> a#n c#p)))

(define/contract (sample3 f g)
(parametric->/c [a b c] (-> (-> b c)(-> a b)(-> a c)))
    (lambda (x) (f (g x))))

((sample3 (lambda (x) (+ x 1)) (lambda (x) (* x 2))) 1)
((sample3 car cdr) (list 1 2 3))
;;(parametric->/c [a] (-> (-> (-> a#n a#p) a#n) a#p)

(define/contract (sample4 f)
(parametric->/c [a] (-> (-> (-> a a) a) a))
    (f f))

(sample4 (lambda (x) x))



;;; (define/contract (func3 e1)
;;;   (parametric->/c [a] (-> (-> (-> a a) a) a))
;;;   (e1 identity))
;;; ;(-> (-> (-> -a +a) -a) +a)
;;; (func3 (lambda (f) (f '(1 2 3))))

;;;;;;;4

;;; (define b 3)

;;; (define/contract ex4
;;; (parametric->/c [a b] (-> a b))
;;;     (lambda (x) (value x)))

;;; (ex4 1)

;;; (define/contract (foo x)
;;;   (parametric->/c [a b] (-> a b))
;;;   (/ 2020 0))

;;; (foo 2)



;;;;;;;5 
(define/contract (foldl-map f a xs)
  (parametric->/c [arg acum listValue] (-> (-> arg acum (cons/c listValue acum)) acum (listof arg) (cons/c (listof listValue) acum)))
  (define (it a xs ys)
    (if (null? xs)
        (cons (reverse ys) a)
        (let [(p (f (car xs) a))]
          (it (cdr p)
              (cdr xs)
              (cons (car p) ys)))))
  (it a xs null))


(foldl-map (lambda (x a) (cons a (+ a x))) 0 '(1 2 3))


; wykład 7 let-subst.rkt

; --------- ;
; Wyrazenia ;
; --------- ;

(struct const    (val)      #:transparent)
(struct binop    (op l r)   #:transparent)
(struct var-expr (id)       #:transparent)
(struct let-expr (id e1 e2) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(let-expr x e1 e2) (and (symbol? x) (expr? e1) (expr? e2))]
    [_ false]))

(define expr/c ; <- NOWE
  (flat-rec-contract expr
    (struct/c const number?)
    (struct/c binop symbol? expr expr)
    (struct/c var-expr symbol?)
    (struct/c let-expr symbol? expr expr)))

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
            (parse (third q)))]))

; ----------------------- ;
; Podstawienie za zmienna ;
; ----------------------- ;

(define/contract (subst e1 x e2)
  (-> expr/c symbol? expr/c expr/c)
  (match e2
    [(var-expr y) (if (eq? x y) e1 (var-expr y))]
    [(const n) (const n)]
    [(binop op l r)
     (binop op (subst e1 x l) (subst e1 x r))]
    [(let-expr y e3 e4)
     (let-expr y (subst e1 x e3)
                 (if (eq? x y) e4 (subst e1 x e4)))]))

; --------- ;
; Ewaluacja ;
; --------- ;

(define (value? v)
  (number? v))

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

(define/contract (eval e)
  (-> expr/c value?)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]
    [(let-expr x e1 e2)
     (eval (subst (const (eval e1)) x e2))]))

(eval (parse '(let [x (+ 2 2)] (+ x 1))))