#lang racket 

;;2

(define (queens board-size)

    (define (empty-board)

        (define (make-row x)
            (if (= x 1)
                (list 0)
                (append (list 0) (make-row (- x 1)))))                

        (make-row board-size))
        
        
    (define (adjoin-position row col rest)
        
        (define (c-iter n l)
            (if (= n col)
                (cons row (cdr l))
                (cons (car l) (c-iter (+ n 1)(cdr l)))))
                
        (c-iter 1 rest))

    (define (get-k k l)

        (if (= k 1)
            (car l)
            (get-k (- k 1) (cdr l))))

    (define (safe? k positions)

        (define (safe-iter n pos l)
            (cond
                [(= n k) #t]
                [(or (= (- pos (- k n)) (car l)) (= (+ pos (- k n)) (car l)) (= (car l) pos)) #f]
                [else (safe-iter (+ n 1) pos (cdr l))]))

        (safe-iter 1 (get-k k positions) positions))
        
    (define(queen-cols k)
        (if(= k 0)
            (list (empty-board))
            (filter
                (lambda(positions) (safe? k positions))
                    (append-map
                        (lambda(new-row)
                            (map (lambda(rest-of-queens)
                                (adjoin-position  new-row k rest-of-queens))
                        (queen-cols  (- k 1))))
                    (range 1 (+ 1 board-size))))))    
    
    (queen-cols  board-size))


(queens 6)

;;liczy od najwiekszych do najmniejszych 
