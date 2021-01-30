#lang racket

(require racklog)

(define %my-append
  (%rel (x xs ys zs)
        [(null ys ys)]
        [((cons x xs) ys (cons x zs))
         (%my-append xs ys zs)]))

(define %my-member
  (%rel (x xs y)
        [(x (cons x xs))]
        [(y (cons x xs))
         (%my-member y xs)]))

(define %select
  (%rel (x xs y ys)
        [(x (cons x xs) xs)]
        [(y (cons x xs) (cons x ys))
         (%select y xs ys)]))

;; prosta rekurencyjna definicja
(define %simple-length
  (%rel (x xs n m)
        [(null 0)]
        [((cons x xs) n)
         (%simple-length xs m)
         (%is n (+ m 1))]))

;;; ;; test w trybie +- (działa)
;;; (%find-all (a) (%simple-length (list 1 2) a))
;;; ;; test w trybie ++ (działa)
;;; (%find-all () (%simple-length (list 1 2) 2))
;;; ;; test w trybie -+ (1 odpowiedź, pętli się)
;;; (%which (xs) (%simple-length xs 2))
;;; ;; test w trybie -- (nieskończona liczba odpowiedzi)
;;; (%which (xs a) (%simple-length xs a))

;(%which (xs ys) (%my-append xs ys ys))

;(%find-all (xs) (%select xs (list 1 2 3 4) (list 1 2 4)))

;(%which (xs) (%my-append '(1 2 3) xs '(1 2 3 4 5))) ~ niestety mam 2 IQ :(


(define %sublist
  (%rel (x xs y ys)
        [(null xs)]
        [((cons y ys) (cons y xs))
         (%sublist ys xs)]
        [((cons y ys) (cons x xs))
         (%sublist (cons y ys) xs)]))

(%find-all (x) (%sublist x '(1 2 3)))
(%which () (%sublist '(1 5) '(1 2 3 4 5)))


(define %perm
  (%rel (x xs ys zs)
        [(xs xs)]
        [((cons x xs) ys)
         (%select x ys zs)
         (%perm xs zs)]))



(define %perm2
  (%rel (x xs ys zs)
        [(null null)]
        [((cons x xs) ys)      
         (%perm2 xs zs)
         (%select x ys zs)
         (%perm2 xs zs)]))

(%find-all (ys) (%perm2 ys '(1 2 3)))
