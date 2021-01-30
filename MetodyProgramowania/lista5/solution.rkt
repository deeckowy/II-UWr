#lang racket
(provide falsifiable-cnf?)(require "props.rkt")


(define (make-conj x y)
    (list 'conj x y))

(define (make-disj x y)
    (list 'disj x y))

(define (make-literal b x)
    (list 'literal b x))

(define (literal? x)
    (and 
        (= 3 (length x))
        (eq? 'literal (first x))
        (boolean? (second x))
        (var? (third x))))


(define (convert-to-cnf x)

    (cond 
        [(literal? x) (list(list x))]
        [(conj? x) (append (convert-to-cnf (conj-left x))(convert-to-cnf (conj-right x)))]
        [(disj? x)
            (append-map
                (lambda (l)
                    (map
                        (lambda (s)
                            (append l s))
                (convert-to-cnf (disj-left x))))
                (convert-to-cnf (disj-right x)))]))


(define (convert-to-nnf x)
    
    (define (T f)
        (cond
            [(var? f) (make-literal true f)]
            [(neg? f) (F (neg-subf f))]
            [(conj? f) (make-conj (T(conj-left f)) (T(conj-right f)))]
            [(disj? f) (make-disj (T(conj-left f)) (T(conj-right f)))]))

    (define (F f)
        (cond
            [(var? f) (make-literal false f)]
            [(neg? f) (T (neg-subf f))]
            [(conj? f) (make-disj (F(conj-left f)) (F(conj-right f)))]
            [(disj? f) (make-conj (F(disj-left f)) (F(disj-right f)))]))
    (T x))


(define (falsifiable-cnf? x)

    (define (look x l)
        (cond 
            [(null? l) (list (third (car x)) (not (second (car x))))]
            [(eq? (third (car x))(first (car l))) 
                (if(= (second (car x))(second (car l)))
                    #f
                    l)]
            [else (look x (cdr l))]))

    (define (val x l)
        (cond 
            [(null? x) l]
            [(not (look x l)) #f]
            [else (val (cdr x) (append l (list(look x l))))]))

    (define (go x)
        (cond 
            [(null? x) #f]
            [(not (val (car x) null))(go (cdr x))]
            [else (val (car x) null)]))

        (go (convert-to-cnf (convert-to-nnf x))))


;;; Funkcja falsifiable-cnf różni się od falsifiable-eval działaniem oraz optymistyczną złożonością czasową,
;;; w pierwszej funkcji staramy się od razu znaleźć wartościowanie, które potwierdzi że testowana formuła nie jest tautologią.
;;; Natomiast druga funkcja najpierw wygeneruje wszystkie możliwe wartościowania, a potem będzie sprawdzać ich wyniki.
;;; Funkcja falsifiable-cnf jest więc w większości przypadków szybsza niż funkcja falsifiable-eval.