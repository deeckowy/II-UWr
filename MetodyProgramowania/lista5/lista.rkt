#lang racket 

(define (var? t)
    (symbol? t))

(define (neg? t)
    (and
        (list? t)
        (= 2 (length t))
        (eq? 'neg (car t))))

(define (conj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'conj (car t))))

(define (disj? t)
  (and (list? t)
       (= 3 (length t))
       (eq? 'disj (car t))))

(define (prop? f)
  (or (var? f)
      (and (neg? f)
           (prop? (neg-subf f)))
      (and (disj? f)
           (prop? (disj-left f))
           (prop? (disj-rght f)))
      (and (conj? f)
           (prop? (conj-left f))
           (prop? (conj-rght f)))))
;;do zadania 5
(define (literal? x)
    (and 
        (= 3 (length x))
        (eq? 'literal (first x))
        (boolean? (second x))
        (var? (third x))))


;;////////////////////////////////1

(define (make-neg x)
    (list 'neg x))

(define (make-conj x y)
    (list 'conj x y))

(define (make-disj x y)
    (list 'disj x y))

(define (neg-subf x)
    (second x))

(define (disj-left x)
    (second x))

(define (disj-rght x)
    (third x))

(define (conj-left x)
    (second x))

(define (conj-rght x)
    (third x))

;;////////////////////////////////2

;;; Indukcja po podformułach.

;;; ```
;;; (define (prop? f)
;;;     (or (var? f)
;;;         (and (neg? f)
;;;              (prop? (neg-subf f)))
;;;         (and (disj? f)
;;;              (prop? (disj-left f))
;;;              (prop? (disj-rght f)))
;;;         (and (conj? f)
;;;              (prop? (conj-left f))
;;;              (prop? (conj-rght f)))))
;;; ```

;;; Zasada indukcji. Dla dowolnej własności P, jeśli:

;;; - dla każdego symbolu x zachodzi P(x),
;;; - dla dowolnej formuły f, jeśli zachodzi P(f), to zachodzi P((neg f)) i
;;; - dla dowolnych formuł f1, f2, jeśli zachodzi P(f1) i P(f2), to zachodzi również P((conj f1 f2)) i P((disj f1 f2))

;;; to dla dowolnej formuły f, jeśli zachodzi (prop? f), to zachodzi P(f).

;;////////////////////////////////3

(define (free-vars f)
    
    (define (free-iter l)
        (cond
            [(var? l) (list l)]
            [(literal? l) (list(third l))]
            [(neg? l) (free-iter (neg-subf l))]
            [(disj? l) (append (free-iter (disj-left l)) (free-iter (disj-rght l)))]
            [(conj? l) (append (free-iter (conj-left l)) (free-iter (conj-rght l)))]))            
            
    (remove-duplicates (free-iter f)))


;;//////////////////////////////5

(define(gen-vals  xs)
    (if(null? xs)
        (list  null)
        (let*
            ((vss   (gen-vals (cdr xs)))
            (x     (car xs))
            (vst   (map (lambda(vs) (cons (list x true)   vs)) vss))
            (vsf   (map (lambda(vs) (cons (list x false) vs)) vss)))
        (append  vst  vsf))))


(define sample (make-conj (make-neg (make-disj 'p 'u))(make-conj 'i (make-conj 'x 'b))))


(define (eval-formula xs gs)
    
    (define (get-val x l)
        (cond
            [(null? l) (display "ERR")]
            [(eq? x (first (car l)))(second (car l))]
            [else (get-val x (cdr l))]))
                   
    (define (go ls)
        (cond
            [(var? ls) (get-val ls gs)]
            [(neg? ls) (not(go (neg-subf ls)))]
            [(literal? ls)
                (if (second ls)
                    (get-val (third ls) gs)
                    (not (get-val (third ls) gs)))]
            [(conj? ls) (and (go (conj-left ls)) (go (conj-left ls)))]
            [(disj? ls) (or (go (disj-left ls)) (go (disj-rght ls)))]))

    (go xs))

(define (falsifiable-eval? xs gs)

    (cond 
        [(null? gs) #f]
        [(eval-formula xs (car gs)) (falsifiable-eval? xs (cdr gs))]
        [else (car gs)]))

;;(falsifiable-eval? sample (gen-vals (free-vars sample)))

;;//////////////////////////////////5


(define (make-literal b x)
    (list 'literal b x))

;;(make-literal true 'f)


;;(literal? (make-literal true 'f))

(define (nnf? xs)
    (or
        (var? xs)
        (literal? xs)
        (and 
            (disj? xs)
            (nnf? (disj-left xs))
            (nnf? (disj-rght xs)))
        (and
            (conj? xs)
            (nnf? (conj-left xs))
            (nnf? (conj-rght xs)))))

;;(nnf? (make-literal true 'f))

(define sample2 (make-disj(make-disj (make-conj (make-literal true 'x)(make-literal false 'f)) (make-literal false 'i))(make-literal true 'g)))

;;(falsifiable-eval? sample2 (gen-vals (free-vars sample2)))


;;//////////////////////6

(define (convert-to-nnf x)
    
    (define (T f)
        (cond
            [(var? f) (make-literal true f)]
            [(neg? f) (F (neg-subf f))]
            [(conj? f) (make-conj (T(conj-left f)) (T(conj-rght f)))]
            [(disj? f) (make-disj (T(conj-left f)) (T(conj-rght f)))]))

    (define (F f)
        (cond
            [(var? f) (make-literal false f)]
            [(neg? f) (T (neg-subf f))]
            [(conj? f) (make-disj (F(conj-left f)) (F(conj-rght f)))]
            [(disj? f) (make-conj (F(disj-left f)) (F(disj-rght f)))]))
    (T x))


;;sample2


;;///////////////8

(define (clause? x)
    (and 
        (list? x)
        (andmap literal? x)))

(define (cnf? x)
    (and 
        (list x)
        (andmap clause? x)))

(define (convert-to-cnf x)

    (cond 
        [(literal? x) (list(list x))]
        [(conj? x) (append (convert-to-cnf (conj-left x))(convert-to-cnf (conj-rght x)))]
        [(disj? x)
            (append-map
                (lambda (l)
                    (map
                        (lambda (s)
                            (append l s))
                (convert-to-cnf (disj-left x))))
                (convert-to-cnf (disj-rght x)))]))

;;(cnf? (convert-to-cnf (convert-to-nnf sample)))

(define (eval-cnf xs ls)
    
    (define (get-val x l)
        (if(eq? (third x) (first (car l)))
            (if (second x)
                (second (car l))
                (not (second (car l))))
            (get-val x (cdr l))))


    (define (go xd)
        (if (= 1 (length xd))
            (get-val (car xd)) ls)
            (or (get-val (car xd) ls) (go (cdr xd))))
            
    (if (go (car xs))
        (eval-cnf (cdr xs) ls)
        #f))

;;(convert-to-cnf (convert-to-nnf sample))

;;(eval-cnf (convert-to-cnf (convert-to-nnf sample)) (car(gen-vals(free-vars sample))))

;;;/////////// 9 aka homework

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

    (cond
        [(cnf? x)(go x)]
        [(nnf? x) (go (convert-to-cnf x))]
        [(prop? x) (go (convert-to-cnf (convert-to-nnf x)))]))

(convert-to-cnf sample2)
(falsifiable-cnf? sample)