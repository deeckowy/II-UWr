#lang racket


(provide (struct-out const) (struct-out binop) rpn->arith)

;; -------------------------------
;; Wyrazenia w odwr. not. polskiej
;; -------------------------------

(define (rpn-expr? e)
  (and (list? e)
       (pair? e)
       (andmap (lambda (x) (or (number? x) (member x '(+ - * /))))
               e)))

;; ----------------------
;; Wyrazenia arytmetyczne
;; ----------------------

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (arith-expr? e)
  (match e
    [(const n) (number? n)]
    [(binop op l r)
     (and (symbol? op) (arith-expr? l) (arith-expr? r))]
    [_ false]))

;; ----------
;; Kompilacja
;; ----------

(define (rpn->arith e)
    
    (define (ar-iter ex st)
      (cond 
          [(empty? ex) (car st)]
          [(number? (car ex)) (ar-iter (cdr ex)(append (list(const (car ex))) st))]
          [(symbol? (car ex)) (ar-iter (cdr ex) (append (list(binop (car ex) (second st) (first st))) (cddr st)))]))

  (ar-iter e null))

(rpn->arith '(2 3 + 5 *))
(arith-expr? (rpn->arith '(2 3 + 5 *)))
(arith-expr? (rpn->arith '(2 7 + 3 / 14 3 - 4 * + 2 /)))
; Mozesz tez dodac jakies procedury pomocnicze i testy
