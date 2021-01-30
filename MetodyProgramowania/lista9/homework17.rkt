#lang racket

; Do programming.rkt dodajemy instrukcje

(provide eval-while parse-while env-empty env-lookup)

; --------- ;
; Wyrazenia ;
; --------- ;

(struct const       (val)      #:transparent)
(struct binop       (op l r)   #:transparent)
(struct var-expr    (id)       #:transparent)
(struct let-expr    (id e1 e2) #:transparent)
(struct letrec-expr (id e1 e2) #:transparent)
(struct if-expr     (eb et ef) #:transparent)
(struct cons-expr   (e1 e2)    #:transparent)
(struct car-expr    (e)        #:transparent)
(struct cdr-expr    (e)        #:transparent)
(struct null-expr   ()         #:transparent)
(struct null?-expr  (e)        #:transparent)
(struct app         (f e)      #:transparent)
(struct lam         (id e)     #:transparent)

(define (expr? e)
  (match e
    [(const n) (or (number? n) (boolean? n) (string? n))]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(let-expr x e1 e2)
     (and (symbol? x) (expr? e1) (expr? e2))]
    [(letrec-expr x e1 e2)
     (and (symbol? x) (expr? e1) (expr? e2))]
    [(if-expr eb et ef)
     (and (expr? eb) (expr? et) (expr? ef))]
    [(cons-expr e1 e2) (and (expr? e1) (expr? e2))]
    [(car-expr e) (expr? e)]
    [(cdr-expr e) (expr? e)]
    [(null-expr) true]
    [(null?-expr e) (expr? e)]
    [(app f e) (and (expr? f) (expr? e))]
    [(lam id e) (and (symbol? id) (expr? e))]
    [_ false]))

(define (parse q)
  (cond
    [(number? q) (const q)]
    [(eq? q 'true)  (const true)]
    [(eq? q 'false) (const false)]
    [(eq? q 'null)  (null-expr)]
    [(string? q) (const q)]
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
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'letrec))
     (letrec-expr (first (second q))
                  (parse (second (second q)))
                  (parse (third q)))]
    [(and (list? q) (eq? (length q) 4) (eq? (first q) 'if))
     (if-expr (parse (second q))
              (parse (third q))
              (parse (fourth q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'lambda))
     (parse-lam (second q) (third q))]
    [(and (list? q) (pair? q) (not (op->proc (car q))))
     (parse-app q)]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]))

(define (parse-app q)
  (define (parse-app-accum q acc)
    (cond [(= 1 (length q)) (app acc (parse (car q)))]
          [else (parse-app-accum (cdr q) (app acc (parse (car q))))]))
  (parse-app-accum (cdr q) (parse (car q))))

(define (parse-lam pat e)
  (cond [(= 1 (length pat))
         (lam (car pat) (parse e))]
        [else
         (lam (car pat) (parse-lam (cdr pat) e))]))

; ---------- ;
; Srodowiska ;
; ---------- ;

(struct blackhole () #:transparent)
(struct environ (xs) #:transparent)

(define env-empty (environ null))
(define (env-add x v env)
  (environ (cons (mcons x v) (environ-xs env))))
(define (env-lookup x env)
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (mcar (car xs)))
             (match (mcdr (car xs))
               [(blackhole) (error "Stuck forever in a black hole!")]
               [x x])]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))
(define (env-update! x v xs)
  (define (assoc-update! xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (mcar (car xs))) (set-mcdr! (car xs) v)]
          [else (env-update! x v (cdr xs))]))
  (assoc-update! (environ-xs xs)))
(define (env-update x v xs) ; <---------------------------------- !!!
  (define (assoc-update xs)
    (cond [(null? xs) (list (mcons x v))]
          [(eq? x (mcar (car xs))) (cons (mcons x v) (cdr xs))]
          [else (cons (car xs) (assoc-update (cdr xs)))]))
  (environ (assoc-update (environ-xs xs))))

; --------- ;
; Ewaluacja ;
; --------- ;

(struct clo (id e env) #:transparent)

(define (value? v)
  (or (number? v)
      (boolean? v)
      (string? v)
      (and (pair? v) (value? (car v)) (value? (cdr v)))
      (null? v)
      (clo? v)
      (blackhole? v)))

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /] ['% modulo]
            ['= =] ['> >] ['>= >=] ['< <] ['<= <=]
            ['and (lambda (x y) (and x y))]
            ['or  (lambda (x y) (or  x y))]
            ['eq? eq?]
            [_ false]))

(define (eval-env e env)
  (match e
    [(const n) n]
    [(binop op l r) ((op->proc op) (eval-env l env)
                                   (eval-env r env))]
    [(let-expr x e1 e2)
     (eval-env e2 (env-add x (eval-env e1 env) env))]
    [(letrec-expr x e1 e2)
     (let* ([new-env (env-add x (blackhole) env)]
            [v (eval-env e1 new-env)])
       (begin
          (env-update! x v new-env)
          (eval-env e2 new-env)))]
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
    [(lam x e) (clo x e env)]
    [(app f e)
     (let ([vf (eval-env f env)]
           [ve (eval-env e env)])
       (match vf [(clo x body fun-env)
                  (eval-env body (env-add x ve fun-env))]))]))

(define (eval e) (eval-env e env-empty))

; ---------------------------------------------------------------- !!!

(struct skip   ()         #:transparent)
(struct assign (x e)      #:transparent)
(struct if-cmd (eb ct cf) #:transparent)
(struct while  (eb cb)    #:transparent)
(struct comp   (c1 c2)    #:transparent)

(define (cmd? c)
  (match c
    [(skip) true]
    [(assign x e) (and (symbol? x) (expr? e))]
    [(if-cmd eb ct cf) (and (expr? eb) (cmd? ct) (cmd? cf))]
    [(while eb ct) (and (expr? eb) (cmd? ct))]
    [else false]))

(define (parse-while q)
  (cond
    [(eq? q 'skip) (skip)]
    [(null? q) (skip)]
    [(and (list? q) (= (length q) 3) (eq? (second q) ':=))
     (assign (first q)
             (parse (third q)))]
    [(and (list? q) (= (length q) 4) (eq? (car q) 'if))
     (if-cmd (parse (second q))
             (parse-while (third q))
             (parse-while (fourth q)))]
     [(and (list? q) (= (length q) 3) (eq? (car q) 'while))
      (while (parse (second q))
             (parse-while (third q)))]
     [(and (list? q) (= (length q) 2))
      (comp (parse-while (first q))
            (parse-while (second q)))]
     [(and (list? q) (> (length q) 2))
      (comp (parse-while (first q))
            (parse-while (cdr q)))]
     [else (error "while parse error")]))

(define (eval-while e env)
  (match e
    [(skip) env]
    [(assign x e)
        (let ([en (env-update x (eval-env e env) env)])
            (begin (env-sync (environ-xs en) (environ-xs en)) en))]
    [(if-cmd eb ct cf)
     (if (eval-env eb env)
         (eval-while ct env)
         (eval-while cf env))]
    [(while eb cb)
     (if (eval-env eb env)
         (eval-while e (eval-while cb env))
         env)]
     [(comp c1 c2) (eval-while c2 (eval-while c1 env))]))

(define (env-sync l x)
    (define (sync-iter l e)
        (if (null? l)
            (environ (reverse (environ-xs e)))
            (sync-iter (cdr l) (env-update! (mcar (car l)) (mcdr (car l)) e))))
  (if (null? l)
      null
      (begin 
        (match (mcdr (car l))
          [(clo id e env)(set-mcdr! (mcdr (car l)) (clo id e (sync-iter x (environ (reverse (environ-xs env))))))]    
          [else null]) (env-sync (cdr l) x))))
; zakladamy, ze program startuje z pamiecia w ktorej
; aktwna jest zmienna t
(define WHILE_FACT
  '{(i := 1)
    (while (> t 0)
      {(i := (* i t))
       (t := (- t 1))})})

(define (fact n)
  (let* ([init-env  (env-add 't n env-empty)]
         [final-env
           (eval-while (parse-while WHILE_FACT) init-env)])
    (env-lookup 'i final-env)))
    
(define sample 
    '{
        (x := 5)
        (f := (lambda (y) (+ x y)))
        (x := 10)
       (z := (f 0))
    })

(define sample2 
    '{
        (x := 5)
        (f := (let [x 50]
              (let [foo (lambda (y) (+ x y))]
              (let [x 100]
              foo))))
        (x := 10)
        (z := (f 0))
    })

(define sample3 
  '{(x := 5)(f := (let [x 50] (lambda (y) (+ x y))))(x := 10)(z := (f 0))})

(define sample4 
  '{(x := 5)(f := (let [x x] (lambda (y) (+ x y))))(x := 10)(z := (f 0))})

(env-lookup 'z (eval-while (parse-while sample) env-empty))
(env-lookup 'z (eval-while (parse-while sample2) env-empty))
(env-lookup 'z (eval-while (parse-while sample3) env-empty))
(env-lookup 'z (eval-while (parse-while sample4) env-empty))

(eval-while (parse-while sample3) env-empty)
