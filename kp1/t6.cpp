/*  NID   */
#include "mlisp.h"
double __NID__try/*2*/ (double x);
double f/*3*/ (double x, double y);
//________________ 
double __NID__try/*2*/ (double x){
 x = f(x
	 , 2.)
	;
	return
 x;
	 }
double f/*3*/ (double x, double y){
 return
 expt(x
	 , y)
	;
	 }
int main(){
 display("Calculations!");
	 newline();
	 display(__NID__try(3.));
	 newline();
	 
std::cin.get();
	 return
 0;
	}

