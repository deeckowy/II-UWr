#lang racket 

(provide make-elem elem-priority elem-val empty-heap heap-insert heap-merge heap-min heap-pop heap-empty?)

(define (inc x)
  (+ x 1))

(define leaf 'leaf)

(define empty-heap leaf)


;; predicates 

(define (tagged-list? len sym x)

    (and
        (list? x)
        (= (length x) len)
        (eq? (first x) sym)))

(define (leaf? h) (eq? 'leaf h))

(define (hnode? h)

    (and
        (tagged-list? 5 'hnode h)
        (real? (caddr h))))

(define (heap? h)
  
  (or
   (leaf? h)
   (and
    (hnode? h)
    (heap? (hnode-left h))
    (heap? (hnode-right h))
    (<= (rank (hnode-right h))
        (rank(hnode-left h)))
    (= (hnode-rank h) (inc (rank(hnode-right h))))
    (hord? (elem-priority (hnode-elem h))
           (hnode-left h)))))

(define (hord? p h)

    (or 
        (leaf? h)
        (<= p (elem-priority (hnode-elem h)))))

(define (heap-empty? h)
    (leaf? h))

;;hnode constructor
(define (make-hnode elem heap-a heap-b)
    (if (>(rank heap-a)(rank heap-b))
        (list 'hnode elem (+ 1 (rank heap-b)) heap-a heap-b)
        (list 'hnode elem (+ 1 (rank heap-a)) heap-b heap-a)))

;;selectors
(define (hnode-elem h)
    (second h))

(define (hnode-left h)
    (fourth h))

(define (hnode-right h)
    (fifth h))

(define (hnode-rank h)
    (third h))

(define (make-elem x y)
    (cons x y))

(define (elem-val x)
    (car x))

(define (elem-priority x)
    (cdr x))

(define (rank h)
  (if(leaf? h)
     0
     (hnode-rank h)))

;; heap operations 

(define (heap-insert elt heap)
    (heap-merge heap (make-hnode elt leaf leaf)))

(define (heap-min heap)
    (hnode-elem heap))

(define (heap-pop heap)
    (heap-merge (hnode-left heap)(hnode-right heap)))

(define (heap-merge h1 h2)
    (cond
    [(leaf? h1)h2]
    [(leaf? h2)h1]
    [(> (elem-priority(hnode-elem h1))(elem-priority(hnode-elem h2))) (make-hnode (hnode-elem h2) (heap-merge (hnode-right h2) h1) (hnode-left h2))]
    [else (make-hnode (hnode-elem h1) (heap-merge (hnode-right h1) h2) (hnode-left h1))]))

;;///////////////////////



(define (sample-heap n)
    (define (heap-iter k sheap)
        (if (= n k)
        sheap
        (heap-iter (inc k) (heap-insert (make-elem 'x k) sheap))))

    (heap-iter 0 empty-heap))

(define eheap (sample-heap 10))

(heap-min eheap)
(newline)
(heap-pop eheap)
(newline)
(heap-insert (make-elem 'pzdr 0) eheap)