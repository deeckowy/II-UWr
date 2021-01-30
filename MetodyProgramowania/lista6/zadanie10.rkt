#lang racket

(provide (struct-out complex) parse eval)

(struct complex (re im) #:transparent)

(define value?
  complex?)

;; Ponizej znajduje sie interpreter zwyklych wyrazen arytmetycznych.
;; Zadanie to zmodyfikowac go tak, by dzialal z liczbami zespolonymi.

(struct const (val)    #:transparent)
(struct binop (op l r) #:transparent)

(define (op->proc op)
  (match op ['+ +] ['- -] ['* *] ['/ /]))

(define (eval e)
  (match e
    [(complex r i) (complex r i)]
    [(binop op l r) 
        (let*(
            [r1 (complex-re (eval l))]
            [i1 (complex-im (eval l))]
            [r2 (complex-re (eval r))]
            [i2 (complex-im (eval r))])
                (cond 
                    [(or (eq? op '-) (eq? op '+)) (complex ((op->proc op) r1 r2) ((op->proc op) i1 i2))]
                    [(eq? op '*) (complex (+(* r1 r2)(- (* i1 i2))) (+ (* r1 i2)(* r2 i1)))]
                    [(eq? op '/) 
                        (let([dz (+(* r2 r2)(* i2 i2))])
                            (complex (/ (+ (* r1 r2) (* i1 i2)) dz) (/ (- (* i1 r2) (* r1 i2)) dz)))]
                    ))]))

(define (parse q)
  (cond 
        [(eq? q 'i) (complex 0 1)]
        [(number? q) (complex q 0)]
        [(and (list? q) (eq? (length q) 3) (symbol? (first q)))
            (binop (first q) (parse (second q)) (parse (third q)))]))


(eval (parse'(/ (+ 2 (* 8 i)) (* i i))))
(eval (parse'(+ 3 (* i 8))))
(eval (parse'(+ 3 (/ (+ 8 (* 4 i)) (+ -12 (* i 9))))))
(eval(parse '(/ 5 i)))
(eval(parse '(/ i 5)))