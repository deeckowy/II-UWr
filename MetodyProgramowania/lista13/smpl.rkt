#lang typed/racket

; wykład 8 plik boolean.rkt

; --------- ;
; Wyrazenia ;
; --------- ;

(define-type Value  (U Real Boolean))
(define-predicate value? Value)
(define-type Expr   (U const binop var-expr let-expr if-expr))
(define-predicate expr? Expr)
(define-type Op     (U '+ '- '* '/ '= '> '>= '< '<= 'and 'or))
(define-predicate op? Op)
(struct const    ([val : Value])                            #:transparent)
(struct binop    ([op : Op] [l : Expr] [r : Expr])          #:transparent)
(struct var-expr ([id : Symbol])                            #:transparent)
(struct let-expr ([id : Symbol] [e1 : Expr] [e2 : Expr])    #:transparent)
(struct if-expr  ([eb : Expr] [et : Expr] [ef : Expr])      #:transparent)

(: parse (-> Any Expr))
(define (parse q)
  (match q
    [(? real? n) (const n)]
    ['true (const true)]
    ['false (const false)]
    [(? symbol? s) (var-expr s)]
    [(list (? symbol? 'let) (list (? symbol? x) expr) body)
      (let-expr x (parse expr) (parse body))]
    [(list 'if pred ifTrue ifFalse)
          (if-expr (parse pred) (parse ifTrue) (parse ifFalse))]
    [(list (? op? op) l r) (binop op (parse l) (parse r))]))

(: test-parse (-> Expr))
(define (test-parse) (parse '(let [x (+ 2 2)] (+ x 1))))

; ---------- ;
; Srodowiska ;
; ---------- ;

(define-type Env environ)
(struct environ ([xs : (Listof (Pairof Symbol Value))]))

(: env-empty Env)
(define env-empty (environ null))

(: env-add (-> Symbol Value Env Env))
(define (env-add x v env)
  (environ (cons (cons x v) (environ-xs env))))
(: env-lookup (-> Symbol Env Value))
(define (env-lookup x env)
  (: assoc-lookup (-> (Listof (Pairof Symbol Value)) Value))
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))

; --------- ;
; Ewaluacja ;
; --------- ;

(: wrap-op-real (-> (-> Real Real Real) (-> Value Value Value)))
(define (wrap-op-real op)
  (lambda (x y)
    (cond
      [(and (real? x) (real? y)) (op x y)]
      [(and (real? x) (boolean? y)) (op x (if y 1 0))]
      [(and (boolean? x) (real? y)) (op (if x 1 0) y)]
      [(and (boolean? x) (boolean? y)) (op (if x 1 0) (if y 1 0))])))

(: wrap-op-bool (-> (-> Real Real Boolean) (-> Value Value Value)))
(define (wrap-op-bool op)
  (lambda (x y)
    (cond
      [(and (real? x) (real? y)) (op x y)]
      [(and (real? x) (boolean? y)) (op x (if y 1 0))]
      [(and (boolean? x) (real? y)) (op (if x 1 0) y)]
      [(and (boolean? x) (boolean? y)) (op (if x 1 0) (if y 1 0))])))

(: wrap-op-int (-> (-> Integer Integer Boolean) (-> Value Value Value)))
(define (wrap-op-int op)
  (lambda (x y)
    (cond
      [(and (real? x) (real? y)) (op (exact-round x) (exact-round y))]
      [(and (real? x) (boolean? y)) (op  (exact-round x) (if y 1 0))]
      [(and (boolean? x) (real? y)) (op (if x 1 0)  (exact-round y))]
      [(and (boolean? x) (boolean? y)) (op (if x 1 0) (if y 1 0))])))

; Usunęliśmy modulo.
(: op->proc (-> Op (-> Value Value Value)))
(define (op->proc op)
  (match op ['+ (wrap-op-real +)] ['- (wrap-op-real -)] ['* (wrap-op-real *)] ['/ (wrap-op-real /)]
            ['= (wrap-op-bool =)] ['> (wrap-op-bool >)] ['>= (wrap-op-bool >=)] ['< (wrap-op-bool <)] 
            ['% (wrap-op-int modulo)]
            ['<= (wrap-op-bool <=)]
            ['and (lambda (x y) (and x y))]
            ['or  (lambda (x y) (or  x y))]))

(: eval-env (-> Expr Env Value))
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
                            (eval-env ef env))]))

(: eval (-> Expr Value))
(define (eval e) (eval-env e env-empty))

(: program Any)
(define program
  '(if (or (< (- 5 3) 5)
           true)
       (+ 2 3)
       (/ 2 0)))

(: test-eval (-> Value))
(define (test-eval) (eval (parse program)))

(parse '(if 2 3 +))