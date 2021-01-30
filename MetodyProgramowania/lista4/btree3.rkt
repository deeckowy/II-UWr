#lang racket

(define (btree? t)
    (or(eq? t'leaf)
        (and (list? t)
            (= 4 (length t))
            (eq? (car t) 'node)
            (btree? (caddr t))
            (btree? (cadddr t)))))

(define (mirror tree)
    (list (car tree)(cadr tree)(cadddr tree)(caddr tree)))

(mirror '(node a (node b (node c leaf leaf) leaf) (node d leaf leaf)))

