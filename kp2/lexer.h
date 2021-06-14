//                 lexer.h 2021
#ifndef LEXER_H
#define LEXER_H
#include "baselexer.h"

#define addalpha(F, X, Y)\
  addrange(F, X, 'A', 'Z', Y);\
  addrange(F, X, 'a', 'z', Y);\


#define addalphanum(F, X, Y)\
  addalpha(F, X, Y);\
  addrange(F, X, '0', '9', Y);\


class tLexer:public tBaseLexer{
public:
//конструктор
 tLexer():tBaseLexer(){
//создать автоматы:

//________________________________________

// вещественное
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
//________________________________________

// идентификатор
  addalpha(Aid, 0, 1);
  addstr(Aid, 0, "!", 1);
  addstr(Aid, 0, "?", 2);

  addalphanum(Aid, 1, 1);
  addstr(Aid, 1, "!-", 1);
  addstr(Aid, 1, "?", 2);

  addalphanum(Aid, 2, 1);
  addstr(Aid, 2, "!", 1);
  addstr(Aid, 2, "?", 2);
  addstr(Aid, 2, "-", 3);

  addalphanum(Aid, 3, 1);
  addstr(Aid, 3, "!-", 1);
  Aid.final(1);
  Aid.final(3);
//________________________________________

// идентификатор предиката
  addstr(Aidq, 0, "?", 1);
  addalpha(Aidq, 0, 2);
  addstr(Aidq, 0, "-", 2);
  addstr(Aidq, 0, "!", 3);

  addstr(Aidq, 1, "?", 1);
  addalphanum(Aidq, 1, 2);
  addstr(Aidq, 1, "-", 2);
  addstr(Aidq, 1, "!", 3);

  addstr(Aidq, 2, "?", 1);
  addalphanum(Aidq, 2, 2);
  addstr(Aidq, 2, "-", 2);
  addstr(Aidq, 2, "!", 3);

  addalphanum(Aidq, 3, 2);
  addstr(Aidq, 3, "-", 2);
  addstr(Aidq, 3, "!", 3);
  Aidq.final(1);
}
};
#endif

