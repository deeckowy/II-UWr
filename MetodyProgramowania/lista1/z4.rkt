#lang racket

;;z4l1
(define (sq x)(* x x)) 

(define (suma e1 e2 e3)
  (-
   (+ (sq e1) (sq e2) (sq e3)) (min (sq e1)(sq e2)(sq e3))))


;;z7l1

(define (p) (p))

(define (test x y)
  (if(= x 0)
     0
     y))


;;z8l1
;; -1 oznacza brak e

(define (power b e)
  (if (= e 1)
      b
      (* b (power b (- e 1)))))

(define (goodp b e n)
  (if (> (power b e) n)
      e
      (goodp b (+ e 1) n)))

(define
  (power-close-to b n)
  (if(> b n)
     1
     (if(= b 1)
        -1
        (if (and (> 1 b) (> 1 n))
            (display "")
            (goodp b 1 n)
            ))))




  