#lang typed/racket

(provide parse typecheck)

; Miejsca, ktore sie zmienily oznaczone sa przez !!!

; --------- ;
; Wyrazenia ;
; --------- ;


;;ponizsze typy utworzylismy dla wygody uzycia w typecheck (nizej zrobimy z nich predykaty)
(define-type Log-Op   (U 'or 'and))
(define-type Arith-Op (U '+ '- '/ '* '%))
(define-type Comp-Op  (U '= '>= '<= '< '>))


;;;definiujemy typy dla elementow skladowych struktur
(define-type Value (U Real Boolean))
(define-type EType (U 'real 'boolean))
(define-type Op (U Log-Op Arith-Op Comp-Op))
(define-type Expr (U const binop var-expr let-expr if-expr))
;;;dodajemy typy dla elemntow struktur
(struct const    ([val : Value])                     #:transparent)
(struct binop    ([op : Op] [l : Expr] [r : Expr])       #:transparent)
(struct var-expr ([id : Symbol])                       #:transparent)
(struct let-expr ([id : Symbol] [e1 : Expr] [e2 : Expr]) #:transparent)
(struct if-expr  ([eb : Expr] [et : Expr] [ef : Expr])   #:transparent) 


(define-predicate value? Value)
(define-predicate op? Op)

(: parse (-> Any Expr))
(define (parse q)
  (match q
    [(? value? q) (const q)]
    ['true (const #t)]
    ['false (const #f)]
    [(? symbol? q) (var-expr q)]
    [(list (? symbol? 'let) (list (? symbol? x) e1) e2)
        (let-expr x (parse e1) (parse e2))]
    [(list (? symbol? 'if) eb et ef) 
        (if-expr (parse eb) (parse et) (parse ef))]
    [(list (? op? op) l r)
        (binop op (parse l) (parse r))]
    [_ (error "Bad syntax" q)]))

(define (test-parse) (parse '(if (= 2 1) #t #f )))
(test-parse)
; ---------- ;
; Srodowiska ;
; ---------- ;
;;od teraz srodowiska beda lista par (zmienna . typ wartosci)
;;nie zmieniamy nic w implementacji ~ dodamy tylko typy


(struct environ ([xs : (Listof (Pairof Symbol (U EType #f)))]))
(define-type Env environ)

(: env-empty Env)
(define env-empty (environ null))

(: env-add (-> Symbol (U EType #f) Env Env))
(define (env-add x v env)
  (environ (cons (cons x v) (environ-xs env))))

(: env-lookup (-> Symbol Env (U EType #f)))
(define (env-lookup x env)

(: assoc-lookup (-> (Listof (Pairof Symbol (U EType #f))) (U EType #f)))
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (car (car xs))) (cdr (car xs))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))


;;tworzymy predykaty dla wygody i czytelnosci kodu
(define-predicate log-op? Log-Op)
(define-predicate comp-op? Comp-Op)
(define-predicate ari-op? Arith-Op)


(: typecheck (-> Expr (U EType #f)))
(define (typecheck e)
    
    (: tc-iter (-> Expr Env (U EType #f)))
    (define (tc-iter ex env)
        (match ex
            [(const n) (if (real? n) 'real 'boolean)]
            [(var-expr x) (env-lookup x env)]
            [(let-expr x e1 e2)
                (let ([new-env (env-add x (tc-iter e1 env) env)])
                    (tc-iter e2 new-env))]
            [(if-expr eb et ef)
                (if (eq? 'boolean (tc-iter eb env))
                    (if (eq? (tc-iter et env) (tc-iter ef env))
                        (tc-iter et env)
                        #f)
                    #f)]
            [(binop op l r)
                (let* (
                    [lt (tc-iter l env)]
                    [rt (tc-iter r env)])
                        (if (eq? lt rt)
                            (cond 
                                [(and (log-op? op) (eq? lt 'boolean)) 'boolean]
                                [(and (comp-op? op) (eq? lt 'real)) 'boolean]
                                [(and (ari-op? op) (eq? lt 'real)) 'real]
                                [else #f])
                            #f))]))
    
    (tc-iter e env-empty))


(define test (typecheck (test-parse)))
test

(: program Any)
(define program
  '(if (or (< (- 5 3) 5)
           true)
       (+ 2 3)
       (/ 2 0)))

(typecheck (parse program))