#lang typed/racket

; --------- ;
; Wyrazenia ;
; --------- ;


(struct const    ([val : Number])                        #:transparent)
(struct binop    ([op : BinopSym] [l : Expr] [r : Expr]) #:transparent)
(struct var-expr ([id : Symbol])                         #:transparent)
(struct let-expr ([id : Symbol] [e1 : Expr] [e2 : Expr]) #:transparent)

(define-type Expr (U const binop var-expr let-expr))

(define-type BinopSym (U '+ '- '* '/))
(define-predicate binop-sym? BinopSym)



(: parse (-> Any Expr))
(define (parse q)
  (match q
    [_ #:when (number? q) (const q)]
    [_ #:when (symbol? q) (var-expr q)]
    [`(,op ,e1 ,e2)
     #:when (binop-sym? op)
     (binop op (parse e1) (parse e2))]
    [`(let (,x ,e1) ,e2)
    #:when (symbol? x)
     (let-expr x (parse e1) (parse e2))]))


;;;;      Alternatywka
;;; (: parse (-> Any Expr))
;;; (define (parse q)
;;;   (match q
;;;     [(? number? n) (const n)]
;;;     [(? symbol? s) (var-expr s)]
;;;     [(list 'let (list (? symbol? x) expr) body)
;;;       (let-expr x (parse expr) (parse body))]
;;;     [(list (? op? op) l r) (binop op (parse l) (parse r))]))


(define (test-parse) (parse '(let [x (+ 2 2)] (+ x 1))))

; ----------------------- ;
; Podstawienie za zmienna ;
; ----------------------- ;

( : subst (-> Expr Symbol Expr Expr))
(define (subst e1 x e2)
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

( : value? (-> Any Boolean))
(define (value? v)
  (number? v))

( : op->proc (-> BinopSym (-> Number Number Number)))
(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

( : eval (-> Expr Number))
(define (eval e)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval l) (eval r))]
    [(let-expr x e1 e2)
     (eval (subst (const (eval e1)) x e2))]))