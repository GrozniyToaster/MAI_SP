/*  NID   */
#include "mlisp.h"
extern double VARIANT/*2*/;
extern double LAST__DIGIT__OF__GROUP__NUMBER/*3*/;
extern double KINDS__OF__COINS/*4*/;
double first__denomination/*6*/ (double kinds__of__coins);
double count__change/*18*/ (double amount);
double cc/*39*/ (double amount, double kinds__of__coins);
bool pier_Q /*52*/ (bool x_Q, bool y_Q);
bool or_Q /*55*/ (bool x_Q, bool y_Q);
double denomination__list/*58*/ (double kinds__of__coins);
double GR__AMOUNT/*67*/ ();
//________________ 
double VARIANT/*2*/ = 17.;
double LAST__DIGIT__OF__GROUP__NUMBER/*3*/ = 6.;
double KINDS__OF__COINS/*4*/ = 4.;
double first__denomination/*6*/ (double kinds__of__coins){
	return
	((kinds__of__coins == 1.) ? 2.
	: (((kinds__of__coins == 2.) ? 5.
	: (((kinds__of__coins == 3.) ? 15.
	: (((kinds__of__coins == 4.) ? 25.
	: (0.))))))));
	}
double count__change/*18*/ (double amount){
	display("______\n amount: ");
	display(amount);
	newline();
	display("KINDS-OF-COINS: ");
	display(KINDS__OF__COINS);
	newline();
	{//let
	double largest__coin(first__denomination(KINDS__OF__COINS));
	display("largest-coin: ");
	display(largest__coin);
	newline();
	return
	((0. < amount) ? ((0. < KINDS__OF__COINS) ? ((0. < largest__coin) ? ((display("List of coin denominations: ")),
	(denomination__list(KINDS__OF__COINS)),
	(display("count-change= ")),
	cc(amount
	, KINDS__OF__COINS)
	)
	: (((display("Improper parameter value!\ncount-change= ")),
	-1.)))
	: (((display("Improper parameter value!\ncount-change= ")),
	-1.)))
	: (((display("Improper parameter value!\ncount-change= ")),
	-1.)));
}//let
}
double cc/*39*/ (double amount, double kinds__of__coins){
	return
	((amount == 0.) ? 1.
	: ((pier_Q((amount < 0.)
	, (kinds__of__coins == 0.))
 ? (cc(amount
	, (kinds__of__coins - 1.))
	 + cc((amount - first__denomination(kinds__of__coins))
	, kinds__of__coins)
	)
	: (0.))));
	}
bool pier_Q /*52*/ (bool x_Q, bool y_Q){
	return
	!(or_Q(x_Q
	, y_Q)
);}
bool or_Q /*55*/ (bool x_Q, bool y_Q){
	return
	(1. == (x_Q ? 1.
	: ((y_Q ? 1.
	: (0.)))));}
double denomination__list/*58*/ (double kinds__of__coins){
	return
	((kinds__of__coins == 0.) ? ((newline()),
	0.)
	: (((display(first__denomination(kinds__of__coins))),
	(display(" ")),
	denomination__list((kinds__of__coins - 1.)))));
	}
double GR__AMOUNT/*67*/ (){
	return
	remainder(((100. * LAST__DIGIT__OF__GROUP__NUMBER) + VARIANT)
	, 231.)
	;
	}
int main(){
	display("Variant ");
	display(VARIANT);
	newline();
	newline();
	display(count__change(100.));
	newline();
	display(count__change(GR__AMOUNT()));
	KINDS__OF__COINS = 13.;
	newline();
	display(count__change(100.));
	newline();
	display("(c) Nedosekov I.D. 2021\n");
	std::cin.get();
	return
	0;
}

