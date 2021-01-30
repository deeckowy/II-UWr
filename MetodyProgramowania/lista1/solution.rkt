#lang racket

(provide cube-root)

(define (cube x)
  (* x x x))

(define (cube-root x)
  (define (good guess)
  (<(abs(- (cube guess) x)) 0.00001))

(define (improve guess)
  (/ (+ (/ x (* guess guess)) (* 2 guess)) 3))

(define (cbrt-iter guess)
  (if (good guess)
      guess
      (cbrt-iter (improve guess))))
  (cbrt-iter 1.0))


