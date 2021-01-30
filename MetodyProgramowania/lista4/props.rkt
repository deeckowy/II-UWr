#lang racket 

(provide conj conj-left conj-right conj?
         disj disj-left disj-right disj?
         neg neg-subf neg?
         var?)


(define (conj p q)
  (list 'conj p q))

(define (conj-left f)
  (second f))

(define (conj-right f)
  (third f))

(define (conj? t)
  (and (list? t)
        (= 3 (length t))
        (eq? 'conj (car t))))


(define (disj p q)
  (list 'disj p q))

(define (disj-left f)
  (second f))

(define (disj-right f)
  (third f))

(define (disj? t)
  (and (list? t)
        (= 3 (length t))
        (eq? 'disj (car t))))


(define (neg x)
  (list 'neg x))

(define (neg-subf x)
  (second x))

(define (neg? t)
  (and (list? t)
        (= 2 (length t))
        (eq? 'neg (car t))))


(define (var? t)
  (symbol? t))

