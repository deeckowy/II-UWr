#lang racket

(provide nth-root)

(define (compose f g)
    (lambda (x) (f(g x))))

(define (repeated p n)
    (if (< n 1)
    identity
    (compose p (repeated p (- n 1)))))

(define (nth-root n x)

    (define (close-to? x y)
        (< (abs(- x y)) 0.0000000001))

    (define (average x y)
        (/ (+ x y) 2))

    (define (average-damp f)
        (lambda (x) 
            (average x (f x))))

    (define (fixed-point x f)
        (if (close-to? x (f x))
        x
        (fixed-point (f x) f)))

    (define (pow x n)
        (if (= n 1)
        x
        (* x (pow x (- n 1)))))


    (let ((fn (lambda (y) (/ x (pow y (- n 1))))))
    (fixed-point x ((repeated average-damp (floor (/ (log n)(log 2))))fn))))

(display "pierwiastek 10 stopnia z 15 : ")
(nth-root 10 15.0)
(display "pierwiastek kwadratowy z 2 : ")
(nth-root 2.0 2.0)
(display "pierwiastek szescienny z 27 : ")
(nth-root 3 27.0)
(display "pierwiastek 4 stopnia z 625 : ")
(nth-root 4 625.0)