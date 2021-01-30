#lang racket

;; Składnia abstrakcyjna
(struct const (val)                 #:transparent)
(struct var-expr (name)             #:transparent)
(struct let-expr (id bound body)    #:transparent)
(struct letrec-expr (id bound body) #:transparent)
(struct if-expr  (eb et ef)         #:transparent)
(struct lambda-expr (arg body)      #:transparent)
(struct app-expr (fun arg)          #:transparent)
(struct handle-expr (e1 e2)         #:transparent)

(define (keyword s)
  (member s '(true false null and or if cond else lambda let letrec)))

(define (expr? e)
  (match e
    [(const n)           (or (number? n)
                             (boolean? n)
                             (null? n)
                             (string? n))]
    [(var-expr id)       (symbol? id)]
    [(let-expr x e1 e2 ) (and (symbol? x)
                              (expr? e1)
                              (expr? e2))]
    [(letrec-expr x e1 e2) (and (symbol? x)
                                (expr? e1)
                                (expr? e2))]
    [(if-expr eb et ef)  (and (expr? eb)
                              (expr? et)
                              (expr? ef))]
    [(lambda-expr x e)   (and (symbol? x)
                              (expr? e))]
    [(app-expr ef ea)    (and (expr? ef)
                              (expr? ea))]
    [_                   false]))

;; Parsowanie (zacytowane wyrażenie -> składnia abstrakcyjna)
(define (parse q)
  (cond
    [(number? q)     (const q)]
    [(string? q)     (const q)]
    [(eq? q 'true)   (const true)]
    [(eq? q 'false)  (const false)]
    [(eq? q 'null)   (const null)]
    [(and (symbol? q)
          (not (keyword q)))
     (var-expr q)]
    [(and (list? q)
          (= (length q) 3)
          (eq? (first q) 'let)
          (list? (second q))
          (= (length (second q)) 2)
          (symbol? (first (second q))))
     (let-expr (first (second q))
               (parse (second (second q)))
               (parse (third q)))]
    [(and (list? q)
          (= (length q) 3)
          (eq? (first q) 'letrec)
          (list? (second q))
          (= (length (second q)) 2)
          (symbol? (first (second q))))
     (letrec-expr (first (second q))
                  (parse (second (second q)))
                  (parse (third q)))]
    [(and (list? q) 
          (= (length q) 3)
          (eq? (first q) 'handle))
      (handle-expr (parse (second q)) (parse (third q)))]
    [(and (list? q)
          (= (length q) 4)
          (eq? (first q) 'if))
     (if-expr (parse (second q))
              (parse (third q))
              (parse (fourth q)))]
    [(and (list? q)
          (pair? q)
          (eq? (first q) 'and))
     (desugar-and (map parse (cdr q)))]
    [(and (list? q)
          (pair? q)
          (eq? (first q) 'or))
     (desugar-or (map parse (cdr q)))]
    [(and (list? q)
          (>= (length q) 2)
          (eq? (first q) 'cond))
     (parse-cond (cdr q))]
    [(and (list? q)
          (= (length q) 3)
          (eq? (first q) 'lambda)
          (list? (second q))
          (andmap symbol? (second q))
          (cons? (second q)))
     (desugar-lambda (second q) (parse (third q)))]
    [(and (list? q)
          (>= (length q) 2))
     (desugar-app (parse (first q)) (map parse (cdr q)))]
    [else (error "Unrecognized token:" q)]))

(define (parse-cond qs)
  (match qs
    [(list (list 'else q))
     (parse q)]

    [(list (list q _))
     (error "Expected 'else' in last branch but found:" q)]

    [(cons (list qb qt) qs)
     (if-expr (parse qb) (parse qt) (parse-cond qs))]))

(define (desugar-and es)
  (if (null? es)
      (const true)
      (if-expr (car es) (desugar-and (cdr es)) (const false))))

(define (desugar-or es)
  (if (null? es)
      (const false)
      (if-expr (car es) (const true) (desugar-or (cdr es)))))

(define (desugar-lambda xs e)
  (if (null? xs)
      e
      (lambda-expr (car xs) (desugar-lambda (cdr xs) e))))

(define (desugar-app e es)
  (if (null? es)
      e
      (desugar-app (app-expr e (car es)) (cdr es))))

;; Środowiska
(struct blackhole ())
(struct environ (xs))

(define env-empty (environ null))
(define (env-add x v env)
  (environ (cons (mcons x v) (environ-xs env))))
(define (env-lookup x env)
  (define (assoc-lookup xs)
    (cond [(null? xs)
           (error "Unknown identifier" x)]
          [(eq? x (mcar (car xs)))
           (let ((v (mcdr (car xs))))
             (if (blackhole? v)
                 (error "Jumped into blackhole at" x)
                 v))]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))
(define (env-update! x v env)
  (define (assoc-update xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (mcar (car xs)))
           (set-mcdr! (car xs) v)]
          [else (assoc-update (cdr xs))]))
  (assoc-update (environ-xs env)))

;; Domknięcia
(struct clo (arg body env))

;; Procedury wbudowane, gdzie
;; proc — Racketowa procedura którą należy uruchomić
;; args — lista dotychczas dostarczonych argumentów
;; pnum — liczba brakujących argumentów (> 0)
;; W ten sposób pozwalamy na częściową aplikację Racketowych procedur
;; — zauważmy że zawsze znamy pnum, bo w naszym języku arność
;; procedury jest ustalona z góry
(struct builtin (proc args pnum))

;; Pomocnicze konstruktory procedur unarnych i binarnych
(define (builtin/1 p)
  (builtin p null 1))
(define (builtin/2 p)
  (builtin p null 2))

;; Procedury
(define (proc? v)
  (or (and (clo? v)
           (symbol?  (clo-arg v))
           (expr?    (clo-body v))
           (environ? (clo-env v)))
      (and (builtin? v)
           (procedure? (builtin-proc v))
           (andmap value? (builtin-args v))
           (natural? (builtin-pnum v))
           (> (builtin-pnum v) 0))))

;; Definicja typu wartości
(define (value? v)
  (or (number? v)
      (boolean? v)
      (null? v)
      (string? v)
      (and (cons? v)
           (value? (car v))
           (value? (cdr v)))
      (proc? v)))

;; Runtime error
(struct runtime-error (reason) #:transparent)

(define (let-error c k)
  (if (runtime-error? c) c (k c)))

;; Środowisko początkowe (przypisujące procedury wbudowane ich nazwom)

(define start-env
  (foldl (lambda (p env) (env-add (first p) (second p) env))
         env-empty
         `((+        ,(builtin/2 +))
           (-        ,(builtin/2 -))
           (*        ,(builtin/2 *))
           (/        ,(builtin/2 /))
           (~        ,(builtin/1 -))
           (<        ,(builtin/2 <))
           (>        ,(builtin/2 >))
           (=        ,(builtin/2 =))
           (<=       ,(builtin/2 <=))
           (>=       ,(builtin/2 >=))
           (not      ,(builtin/1 not))
           (cons     ,(builtin/2 cons))
           (car      ,(builtin/1 car))
           (cdr      ,(builtin/1 cdr))
           (pair?    ,(builtin/1 cons?))
           (null?    ,(builtin/1 null?))
           (boolean? ,(builtin/1 boolean?))
           (number?  ,(builtin/1 number?))
           (procedure? ,(builtin/1 (lambda (x) (or (clo? x) (builtin? x)))))
           (string?  ,(builtin/1 string?))
           (string-= ,(builtin/2 string=?))
           (error    ,(builtin/1 runtime-error))
           ;; and so on, and so on
           )))

;; Ewaluator
;; -- zwraca wartość lub runtime error
(define (eval-env e env)
  (match e
    [(const n)
     n]

    [(var-expr x)
     (env-lookup x env)]

    [(let-expr x e1 e2)
     (let-error (eval-env e1 env) (lambda (v1)
           (eval-env e2 (env-add x v1 env))))]

    [(letrec-expr f ef eb)
     (let ((new-env (env-add f (blackhole) env)))
       (let-error (eval-env ef new-env)
         (lambda (vf) (env-update! f vf new-env)
                      (eval-env eb new-env))))]
    [(handle-expr e f)
      (let-error (eval-env e env) (lambda (x) (eval-env f env)))]
    [(if-expr eb et ef)
     (let-error (eval-env eb env)
       (lambda (vb)
         (match vb
           [#t (eval-env et env)]
           [#f (eval-env ef env)]
           [v  (error "Not a boolean:" v)])))]
    [(lambda-expr x e)
     (clo x e env)]

    [(app-expr ef ea)
     (let-error (eval-env ef env) (lambda (vf)
     (let-error (eval-env ea env) (lambda (va)
       (match vf
         [(clo x e env)
          (eval-env e (env-add x va env))]
         [(builtin p args nm)
          (if (= nm 1)
              (apply p (reverse (cons va args)))
              (builtin p (cons va args) (- nm 1)))]
         [_ (error "Not a function:" vf)])))))]))

(define (eval e)
  (eval-env e start-env))


;; REPL — interpreter interaktywny (read-eval-print loop)

;; dodajemy składnię na wiązanie zmiennych "na poziomie interpretera"
;; i komendę wyjścia "exit" ...
(struct letrec-repl (id expr))
(struct let-repl (id expr))
(struct exit-repl ())

;; ... a także rozszerzoną procedurę parsującą te dodatkowe komendy i
;; prostą obsługę błędów
(define (parse-repl q)
  (with-handlers
      ([exn? (lambda (exn)
               (display "Parse error! ")
               (displayln (exn-message exn)))])
    (cond
      [(eq? q 'exit)   (exit-repl)]
      [(and (list? q)
            (= 3 (length q))
            (eq? (first q) 'let))
       (let-repl (second q) (parse (third q)))]
      [(and (list? q)
            (= 3 (length q))
            (eq? (first q) 'letrec))
       (letrec-repl (second q) (parse (third q)))]
      [else (parse q)])))

;; trochę zamieszania w procedurze eval-repl wynika z rudymentarnej
;; obsługi błędów: nie chcemy żeby błąd w interpretowanym programie
;; kończył działanie całego interpretera!
(define (eval-repl c env continue)
  (define (eval-with-err e env)
    (with-handlers
        ([exn? (lambda (exn)
                 (display "Error! ")
                 (displayln (exn-message exn)))])
      (eval-env e env)))
  (match c
    [(exit-repl)
     (void)]

    [(let-repl x e)
     (let ((v (eval-with-err e env)))
       (if (void? v)
           (continue env)
           (continue (env-add x v env))))]

    [(letrec-repl f e)
     (let* ((new-env (env-add f (blackhole) env))
            (v       (eval-with-err e new-env)))
       (if (void? v)
           (continue env)
           (begin
             (env-update! f v new-env)
             (continue new-env))))]

    [_
     (let ((v (eval-with-err c env)))
       (unless (void? v)
         (displayln v))
       (continue env))]))

;; I w końcu interaktywny interpreter
(define (repl)
  (define (go env)
    (display "FUN > ")
    (let* ((q (read))
           (c (parse-repl q)))
      (if (void? c)
          (go env)
          (eval-repl c env go))))
  (displayln "Welcome to the FUN functional language interpreter!")
  (go start-env))


;;;;;;1

(define (fact n)
  (if (= n 1)
    n
    (* n (fact (- n 1)))))


(define fact-eval  
  '(letrec [factx (lambda (x) 
      (if (= x 1)
        x
        (* x (factx (- x 1)))))] (factx 9000)))


;(begin (display "liczenie silni z 90 przez racketa : ") (time (fact 9000)))
;(begin (display "liczenie silni z 90 przez eval i parse : ")(time (eval(parse fact-eval))))


;;; na przykladzie testu powyzej mozemy stwierdzic ze nasz jezyk jest wolniejszy o ~ 20%


;;;;;;2 ~ nie czaje tego totalnie 

; (define x 12)
; (define-syntax m (syntax-rules () [(_ id) (let ([x 10]) id)]))

; (m (fact 5))

;;;;;;3 ~ to dziala ale nie chce mi sie zmieniac wszytskich error w eval-env

(eval(parse '(handle (if (+ 21 2) 1 2) 1)))