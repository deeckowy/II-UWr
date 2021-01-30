#lang typed/racket

;#lang racket

;;; (define (prefixes [xs null] ys)
;;;     (if (null? (cdr ys))
;;;       (car ys)
;;;       (cons (reverse xs) (prefixes (cons (car ys) xs) (cdr ys)))))

;;; (prefixes (list 1 2 3 4))

;;; (number? 1+2i)

;;; (define-predicate nonneg-real? Nonnegative-Real)


;;; (: square (-> Real Nonnegative-Real))
;;; (define (square x) (assert (* x x) nonneg-real?))

;;; (square 0)
(: len (-> (Listof Any) Integer))
(define (len li)
  (foldr (lambda ([xs : Any] [acc : Integer]) (+ acc 1)) 0 li))

(len (list 'x 's 'd 'f))



;;;;;;;;;;;333
#lang typed/racket

(: foldr (All (a b) (-> (-> a b b) b (Listof a) b)))
(define (foldr f initial xs)
  (if (null? xs)
      initial
      (f (car xs) (foldr f initial (cdr xs)))))

(foldr + 0 '(1 2 3 4))
(foldr - 0 '(1 2 3 4))

(: foldr-single (All (a) (-> (-> a a a) a (Listof a) a)))
(define (foldr-single f initial xs)
  (if (null? xs)
      initial
      (f (car xs) (foldr-single f initial (cdr xs)))))

; podpunkt a)

(: foldr-single-bad (All (a) (-> (-> a a a) a (Listof a) a)))
(define (foldr-single-bad f initial xs)
  (if (null? xs)
      initial
                                  ;(car xs) zamiast initial
      (f (car xs) (foldr-single-bad f (car xs) (cdr xs)))))

;(: foldr-bad (All (a b) (-> (-> a b b) b (Listof a) b)))
;(define (foldr-bad f initial xs)
;  (if (null? xs)
;      initial
;      (f (car xs) (foldr-bad f (car xs) (cdr xs)))))

(foldr-single-bad + 0 '(1 2 3 4))
;(foldr-bad + 0 '(1 2 3 4))

; podpunkt b) (tak ogranicza)

(: wasteful-string-identity (-> Number String String))
(define (wasteful-string-identity n s) s)

(foldr wasteful-string-identity "1" '(1 2 3))
;(foldr-single wasteful-string-identity "1" '(1 2 3))

(: len (-> (Listof Any) Number))
(define (len list) 
    (foldr (lambda ((elem : Any) (acc : Number)) (+ acc 1)) 0 list)
)




