#lang racket

(require compatibility/mlist)

(define (cycle xs)
  (define (list->mlist xs)
    (cond [(null? xs) null]
          [else (mcons (car xs) (list->mlist (cdr xs)))]))
  (define (first-to-last! mxs)
    (define (aux mys)
      (cond [(null? mys) (error "Can't cycle empty list")]
            [(and (mpair? mys) (null? (mcdr mys)))
             (set-mcdr! mys mxs)]
            [else (aux (mcdr mys))]))
    (aux mxs))
  (let ([mxs (list->mlist xs)])
    (begin (first-to-last! mxs)
           mxs)))

(define (mtake n mxs)
  (cond [(= n 0) null]
        [(null? mxs) null]
        [else (cons (mcar mxs) (mtake (- n 1) (mcdr mxs)))]))

(define (test)
  (mtake 15 (cycle '(0 1 2 3))))

;;;;;1

(define (mreverse! xs)
    (define (mrev-iter xd e)
        (if (null?(mcdr xd))
            (begin (set! xs xd) (set-mcdr! xs (mcons e null)))
            (begin (mrev-iter (mcdr xd) (mcar xd))(set-mcdr! (help xs) (mcons e null)))))
    (define (help x)
      (if (null? (mcdr x))
          x
          (help (mcdr x))))
    (begin (mrev-iter (mcdr xs) (mcar xs)) xs))

(mreverse! (mlist 1 2 3 4))


;;;;;;;2222222

(struct bdlist (v [prev #:mutable] [next #:mutable]) #:transparent)

(define (list->bdlist x)
    (define (l-iter x)
        (if (null? x)
            null
            (bdlist (car x) null (l-iter (cdr x)))))
    (define (rev x p)
        (let ([ac (set-bdlist-prev! x p)])
            (if (null? (bdlist-next x))
                ac
                (begin ac (rev (bdlist-next x) x)))))
    (let ([d (l-iter x)])
        (begin (rev d null) d)))

(define (bdfilter f x)
    (define (help l)
        (if (null? (bdlist-prev l))
            l
            (help (bdlist-prev l))))
    
    
    
    (let* 
        (
            [p (bdlist-prev x)]
            [n (bdlist-next x)]
            [arg (f (bdlist-v x))])
            (cond 
                [(and (null? p)(null? n))
                    (if arg
                        x
                        null)]
                [(null? n)
                        (if arg 
                            (help x)
                            (begin (set-bdlist-next! p n) (help p)))]
                [(null? p)
                    (let ([go (bdfilter f n)])
                        (if arg 
                            go
                            (begin (set-bdlist-prev! n p) go)))]
                [else (let ([go (bdfilter f n)])
                            (if arg 
                                go 
                                (begin (set-bdlist-prev! n p)(set-bdlist-next! p n) go)))])))

(define sample (list->bdlist '(1 2 -3 4)))
sample

(bdfilter positive? sample)
;;(should be '(1 2 4))

;;;;;;;;333333
(define (cycle-bdlist! l)
    (define (cycle-iter l f)
        (let* 
            ([p (bdlist-prev l)]
            [n (bdlist-next l)])
            (cond 
                [(null? p) (begin (set-bdlist-prev! l (cycle-iter n l)) l)]
                [(null? n) (begin (set-bdlist-next! l f) l)]
                [else (cycle-iter n f)])))
    (cycle-iter l null))

(cycle-bdlist! sample)

(define (decycle-bdlist! l n)
    (if (= n 0)
        (let* ([p (bdlist-prev l)])
            (begin (set-bdlist-next! p null)(set-bdlist-prev! l null) l))
            (decycle-bdlist! (bdlist-next l) (- n 1))))

(decycle-bdlist! sample 0)


