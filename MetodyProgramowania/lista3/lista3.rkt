#lang racket 

(define (append l o)
    (if(null? l)
        o
        (cons (car l) (append (cdr l) o))))

(define (square x)(* x x))

(define (good-enough? x y)
    (< (abs(- x y)) 0.000000001))

(define (sqrt x)
    (define (sqrt-iter y x)
        (if (good-enough? (* y y) x)
        y
        (sqrt-iter (/(+ x y)2) x)))
    (sqrt-iter 1 x))

(define(display-point p)
(display "(")
(display (point-x p))
(display ", ")
(display (point-y p))
(display ")"))

(define(display-vect v)
(display "[")
(display-point (vect-begin v))
(display ", ")
(display-point (vect-end v))
(display "]"))
;;z1

(define (make-point x y)(cons x y))

(define (point-x x)(car x))

(define (point-y x)(cdr x))

(define (point? x)
    (and (pair? x) (not (or (null? (point-x x)) (null? (point-y x))))))

;;testy dla punktu
(point? 1)
(point? (make-point 1 3))
(point? (cons 1 `()))

;;wektor 

(define (make-vect a b)
    (cons a b))

(define (vect-begin v)(car v))
(define (vect-end v)(cdr v))

(define (vect? v)
    (and (point? (vect-begin v))(point? (vect-end v))))

(make-vect 1 2)
(newline)
(vect? (make-vect (make-point 1 2) (make-point 3 2)))

(define (vect-lenght v)
    (sqrt 
        (+
            (square (- (point-x (vect-end v))(point-x(vect-begin v)))) 
            (square (- (point-y (vect-end v))(point-y (vect-begin v)))))))

(vect-lenght (make-vect (make-point 1 1.0)(make-point 1 1)))

(define (vect-scale v k)
    (make-vect (vect-begin v) (make-point (* (point-x(vect-end v)) k) (*(point-y(vect-end v)) k))))

(display-vect (vect-scale (make-vect (make-point 1 1.0) (make-point 1 1)) 2))

;;z3

(newline)

(define (l-lenght l)
    (if(null? l)
        0
        (+ 1 (l-lenght (cdr l)))))

(define (take-last l)
    (if (= 1 (l-lenght l))
        l
        (take-last (cdr l))))

(define (take-elem l n)
    (define (take-iter l i)
        (if (= i n)
        (car l)
        (take-iter (cdr l) (+ i 1))))
        (take-iter l 1))

(define (rem-last l)
    (if (= (l-lenght l) 2)
        (car l)
        (cons (car l) (rem-last (cdr l)))))

(define (reverse l)
    (define (rev-iter n)
        (if (= 1 n)
            (car l)
            (cons (take-elem l n) (rev-iter (- n 1)))))
    (rev-iter (l-lenght l)))

(take-elem (list 1 2 3 4 5 6) 6)

(reverse (list 1 2 3 4 5 6))

;;z4 

(define (insert l n)
    (if (null? l)
        (list n)    
        (if (< n (car l))
            (cons n l)
            (cons (car l) (insert (cdr l) n)))))

(insert (list 1 2 3) 4)

(define (insertion-sort l)
    (define (iter l z)
        (if (null? l)
            z
            (iter (cdr l) (insert z (car l)))))
    (iter l null))

(insertion-sort (list 3 2 3 4 9 1)) 


