/*  NID   */
#include "mlisp.h"
double __NID__try/*2*/ (double x);
//________________ 
double __NID__try/*2*/ (double x){
 x = sin(x);
	return
	x;
	 }
int main(){
 display("Calculations!");
	 newline();
	 display(__NID__try(2.));
	 newline();
	 
std::cin.get();
	 return
 0;
	}

