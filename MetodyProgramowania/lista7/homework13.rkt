#lang racket

(provide (struct-out const) (struct-out binop) (struct-out var-expr) (struct-out let-expr) (struct-out var-dead) find-dead-vars)
; --------- ;
; Wyrazenia ;
; --------- ;

(struct const    (val)      #:transparent)
(struct binop    (op l r)   #:transparent)
(struct var-expr (id)       #:transparent)
(struct var-dead (id)       #:transparent)
(struct let-expr (id e1 e2) #:transparent)

(define (expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r) (and (symbol? op) (expr? l) (expr? r))]
    [(var-expr x) (symbol? x)]
    [(var-dead x) (symbol? x)]
    [(let-expr x e1 e2) (and (symbol? x) (expr? e1) (expr? e2))]
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
            (parse (third q)))]))

; ---------------------------------- ;
; Wyszukaj ostatnie uzycie zmiennych ;
; ---------------------------------- ;

;;po znalezieniu leta wywolujemy funkcje make-dead i tworzymy nowe let-expr z wynikiem tej funkcji  
(define (find-dead-vars e)
  (match e
    [(const n) (const n)]
    [(binop op l r)(binop op (find-dead-vars l)(find-dead-vars r))]
    [(var-expr x) (var-expr x)]
    [(var-dead x) (var-dead x)]
    [(let-expr id e1 e2) (let-expr id (find-dead-vars e1) (find-dead-vars (make-dead e2 id)))]))

;;funkcja ktora po wywolaniu szuka wystapien zmiennej x zaczynajac od prawej strony i zamienia pierwsze znaleziona na martwe 
(define (make-dead e x)
    (match e
      [(const n) (const n)]
      [(binop op l r)
        (let ([r-tree (make-dead r x)])
          (if (is-dead? r-tree x)
            (binop op l r-tree)
            (binop op (make-dead l x) r)))]
      [(var-expr s)
        (if (eq? x s)
          (var-dead x)
          (var-expr s))]
      [(var-dead s)(var-dead s)]
      [(let-expr id e1 e2) 
        (if (eq? id x)
          (let-expr id (make-dead e1 x) e2)
          (let ([e2-tree (make-dead e2 x)])
            (if (is-dead? e2-tree)
              (let-expr id e1 e2-tree)
              (let-expr id (make-dead e1 x) e2))))])) 

;;funckja sprawdza czy zostala utworzona martwa zmienna  
(define (is-dead? e x)
  (match e
    [(const n) #f]
    [(binop op l r)(or (is-dead? r x)(is-dead? l x))]
    [(var-expr s) #f]
    [(var-dead s) (eq? x s)]
    [(let-expr id e1 e2) 
      (if (eq? id x)
        (is-dead? e1 x)
        (or (is-dead? e2 x)(is-dead? e1 x)))]))

(find-dead-vars (let-expr 'x (const  3)(binop '+ (var-expr 'x) (var-expr 'x))))
(find-dead-vars (let-expr 'x (const  3)(binop '+ (var-expr 'x)(let-expr 'x (const  5)(binop '+ (var-expr 'x)(var-expr 'x))))))

