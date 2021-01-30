#lang racket

(provide cont-frac)

(define (square x)
  (* x x))

(define (cont-frac n d)
  (define (cia n d  i)
    (cond 
      [(= i -1) 1]
      [(= i 0) 0]
      [(+ (* (d i) (cia n d  (- i 1))) (* (n i) (cia n d  (- i 2))))]))

  (define (cib n d  i)
    (cond 
      [(= i -1) 0]
      [(= i 0) 1]
      [(+ (* (d i) (cib n d  (- i 1))) (* (n i) (cib n d  (- i 2))))]))
  
  (define (iter i)
    (if (> 0.0001 (abs(- (/ (cia n d  i)(cib n d  i)) (/ (cia n d  (+ i 1)) (cib n d  (+ i 1))))))
      (/ (cia n d  (+ i 1)) (cib n d  (+ i 1)))
      (iter (+ i 1))))

(iter 2))



(define pi
  (+ 3 
  (cont-frac 
    (lambda (i) (square(- (* 2 i)1)))
    (lambda (i) 6.0))))

pi

(display "Przybliżenie fi : \n")
(cont-frac (lambda (x) 1.0) (lambda (x) 1.0))
