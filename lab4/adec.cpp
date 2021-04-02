
//               adec.cpp
#include <iostream>
#include <iomanip>
#include "fsm.h"
using namespace std;

int main(){
    addstr(Adec, 0, "+-", 1);
    addstr(Adec, 0, ".", 3);
    addrange(Adec, 0, '0', '9', 2);

    addrange(Adec, 1, '0', '9', 2);
    addstr(Adec, 1, ".", 3);

    addrange(Adec, 2, '0', '9', 2);
    addstr(Adec, 2, ".", 3);

    addrange(Adec, 3, '0', '9', 4);

    addrange(Adec, 4, '0', '9', 4);
    addstr(Adec, 4, "eE", 5);

    addstr(Adec, 5, "+-", 6);

    addrange(Adec, 6, '0', '9', 7);

    addrange(Adec, 7, '0', '9', 7);

    Adec.final(7);

    cout << "Number of states = " << Adec.size() << "\n";

    while (true){
        char input[81];
        cout << ">";
        cin.getline(input, 81);
        std::cout << input << std::endl;
        if (!*input) break;
        int res = Adec.apply(input);
        cout << setw(res ? res + 1 : 0) << "^" << endl;
    }
    return 0;
}

