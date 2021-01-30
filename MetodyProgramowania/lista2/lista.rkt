#lang racket

;; zad 2
(define (compose f g)
  (lambda (x)(f(g x))))

(define (square x)
  (* x x))

(define (ff x)
  (+ x 1))

((compose square ff)3)

;;zad 3
(define (repeated p n)
  (if (= n 0)
  identity
  (compose p(repeated p (- n 1)))))

((repeated (* 2)2)2)


;;zad 4 
(define (inc x)(+ x 1))

(define (product val next start end)
  (if(> start end)
     1.0
     (*(val start)(product val next (next start) end))))

(define (product_iter val next start end)
  (define (product-inner start acc)
    (if(> start end)
       acc
       (product-inner (next start)(* acc (val start)))))
  (product-inner start 1.0)) 

(product identity inc 1 100) 

(product_iter identity inc 1 5)

;;zad 5
                  ;;  *      1.0     val start  end
(define (accumulate combiner null-val term a next b)
  (if(> a b)
     null-val
     (combiner(term a)(accumulate combiner null-val term (next a)next b))))

(accumulate * 1.0 inc 1 inc 2)

(define (inc2 x)(+ x 2))

(* 4(accumulate * 1 (lambda(x) (/(* x (inc2 x))(square (+ x 1)))) 2.0 inc2 125000.0))

;;zad 6

(define (cont n d i k)
  (if(= k i)
     0
     (/ (n i) (+ (d i) (cont n d (+ i 1) k)))))

(define (cont-iter n d k)
  (define (iter acc i)
  (if(= i 0)
     acc
     (iter (/ (n i)(+ (d i) acc)) (- i 1))))
(iter 0 k))

;;zad 6
(cont (lambda (x) 1.0) (lambda (x) 1.0) 1.0 1000)

;;zad 7
(+ 3 (cont (lambda (i) (square (- (* 2 i) 1.0))) (lambda (i) 6.0) 1.0 500))

(+ 3 (cont-iter (lambda (i) (square (- (* 2 i) 1.0))) (lambda (i) 6.0) 500))

;;zad 8

(define (arct x)
  (cont-iter (lambda (k)
               (if(= k 1)
                  x
                  (square(* x (- k 1)))))
             (lambda (k) (- (* 2 k) 1))
             1000.0))

(arct 1)
