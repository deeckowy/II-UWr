#lang racket 

(define (flatten tree)
    (if (list? tree)
        (append (flatten(caddr tree))(append (list(cadr tree))(flatten (cadddr tree))))
        null))
(flatten '(node a (node b (node c leaf leaf) leaf) (node d leaf leaf)))
