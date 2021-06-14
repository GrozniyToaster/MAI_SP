;coin21
(define VARIANT 17)
(define LAST-DIGIT-OF-GROUP-NUMBER 6)
(define KINDS-OF-COINS 4)

(define (first-denomination kinds-of-coins)
   (cond ( (= kinds-of-coins 1) 2)
         (else (cond ((= kinds-of-coins 2) 5)
                     (else (cond ((= kinds-of-coins 3) 15)
                                 (else (cond ((= kinds-of-coins 4) 25) (else 0) );cond 4 25
                                       );else
                                 );cond 3 15
                           ); else 
                     ); cond 2 5
         );else   
     ); max cond 1 2
   )
(define (count-change amount)
  (display "______\n amount: ") (display amount) (newline)
  (display "KINDS-OF-COINS: ") (display KINDS-OF-COINS) (newline)
  (let (
        (largest-coin (first-denomination KINDS-OF-COINS))
        )
       (display "largest-coin: ") (display largest-coin) (newline)
       (cond
         ((< 0 amount) (cond
              ((< 0 KINDS-OF-COINS) (cond
                     ((< 0 largest-coin) (let ()
                               (display "List of coin denominations: ")
                               (denomination-list KINDS-OF-COINS)
                               (display "count-change= ") (cc amount KINDS-OF-COINS)) )
                     (else (let () (display "Improper parameter value!\ncount-change= ") -1)) ))
               (else (let () (display "Improper parameter value!\ncount-change= ") -1)))) 
        (else(let ()
               (display "Improper parameter value!\ncount-change= ") -1)); else
        );cond                             
    );let
  );define
(define (cc amount kinds-of-coins)
  (cond ((= amount 0) 1) ;first branch
        (else (cond
                ((pier? (< amount 0) (= kinds-of-coins 0))
                 (+
                  (cc amount (- kinds-of-coins 1))
                  (cc (- amount (first-denomination kinds-of-coins)) kinds-of-coins )
                  ))
                (else 0)
                );cond
              );else cond
   );cond
 )
(define (pier? x? y? )
  (not (or? x? y?))
  )
(define (or? x? y?)
  (= 1(cond (x? 1) (else (cond (y? 1) (else 0)) ) ) )
  )
(define (denomination-list kinds-of-coins)
  (cond ((= kinds-of-coins 0) (let () (newline) 0))
      (else
       (let ()
         (display (first-denomination kinds-of-coins))
         (display " ")
         (denomination-list (- kinds-of-coins 1))))
   )
 )
(define (GR-AMOUNT)
  (remainder (+ (* 100 LAST-DIGIT-OF-GROUP-NUMBER) VARIANT) 231)
 )
(display "Variant ")
(display VARIANT)
(newline)
(newline)
(display (count-change 100)) (newline)
(display (count-change (GR-AMOUNT)))
(set! KINDS-OF-COINS 13) (newline)
(display (count-change 100)) (newline)
(display "(c) Nedosekov I.D. 2021\n")
