/*  NID   */
#include "mlisp.h"
extern double a/*2*/;
extern double b/*2*/;
double fun/*3*/ (double x);
double golden__section__search/*7*/ (double a, double b);
double golden__start/*15*/ (double a, double b);
extern double mphi/*24*/;
double __NID__try/*25*/ (double a, double b
	, double xa, double ya
	, double xb, double yb);
bool close__enough_Q /*49*/ (double x, double y);
extern double tolerance/*51*/;
extern double total__iterations/*52*/;
extern double xmin/*53*/;
//________________ 
double a/*2*/ = -5.;
double b/*2*/ = -3.;
double fun/*3*/ (double x){
	x = (x - (17. / 18.));
	return
	((exp((- x)) * sin((x + pi))) + cos(x) + (- .13e+0));
	}
double golden__section__search/*7*/ (double a, double b){
	{//let
	double xmin(((a < b) ? golden__start(a
	, b)
	 : (golden__start(b
	, a)
	)));
	newline();
	return
	xmin;
}//let
}
double golden__start/*15*/ (double a, double b){
	total__iterations = 0.;
	{//let
	double xa((a + (mphi * (b - a)))),
	xb((b + (- (mphi * (b - a)))));
	return
	__NID__try(a
	, b
	, xa
	, fun(xa)
	, xb
	, fun(xb))
	;
}//let
}
double mphi/*24*/ = ((3. - sqrt(5.)) * (1. / 2.0e+0));
double __NID__try/*25*/ (double a, double b
	, double xa, double ya
	, double xb, double yb){
	return
	(close__enough_Q(a
	, b)
 ? ((a + b) * 0.5e+0) : (((display("+")),
	(total__iterations = (total__iterations + 1.)),
	((ya < yb) ? ((b = xb),
	(xb = xa),
	(yb = ya),
	(xa = (a + (mphi * (b - a)))),
	__NID__try(a
	, b
	, xa
	, fun(xa)
	, xb
	, yb)
	) : ((a = xa),
	(xa = xb),
	(ya = yb),
	(xb = (b - (mphi * (b - a)))),
	__NID__try(a
	, b
	, xa
	, ya
	, xb
	, fun(xb))
	)))));
	}
bool close__enough_Q /*49*/ (double x, double y){
	return
	(abs((x - y)) < tolerance);}
double tolerance/*51*/ = .1e-2;
double total__iterations/*52*/ = 0.;
double xmin/*53*/ = 0.;
int main(){
	xmin = golden__section__search(a
	, b)
	;
	display("Interval=\t[");
	display(a);
	display(" , ");
	display(b);
	display("]\n");
	display("Total number of iteranions=");
	display(total__iterations);
	newline();
	display("xmin=\t\t");
	display(xmin);
	newline();
	display("f(xmin)=\t");
	display(fun(xmin));
	newline();
	std::cin.get();
	return
	0;
}

