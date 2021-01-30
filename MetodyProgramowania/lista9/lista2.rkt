
#lang racket

; Do fun.rkt dodajemy rekurencyjne let-y
;
; Miejsca, ktore sie zmienily oznaczone sa przez !!!

; --------- ;
; Wyrazenia ;
; --------- ;

(struct const       (val)           #:transparent)
(struct binop       (op l r)        #:transparent)
(struct var-expr    (id)            #:transparent)
(struct let-expr    (id e1 e2)      #:transparent)
(struct string (s)                  #:transparent)
(struct letrec-expr (id e1 e2)      #:transparent) ; <----------------- !!!
(struct if-expr     (eb et ef)      #:transparent)
(struct cons-expr   (e1 e2)         #:transparent)
(struct car-expr    (e)             #:transparent)
(struct cdr-expr    (e)             #:transparent)
(struct null-expr   ()              #:transparent)
(struct null?-expr  (e)             #:transparent)
(struct app         (f e)           #:transparent)
(struct lam         (id e)          #:transparent)
(struct map-expr    (p e)           #:transparent)
(struct filter-expr (p l)           #:transparent)
(struct append-expr (l1 l2)         #:transparent)
(struct const?-expr (c)             #:transparent)
(struct dis-expr    (d)             #:transparent)
(struct begin-expr  (e1 e2 e3 e4)   #:transparent)
(struct read-expr   ()              #:transparent)

(define (expr? e)
  (match e
    [(const n) (or (number? n) (boolean? n))]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(let-expr x e1 e2)
     (and (symbol? x) (expr? e1) (expr? e2))]
    [(letrec-expr x e1 e2) ; <------------------------------------ !!!
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
    [(eq? q 'read)  (read-expr)]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'letrec*))
      (let-parse (second q) (third q))]
    [(and (list? q) (eq? (length q) 2) (eq? (first q) 'display))
      (dis-expr (parse (second q)))]
    [(and (list? q) (eq? (length q) 5) (eq? (first q) 'begin))
      (begin-expr
        (parse (second q))
        (parse (third q))
        (parse (fourth q))
        (parse (fifth q)))]
    [(and (list? q) (eq? (length q) 2) (eq? (first q) 'const?))
        (const?-expr (parse (second q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'map))
        (map-expr (parse (second q)) (parse (third q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'filter))
        (filter-expr (parse (second q)) (parse (third q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'append))
        (append-expr (parse (second q)) (parse (third q)))]
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
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'letrec)) ; <!!!
     (letrec-expr (first (second q))
                  (parse (second (second q)))
                  (parse (third q)))]
    [(and (list? q) (eq? (length q) 4) (eq? (first q) 'if))
     (if-expr (parse (second q))
              (parse (third q))
              (parse (fourth q)))]
    [(and (list? q) (eq? (length q) 3) (eq? (first q) 'lambda))
     (parse-lam (second q) (third q))]
    [(and (list? q) (eq? (length q) 2) (eq? (first q) 'quote)) (string q)]
    [(and (list? q) (pair? q) (not (op->proc (car q))))
     (parse-app q)]
    [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
     (binop (first q)
            (parse (second q))
            (parse (third q)))]))

(define (let-parse l e)
  (let* ([sel (car l)]
         [par (lambda (x) (parse x))])
    (if (eq? 1 (length l))
      (let-expr (car sel) (par (first (cdr sel))) (par e))
      (let-expr (car sel) (par (first (cdr sel))) (let-parse (cdr l) e)))))

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

(struct blackhole () #:transparent) ; <------------------------- !!!
(struct environ (xs) #:transparent)

(define env-empty (environ null))
(define (env-add x v env)
  (environ (cons (mcons x v) (environ-xs env)))) ; <-------------- !!!
(define (env-lookup x env)
  (define (assoc-lookup xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (mcar (car xs))) ; <---------------------------- !!!
             (match (mcdr (car xs))
               [(blackhole) (error "Stuck forever in a black hole!")]
               [x x])]
          [else (assoc-lookup (cdr xs))]))
  (assoc-lookup (environ-xs env)))
(define (env-update! x v xs) ; <---------------------------------- !!!
  (define (assoc-update! xs)
    (cond [(null? xs) (error "Unknown identifier" x)]
          [(eq? x (mcar (car xs))) (set-mcdr! (car xs) v)]
          [else (env-update! x v (cdr xs))]))
  (assoc-update! (environ-xs xs)))

; --------- ;
; Ewaluacja ;
; --------- ;

(struct clo (id e env) #:transparent)

(define (value? v)
  (or (number? v)
      (boolean? v)
      (and (pair? v) (value? (car v)) (value? (cdr v)))
      (null? v)
      (clo? v)
      (blackhole? v))) ; <---------------------------------------- !!!

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /] ['% modulo]
            ['= =] ['> >] ['>= >=] ['< <] ['<= <=]
            ['and (lambda (x y) (and x y))]
            ['or  (lambda (x y) (or  x y))]
            [_ false]))

(define (eval-env e env)
  (match e
    [(const n) n]
    [(const?-expr c) (const? (eval-env c env))]
    [(binop op l r) ((op->proc op) (eval-env l env)
                                   (eval-env r env))]
    [(let-expr x e1 e2)
     (eval-env e2 (env-add x (eval-env e1 env) env))]
    [(letrec-expr x e1 e2) ; <------------------------------------ !!!
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
    [(begin-expr e1 e2 e3 e4)
      (let ([ev (lambda (x) (eval-env x env))])
        (begin (begin (ev e1) (ev e2) (ev e3)) (ev e4)))]
    [(read-expr) (read)]
    [(dis-expr d) (display (eval-env d env))]
    [(map-expr p l)(map-eval p l env)]
    [(filter-expr p l) (filter-eval p l env)]
    [(append-expr e1 e2) (list (append-eval e1 env)(append-eval e2 env))]
    [(string x)  x]
    [(null?-expr e) (null? (eval-env e env))]
    [(lam x e) (clo x e env)]
    [(app f e)
     (let ([vf (eval-env f env)]
           [ve (eval-env e env)])
       (match vf [(clo x body fun-env)
                  (eval-env body (env-add x ve fun-env))]))]))

(define (eval e) (eval-env e env-empty))

(define (filter-eval p l env)
    (match l
        [(cons-expr e1 e2)
            (let ([fil (filter-eval p e2 env)])
                (if (eval-env (app p e1) env)
                    (cons (const-val e1) fil)
                    fil))]
        [else
            (if (eval-env (app p l) env)
                (eval-env l env)
                null)]))

(define (append-eval e1 env)
    (match e1
        [(cons-expr e1 e2)
            (cons (eval-env e1 env) (append-eval e2 env))]
        [else (eval-env e1 env)]))

(define (map-eval p l env)
    (match l
        [(cons-expr e1 e2)
            (cons (eval-env (app p e1) env) (map-eval p e2 env))]
        [else (eval-env (app p l) env)]))

(define program
  '(letrec
     [fact (lambda (n) (if (= n 0) 1 (* n (fact (- n 1)))))]
   (letrec
     [even-odd
       (cons
         (lambda (x)
           (if (= x 0) true  ((cdr even-odd) (- x 1))))
         (lambda (x)
           (if (= x 0) false ((car even-odd) (- x 1)))))]
   (let [even (car even-odd)]
   (let [odd  (cdr even-odd)]
   (even (fact 6)))))))

(define PROGRAM
  '(letrec [from-to (lambda (n k)
                      (if (> n k)
                          null
                          (cons n (from-to (+ n 1) k))))]
   (letrec [sum (lambda (xs)
                  (if (null? xs)
                      0
                      (+ (car xs) (sum (cdr xs)))))]
   (sum (from-to 1 36)))))

(define (test-eval) (eval (parse PROGRAM)))


;;;;;;;5

(define lisst '(cons 1 (cons 2 (cons 3 (cons 4 (cons 5 null))))))

;;(eval (parse '(append (cons 1 2) (cons 3 4))))
;(eval (parse '(map (lambda (x) (+ x 1)) (cons 1 (cons 2 (cons 3 (cons 4 (cons 5 6))))))))
;(eval (parse '(filter (lambda (x) (> x 0)) (cons 1 (cons 2 3)))))

(eval (parse '(lambda (x) (+ x 1))))



;;;;;6
(define insertion-sort ;;to nie dziala 
  '(letrec [insert (lambda (l n)
                      (if (const? l)
                        (cons l null)
                        (if (<= n (car l))
                          (cons n l)
                          (cons (car l) (insert (cdr l) n)))))]
                            (letrec [sort (lambda (l)
                                            (if (const? l)
                                              l
                                              (insert (sort (cdr l) (car l)))))]
                              (sort (cons 1 (cons 2 (cons 3 (cons 4 5))))))))

(define (sort l)
  (define (insert l n)
    (cond
      [(null? l) (cons n null)]
      [(<= n (car l)) (cons n l)]
      [else (cons (car l) (insert (cdr l) n))]))

  (if (null? l)
    l
    (insert (sort (cdr l))(car l))))


;;(sort '(8 7 3 1))
;;(eval (parse insertion-sort))


;;;;;;7


;;(display 'x)

;;(eval (parse '(+ 1 read)))

;;(eval (parse '(begin (+ 2 1) (+ 4 4) 3 4)))

(define tes '(letrec [rrrr (lambda (x)
    (if (= x 0)
      x
      (begin 1 2 (display x) (rrrr read))))] (rrrr 2)))

;;(eval (parse tes))

;;;;;;;8 dziala pienknie 

(define ss '(let (x (+ 2 1)) x))
(define sample8 '(letrec* ([x (+ 1 2)][y (+ 3 4)]) (+ x y)))


(eval (parse ss))
(eval (parse sample8))