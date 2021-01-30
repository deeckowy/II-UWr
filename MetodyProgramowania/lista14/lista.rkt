#lang racket

(require racklog)

;; predykat unarny %male reprezentuje zbiór mężczyzn
(define %male
  (%rel ()
        [('adam)]
        [('john)]
        [('joshua)]
        [('mark)]
        [('david)]))

;; predykat unarny %female reprezentuje zbiór kobiet
(define %female
  (%rel ()
        [('eve)]
        [('helen)]
        [('ivonne)]
        [('anna)]))

;; predykat binarny %parent reprezentuje relację bycia rodzicem
(define %parent
  (%rel ()
        [('adam 'helen)]
        [('adam 'ivonne)]
        [('adam 'anna)]
        [('eve 'helen)]
        [('eve 'ivonne)]
        [('eve 'anna)]
        [('john 'joshua)]
        [('helen 'joshua)]
        [('ivonne 'david)]
        [('mark 'david)]))

;; predykat binarny %sibling reprezentuje relację bycia rodzeństwem
(define %sibling
  (%rel (a b c)
        [(a b)
         (%parent c a)
         (%parent c b)]))

;; predykat binarny %sister reprezentuje relację bycia siostrą
(define %sister
  (%rel (a b)
        [(a b)
         (%sibling a b)
         (%female a)]))

;; predykat binarny %ancestor reprezentuje relację bycia przodkiem
(define %ancestor
  (%rel (a b c)
        [(a b)
         (%parent a b)]
        [(a b)
         (%parent a c)
         (%ancestor c b)]))

;;;;;11111


;;predykat binarny %granson reprezentuje relację bycia wnukiem
(define %grandson
    (%rel (a b c)
        [(a c)
         (%parent a b)
         (%parent b c)]))
;test

;(%find-all (a b) (%grandson a b))

(define %cousin
    (%rel (a b c d)
        [(a b)
            (%sibling c d)
            (%parent c a)
            (%parent d b)
            ]))

;(%find-all (a b) (%cousin a b))

(define %is_mother 
    (%rel (a b)
        [(a)
            (%female a)
            (%parent a b)]))

;(%find-all (x) (%is_mother x))

(define %is_father
    (%rel (a b)
        [(a)
            (%male a)
            (%parent a b)]))

;(%find-all (x) (%is_father x))

;;;;;;;22222

(%find-all () (%ancestor 'mark 'john))
(%find-all (x) (%parent 'adam x))
(%find-all (x) (%sister 'ivonne x))
(%find-all (x y) (%cousin x y))

;;;;;;;333333
(%which (x) (%= 'a x))
(%which (x) (%== 'a x))

(%which (x y) (%grandson x y))

(%find-all (x) (%let (y) (%grandson x y)))