//golden21.cpp
#include "mlisp.h"

double fun(double x);
double golden__section__search(double a, double b);
double golden__start(double a, double b);
double __nid__try(double a, double b, double xa, double ya, double xb, double yb);
bool close__enough_Q(double x, double y);

extern double a;
extern double b;
extern double mphi;
extern double tolerance;
extern double total__iterations;
extern double xmin;

double a = -5.; double b = -3.;

double fun(double x) {
    x = x - 17. / 18.;
    return  exp(-x) * sin(x + pi) + cos(x) - 0.13;
}

double golden__section__search(double a, double b) {
    {//let
        double xmin((a < b) ? golden__start(a, b) : golden__start(b, a));
        newline();
        return xmin;
    }//let
}

double golden__start(double a, double b) {
    total__iterations = 0.;
    {//let
        double xa(a + mphi * (b - a)),
            xb(b +( - mphi * (b - a) ) );
        return __nid__try(a, b, xa, fun(xa), xb, fun(xb));
    }//let
}

double mphi = (3. - sqrt(5.)) * (1. / 2.0);

double __nid__try(double a, double b, double xa, double ya, double xb, double yb) {
    return close__enough_Q(a, b) ? ((a + b) * 0.5)
        : (display("+"),
            (total__iterations = total__iterations + 1.),
            (ya < yb) ? ((b = xb), (xb = xa), (yb = ya), (xa = a + mphi * (b - a)), __nid__try(a, b, xa, fun(xa), xb, yb))
            : ((a = xa), (xa = xb), (ya = yb), (xb = b - mphi * (b - a)), __nid__try(a, b, xa, ya, xb, fun(xb)))
        );


}

bool close__enough_Q(double x, double y) {
    return (abs(x - y) < tolerance);
}
double tolerance = 0.001;
double total__iterations = 0.;
double xmin = 0.;

int main() {

    xmin = golden__section__search(a, b);
    display("Interval=\t[");
    display(a);
    display(" , ");
    display(b);
    display("]");
    newline();
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
    return 0;
}

