#lang racket

; z zeszłych zadań:
(require racklog)

(define %sublist
  (%rel (x y xs ys)
        [(xs xs)]
        ; ten sam element - przesuwamy się po obu listach
        [((cons x xs) (cons x ys))
         (%sublist xs ys)]
        ; nie ma takich samych elementów - usuwamy z drugiej listy
        [((cons x xs) (cons y ys))
         (%/== x y)
         (%sublist (cons x xs) ys)]))

(define %select
  (%rel (x xs y ys)
        [(x (cons x xs) xs)]
        [(y (cons x xs) (cons x ys))
         (%select y xs ys)]))

(define %perm
  (%rel (x y xs ys zs)
        [(null null)]
        [((cons x xs) ys)
         (%select x ys zs)
         (%perm xs zs)]))

(define %length
  (%rel (x xs n m)
        [(null 0)]
        [((cons x xs) n)
         (%length xs m)
         (%is n (+ m 1))]))

; NOWE.
(define (list->num xs)
  (define (iter acc xs)
    (if (null? xs)
      acc
      (iter (+ (* acc 10) (car xs)) (cdr xs))))
  (iter 0 xs))

(define %solve
  (%rel (D E M N O R S Y l1 l2 l3 l4)
        [((list D E M N O R S Y))
         (%=/= M 0)
         (%=/= S 0)
         (%is l1 (list->num (list M O N E Y)))
         (%is l2 (list->num (list S E N D)))
         (%is l3 (list->num (list M O R E)))
         (%is l4 (+ l2 l3))
         (%= l1 l4)]))

(%which (xs ys) (%sublist xs '(0 1 2 3 4 5 6 7 8 9))
                (%length xs 8)
                (%perm ys xs) ; kolejność ma znaczenie!
                (%solve ys))

; '((xs 0 1 2 5 6 7 8 9) (ys 7 5 1 6 0 8 9 2))
; Time: 0h:06m:45s
; 9567 + 1085 = 10652