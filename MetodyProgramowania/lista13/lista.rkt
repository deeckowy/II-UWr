#lang typed/racket 

;;;;1111

;;; (: prefixes3 (All (A)  (-> (Listof A) (Listof (Listof A)))))
;;; (define (prefixes3 l)
;;;   (if (null? l)
;;;       (list null)
;;;       (cons null 
;;;             (map (lambda ([xs : (Listof A)]) (cons (car l) xs))
;;;                  (prefixes3 (cdr l))))))



;;; (: prefixes (All (a) (-> (Listof a) (U Null (Listof (Listof a))))))
;;; (define (prefixes xs) 
;;;     (if (null? xs)
;;;       (list null)
;;;       (cons xs (prefixes (reverse (cdr (reverse xs)))))))

;;; (prefixes (list 1 2 3 4))

;;; (: prefixes (All (a) (-> (Listof a) (Listof (Listof a)))))
;;; (define (prefixes l)
;;;   (: prefix (All (a) (-> (Listof a) (Listof (Listof a)))))
;;;   (define (prefix xs)
;;;     (if (null? xs)
;;;         (list null)
;;;         (cons (reverse xs) (prefix (cdr xs)))))
;;;   (prefix (reverse l)))


;;(prefixes3 '(1 2 3 4))

;;;;;22222

(struct vector2 ([x : Real] [y : Real]) #:transparent)
(struct vector3 ([x : Real] [y : Real] [z : Real]) #:transparent)

(define-predicate nonneg-real? Nonnegative-Real)

(: square (-> Real Nonnegative-Real))
(define (square x) (assert (* x x) nonneg-real?))


(: vector-length (-> (U vector2 vector3) Real))
(define (vector-length v)
  (match v
    [(vector2 x y) (sqrt (+ (square x) (square y)))]
    [(vector3 x y z) (sqrt (+ (square x) (square y) (square z)))]))


(: vector-length2 (-> (U vector2 vector3) Number))
(define (vector-length2 v)
  (if (vector2? v)
      (sqrt (+ (square (vector2-x v)) (square (vector2-y v))))
      (sqrt (+ (square (vector3-x v)) (square (vector3-y v)) (square (vector3-z v))))))


(vector-length (vector2 1 1))
(vector-length2 (vector3 1 1 1))

;;; (struct vector2 ([x : Real] [y : Real])            #:transparent)
;;; (struct vector3 ([x : Real] [y : Real] [z : Real]) #:transparent)

;;; ;tu nie definiujemy predykatów, bo to struktura, a nie typ
;;; (: vector-length-cond (-> (U vector2 vector3) Real))
;;; (define (vector-length-cond v)
;;;   (cond
;;;     [(vector2? v) (sqrt (+ (sqr (vector2-x v)) (sqr (vector2-y v))))]
;;;     [(vector3? v) (sqrt (+ (sqr (vector3-x v)) (sqr (vector3-y v)) (sqr (vector3-z v))))]))

;;; (: vector-length-match (-> (U vector2 vector3) Real))
;;; (define (vector-length-match v)
;;;   (match v
;;;     [(vector2 x y) (sqrt (+ (sqr x) (sqr y)))]
;;;     [(vector3 x y z) (sqrt (+ (sqr x) (sqr y) (sqr z)))]))

;;; (vector-length-cond  (vector2 -4 3))
;;; (vector-length-match (vector2 -4 3))

;;; (vector-length-cond  (vector3 -1 2 1))
;;; (vector-length-match (vector3 -1 2 1))
;;;;;;;33333

;;;;;;;44444

(struct [a] rose-node ([val : a][list : (Listof (rose-tree a))]) #:transparent)
(struct rose-leaf () #:transparent)

(define-type (rose-tree a)(U rose-leaf (rose-node a)))
(define-predicate r-tree? (rose-tree Any))


(: get-preorder (All (a) (-> (rose-tree a) (U (Listof a) Null))))
(define (get-preorder t)
  (match t
    [(rose-node v li)
     (: it (All (a) (-> (Listof (rose-tree a)) (Listof a))))
        (define (it list)
          (if (null? list)
            null
            (match (car list)
              [(rose-leaf)(it (cdr list))]
              [(rose-node v li)(append (get-preorder (car list)) (it (cdr list)))])))
              (cons v (it li))]
    [(rose-leaf) null]))


(define sample-tree (rose-node 3 (list (rose-leaf) (rose-node 5 null) (rose-node 7 (list (rose-leaf) (rose-node 91 null))))))

(get-preorder sample-tree)