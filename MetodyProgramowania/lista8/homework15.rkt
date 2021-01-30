#lang racket

(provide eval parse)

; Do list.rkt dodajemy procedury
;
; Miejsca, ktore sie zmienily oznaczone sa przez !!!

; --------- ;
; Wyrazenia ;
; --------- ;

(struct const      (val)      #:transparent)
(struct binop      (op l r)   #:transparent)
(struct var-expr   (id)       #:transparent)
(struct let-expr   (id e1 e2) #:transparent)
(struct if-expr    (eb et ef) #:transparent)
(struct cons-expr  (e1 e2)    #:transparent)
(struct car-expr   (e)        #:transparent)
(struct cdr-expr   (e)        #:transparent)
(struct null-expr  ()         #:transparent)
(struct null?-expr (e)        #:transparent)
(struct app        (f e)      #:transparent) ; <------------------ !!!
(struct lam        (id e)     #:transparent) ; <------------------ !!!

(define (expr? e)
  (match e
    [(const n) (or (number? n) (boolean? n))]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(let-expr x e1 e2)
     (and (symbol? x) (expr? e1) (expr? e2))]
    [(if-expr eb et ef)
     (and (expr? eb) (expr? et) (expr? ef))]
    [(cons-expr e1 e2) (and (expr? e1) (expr? e2))]
    [(car-expr e) (expr? e)]
    [(cdr-expr e) (expr? e)]
    [(null-expr) true]
    [(null?-expr e) (expr? e)]
    [(app f e) (and (expr? f) (expr? e))] ; <--------------------- !!!
    [(lam id e) (and (symbol? id) (expr? e))] ; <----------------- !!!
    [_ false]))

(define (parse q)
  (cond
    [(number? q) (const q)]
    [(eq? q 'true)  (const true)]
    [(eq? q 'false) (const false)]
    [(eq? q 'null)  (null-expr)]
    [(symbol? q) (var-expr q)]
    [(and (list? q) (eq? (length q) 2) (eq? (first q) 'null?))
     (null?-expr (parse (second q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'cons))
     (cons-expr (parse (second q))
                (parse (third q)))]
    [(and (list? q) (eq? (length q) 2) (eq? (first q) 'car))
     (car-expr (parse (second q)))]
    [(and (list? q) (eq? (length q) 2) (eq? (first q) 'cdr))
     (cdr-expr (parse (second q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'let))
     (let-expr (first (second q))
               (parse (second (second q)))
               (parse (third q)))]
    [(and (list? q) (eq? (length q) 4) (eq? (first q) 'if))
     (if-expr (parse (second q))
              (parse (third q))
              (parse (fourth q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'lambda)) ; <!!!
     (parse-lam (second q) (third q))]
    [(and (list? q) (pair? q) (not (op->proc (car q)))) ; <------- !!!
     (parse-app q)]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]))

(define (parse-app q) ; <----------------------------------------- !!!
  (define (parse-app-accum q acc)
    (cond [(= 1 (length q)) (app acc (parse (car q)))]
          [else (parse-app-accum (cdr q) (app acc (parse (car q))))]))
  (parse-app-accum (cdr q) (parse (car q))))

(define (parse-lam pat e) ; <------------------------------------- !!!
  (cond [(= 1 (length pat))
         (lam (car pat) (parse e))]
        [else
         (lam (car pat) (parse-lam (cdr pat) e))]))

; ---------- ;
; Srodowiska ;
; ---------- ;

(struct environ (xs) #:transparent)

(define env-empty (environ null))
(define (env-add x v env)
  (environ (cons (cons x v) (environ-xs env))))
(define (env-lookup x env)
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))

; --------- ;
; Ewaluacja ;
; --------- ;

(struct clo (id e env) #:transparent) ; <------------------------- !!!

(define (value? v)
  (or (number? v)
      (boolean? v)
      (and (pair? v) (value? (car v)) (value? (cdr v)))
      (null? v)
      (clo? v))) ; <---------------------------------------------- !!!

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /] ['% modulo]
            ['= =] ['> >] ['>= >=] ['< <] ['<= <=]
            ['and (lambda (x y) (and x y))]
            ['or  (lambda (x y) (or  x y))]
            [_ false])) ; <--------------------------------------- !!!

(define (make-lazy e env)
    (match e
    [(const n) (const n)]
    [(binop op l r) (binop op (make-lazy l env) (make-lazy r env))]
    [(let-expr x e1 e2)
     (make-lazy e2 (env-add x (make-lazy e1 env) env))]
    [(var-expr x) (env-lookup x env)]
    [(if-expr eb et ef) (if (make-lazy eb env)
                            (make-lazy et env)
                            (make-lazy ef env))]
    [(cons-expr e1 e2) (cons-expr 
                            (make-lazy e1 env)
                            (make-lazy e2 env))]
    [(car-expr e) (cons-expr-e1 (make-lazy e env))]
    [(cdr-expr e) (cons-expr-e2 (make-lazy e env))]
    [(null-expr) (null-expr)]
    [(null?-expr e) (null?-expr (make-lazy e env))]
    [(lam x e) (clo x e env)] ; <--------------------------------- !!!
    [(app f e) ; <------------------------------------------------ !!!
     (let ([vf (make-lazy f env)]
           [ve (make-lazy e env)])
       (match vf [(clo x body fun-env)
                  (make-lazy body (env-add x ve fun-env))]))]))


(define (eval-env e env)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval-env l env)
                                   (eval-env r env))]
    [(let-expr x e1 e2)
     (eval-env e2 (env-add x (eval-env e1 env) env))]
    [(var-expr x) (env-lookup x env)]
    [(if-expr eb et ef) (if (eval-env eb env)
                            (eval-env et env)
                            (eval-env ef env))]
    [(cons-expr e1 e2) (cons (eval-env e1 env)
                             (eval-env e2 env))]
    [(car-expr e) (car (eval-env e env))]
    [(cdr-expr e) (cdr (eval-env e env))]
    [(null-expr) null]
    [(null?-expr e) (null? (eval-env e env))]
    [(lam x e) (clo x e env)] ; <--------------------------------- !!!
    [(app f e) ; <------------------------------------------------ !!!
     (let ([vf (eval-env f env)]
           [ve (eval-env e env)])
       (match vf [(clo x body fun-env)
                  (eval-env body (env-add x ve fun-env))]))]))

(define (eval e) (eval-env (make-lazy e env-empty) env-empty))

(define program
  '(let [twice (lambda (f x) (f (f x)))]
   (let [inc (lambda (x) (+ 1 x))]
     (twice twice twice twice inc 1))))
    

(define (test-eval) (eval (parse program)))

(eval (parse '((lambda (x) (+ 3 3)) (/ 5 0))))
(eval (parse'(let [if-fun (lambda (b t e) (if b t e))](if-fun  true 4 (/ 5 0)))))
(eval (parse'(car (cons (+ 2 2) (/ 5 0)))))

(eq? 4 (eval(parse '(car (cdr (cons (/ 5 0) (cons (+ 2 2) (/ 5 0))))))))