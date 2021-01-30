#lang racket

(define (make-rat n d)(cons n d))

(define (numer x) (car x))

(define (denom x) (cdr x))

(define (print-rat x)
    (newline)
    (display (numer x))
    (display "/")
    (display (denom x)))

(define x (make-rat 1 2))
(print-rat x)

(define (make-interval n d)(cons n d))

(define (upper-bound x)(car x))

(define (lower-bound x)(cdr x))

(define (sub-interval x y)
    (make-interval 
        (- (upper-bound x) (upper-bound y))
        (- (lower-bound x) (lower-bound y))))

(newline)

(define (lenght x)
    (if (null? x)
        0
        (+ 1 (lenght (cdr x)))))

(define (last-pair x)
    (if (= 1 (lenght x))
        x
        (last-pair (cdr x))))

(last-pair (list 23 72 149 34))

(define (reverse x)
    (cons (last-pair x) (reverse (cdr x))))

(reverse (list 1 4 9 16 25))