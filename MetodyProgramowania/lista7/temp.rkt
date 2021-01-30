#lang racket
(provide (struct-out const) (struct-out binop) (struct-out var-expr) (struct-out let-expr)
 (struct-out var-dead) find-dead-vars)

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


(define (find-dead-vars e)
     
    (define (find-last x e) ;Wyszukuje ostatnie wystąpienie szukając pierwszego (var-expr x) który jest 
      (match e              ;najbardziej na prawo i zamienia go na (var-dead x)
        [(const a) (const a)]
        [(binop op l r)  (let ([find-r (find-last x r)]) 
                                (if (check find-r x)
                                    (binop op l find-r)
                                    (binop op (find-last x l) r)))]
        [(var-expr a) (if (eq? x a) (var-dead a) (var-expr a))]
        [(var-dead a) (var-dead a)]
        [(let-expr a e1 e2) 
          (if (eq? a x)         ;Sprawdzamy czy nie nastąpiło przesłonięcie
              (let-expr a (find-last x e1) e2)
              (let ([find-e2 (find-last x e2)]) 
                                (if (check find-e2 x)
                                    (let-expr a e1 find-e2)
                                    (let-expr a (find-last x e1) e2))))]))


    (define (check e x) ;Sprawadza czy w danym poddrzewie udało się znaleźć ostatnie wystąpienie x
          (match e
            [(const a) #f]
            [(binop op l r) (or (check r x) (check l x))]
            [(var-dead a) (if (eq? a x) #t #f)]
            [(var-expr a) #f]
            [(let-expr a e1 e2) 
              (if (eq? a x)
                (check e1 x)
                (or (check e2 x) (check e1 x)))]))

          
    (match e
      [(const n) (const n)]
      [(binop op l r) (binop op (find-dead-vars l) (find-dead-vars r))]
      [(var-expr x) (var-expr x)]
      [(var-dead x) (var-dead x)]
      [(let-expr x e1 e2) (let-expr x (find-dead-vars e1) (find-dead-vars (find-last x e2)))]
      [_ false]))
