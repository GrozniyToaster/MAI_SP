/* $n17 */
#include "semantics.h"
using namespace std;
// Для удобного запонения бинарных форм (тип аргументов функции)
template <int N> struct binary {
  static const int value = (N % 10) + 2 * binary<N / 10>::value;
};

template <> struct binary<0> { static const int value = 0; };

template <int N> constexpr int binary_v = binary<N>::value;
template <int N> constexpr int BIN = binary_v<N>;

void tSM::init() {
  globals.clear();
  locals.clear();
  params.clear();
  scope = 0; // вне процедуры
  //константы:
  globals["e"] = tgName(VAR | DEFINED | BUILT);
  globals["pi"] = tgName(VAR | DEFINED | BUILT);

  // элементарные процедуры:
  globals["abs"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["atan"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["cos"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["exp"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["expt"] = tgName(PROC | DEFINED | BUILT, "", 2);
  globals["log"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["quotient"] = tgName(PROC | DEFINED | BUILT, "", 2);
  globals["remainder"] = tgName(PROC | DEFINED | BUILT, "", 2);
  globals["sin"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["sqrt"] = tgName(PROC | DEFINED | BUILT, "", 1);
  globals["tan"] = tgName(PROC | DEFINED | BUILT, "", 1);
}
int tSM::p01() { //        S -> PROG
  for (auto &[name, rec] : globals) {
    string description = name + " declared on " + rec.line;
    if (!rec.test(DEFINED)) {
      ferror_message += "Error[01-1]: " + description + " not defined\n";
      // a42 обявленная на 3 не определена
      // a42 declared on 3 not defined
      return 1;
    } else if (!rec.test(USED) && !rec.test(BUILT)) {
      ferror_message += "Warning[01-1]: " + description + " not used\n";
      // a определенная на 2 не использована
      // a defined on 2 not used
    }
  }
  return 0;
}
int tSM::p02() { //     PROG -> CALCS
  return 0;
}
int tSM::p03() { //     PROG -> DEFS
  return 0;
}
int tSM::p04() { //     PROG -> DEFS CALCS
  return 0;
}
int tSM::p05() { //        E -> $id
  string name = S1->name;
  switch (scope) {
  case 2:
    if (locals.count(name))
      break;
  case 1:
    if (params.count(name))
      break;
  default:
    tgName &ref = globals[name];
    if (ref.empty()) {
      ref = tgName(VAR | USED, S1->line);
      break;
    } // if(ref.empty())...
    if (ref.test(VAR)) {
      ref.set(USED);
      break;
    }
    if (ref.test(BUILT)) {
      ferror_message += "Error[05-1] in line " + S1->line + ": the built-in '" +
                        name +
                        "' procedure\n\t\t\t cannot be used as a variable!\n";
      //встроенную процедуру 'abs' нельзя использовать в качестве переменной
      // the built-in 'abs' procedure cannot be used as a variable
      return 1;
    }

    ferror_message +=
        "Error[05-2] in line " + S1->line + ": the name '" + name +
        "' cannot be used to refer to a variable;\n" +
        "\t\t\tit was previously declared as a procedure in line " + ref.line +
        "\n";
    //имя 'f' нельзя использовать для ссылки на переменную, в строке 1 оно ранее
    //объявлено как процедура
    // the name 'f' cannot be used to refer to a variable,
    // it was previously declared as a procedure in line 1
    return 1;

  } // switch...

  return 0;
}
int tSM::p06() { //        E -> $int
  return 0;
}
int tSM::p07() { //        E -> $dec
  return 0;
}
int tSM::p08() { //        E -> AREX
  return 0;
}
int tSM::p09() { //        E -> COND
  return 0;
}
int tSM::p10() { //        E -> EASYLET
  return 0;
}
int tSM::p11() { //        E -> CPROC
  return 0;
}
int tSM::p12() { //     AREX -> HAREX E )
  return 0;
}
int tSM::p13() { //    HAREX -> ( AROP
  return 0;
}
int tSM::p14() { //    HAREX -> HAREX E
  return 0;
}
int tSM::p15() { //     AROP -> +
  return 0;
}
int tSM::p16() { //     AROP -> -
  return 0;
}
int tSM::p17() { //     AROP -> *
  return 0;
}
int tSM::p18() { //     AROP -> /
  return 0;
}
int tSM::p19() { //  EASYLET -> HEASYL E )
  scope = 1;
  return 0;
}
int tSM::p20() { //   HEASYL -> ( let ( )
  scope = 2;
  return 0;
}
int tSM::p21() { //   HEASYL -> HEASYL INTER
  return 0;
}
int tSM::p22() { //     COND -> ( cond BRANCHES )
  return 0;
}
int tSM::p23() { // BRANCHES -> CLAUS ELSE
  return 0;
}
int tSM::p24() { //    CLAUS -> ( BOOL E )
  return 0;
}
int tSM::p25() { //     ELSE -> ( else ELSEB )
  return 0;
}
int tSM::p26() { //    ELSEB -> E
  return 0;
}
int tSM::p27() { //    ELSEB -> INTER ELSEB
  return 0;
}
int tSM::p28() { //      STR -> $str
  return 0;
}
int tSM::p29() { //      STR -> SCOND
  return 0;
}
int tSM::p30() { //    SCOND -> ( cond SBRANCHES )
  return 0;
}
int tSM::p31() { // SBRANCHES -> SELSE
  return 0;
}
int tSM::p32() { // SBRANCHES -> SCLAUS SBRANCHES
  return 0;
}
int tSM::p33() { //   SCLAUS -> ( BOOL STR )
  return 0;
}
int tSM::p34() { //    SELSE -> ( else STR )
  return 0;
}
int tSM::p35() { //    CPROC -> HCPROC )
  auto &ref = globals[S1->name];
  if (ref.test(DEFINED)) {
    if (S1->count != ref.arity) {
      ferror_message += "Error[35-1] in line " + S2->line + ": '" + S1->name +
                        "' defined on " + ref.line + " with " +
                        to_string(ref.arity) + " attributes, but call with " +
                        to_string(S1->count) + "\n";
      // "a" определяется на 1 с 2 атрибутами, но вызывается с 1
      // 'a' defined on 1 with 2 attributes, but call with 1
    }
  } else {
    ref.arity = S1->count;
  }
  S1->count = 0;
  return 0;
}
int tSM::p36() { //   HCPROC -> ( $id
  if (params.count(S2->name) || locals.count(S2->name)) {
    ferror_message += "Error[36-1] in line " + S2->line + ": '" + S2->name +
                      "' previous declared as variable\n";
    // 'f' previous declared as variable
    // 'f' ранее объявлялось как переменная
  }
  auto &ref = globals[S2->name];
  if (ref.empty()) {
    ref = tgName(PROC | USED, S2->line);
  } else if (ref.test(PROC)) {
    ref.set(USED);
  } else { // попали в переменную
    ferror_message += "Error[36-2] in line " + S2->line + ": procedure '" +
                      S2->name +
                      "'has the same name \n"
                      "\t\t\tas global var on line " +
                      ref.line + "\n";
    // процедура 'pr' имеет то же имя что и глобальная переменная на строке 12
    // procedure 'pr' has the same name as the global variable on line 12
    return 1;
  }
  S1->name = move(S2->name);
  S1->count = 0;
  return 0;
}
int tSM::p37() { //   HCPROC -> HCPROC E
  ++(S1->count);
  auto &ref = globals[S1->name];
  if (!ref.test(DEFINED)) {
    ref.types = (1 << S1->count) | ref.types;
    ++ref.arity;
  } else {
    if (ref.arity < S1->count) {
      ferror_message += "Error[37-1] in line " + S2->line + ": procedure '" +
                        S1->name + "' declared on line " + ref.line + " has " +
                        to_string(ref.arity) +
                        " attributes"
                        ", " +
                        to_string(S1->count) + " are specified.\n";
      // процедура 'pr' объявленная на строке 15 имеет 4 атрибута, указано 5
      // procedure 'pr' declared on line 15 has 4 attributes, specified 5
      return 1;
    }
  }
  return 0;
}
int tSM::p38() { //     BOOL -> $bool
  return 0;
}
int tSM::p39() { //     BOOL -> $idq
  string name = S1->name;
  switch (scope) {
  case 1:
    if (params.count(name))
      break;
  default:
    tgName &ref = globals[name];
    if (ref.empty()) {
      ref = tgName(PROC | USED, S1->line);
      break;
    } // if(ref.empty())...
    if (ref.test(PROC)) {
      ref.set(USED);
      break;
    }
    return 1;

  } // switch...

  return 0;
}
int tSM::p40() { //     BOOL -> REL
  return 0;
}
int tSM::p41() { //     BOOL -> ( not BOOL )
  return 0;
}
int tSM::p42() { //     BOOL -> CPRED
  return 0;
}
int tSM::p43() { //    CPRED -> HCPRED )
  auto &ref = globals[S1->name];
  if (ref.test(DEFINED)) {
    if (ref.arity != S1->count) {
      ferror_message +=
          "Error[43-1] in line " + S1->line + ": the arity of the predicate " +
          S1->name + " differs from that declared on line " + ref.line + "\n";
      // арность предиката a? отличается от того, что объявлено в строке 1
      // arity of the predicate a? different from what is declared in line 1
      return 1;
    }
  } else {
    ref.arity = S1->count;
  }
  S1->count = 0;
  return 0;
}
int tSM::p44() { //   HCPRED -> ( $idq
  auto &ref = globals[S2->name];
  if (ref.empty()) {
    ref = tgName(PROC | USED, S2->line);
  } else {
    ref.set(USED);
  }
  S1->name = move(S2->name);
  S1->count = 0;
  return 0;
}
int tSM::p45() { //   HCPRED -> HCPRED ARG
  auto &ref = globals[S1->name];
  ++S1->count;
  if (ref.test(DEFINED)) {
    if (ref.arity >= S1->count) {
      if (S2->types) {
        if (((1 << (S1->count - 1)) | ref.types) != ref.types) {
          ferror_message += "Error[45-1] in line " + S1->line + ": predicate " +
                            S1->name + " type of parameter on position " +
                            to_string(S1->count) +
                            " differ with declared before on " + ref.line +
                            ".\nExpected bool\n";
          // предикат a? тип параметра в позиции 1 отличается от объявленного
          // ранее на 1. Ожидаллся bool. predicate a? type of parameter on
          // position 1 differ with declared before on 1. Expected bool
          return 1;
        }
      } else {
        if (((1 << (S1->count - 1)) & ref.types) != 0) {
          ferror_message +=
              "Error[45-2] in line " + S1->line + ": predicate " + S1->name +
              " type of parameter on position " + to_string(S1->count) +
              " differ with declared before on " + ref.line + ".\nExpected E\n";
          // предикат a? тип параметра в позиции 1 отличается от объявленного
          // ранее в позиции 1. Ожидался Е. predicate a? type of parameter on
          // position 2 differ with declared before on 1. Expected E.
          return 1;
        }
      }
    }
  } else {
    if (S2->types) {
      ref.types |= 1 << (S1->count - 1);
    }
  }
  return 0;
}
int tSM::p46() { //      ARG -> E
  S1->types = 0;
  return 0;
}
int tSM::p47() { //      ARG -> BOOL
  S1->types = 1;
  return 0;
}
int tSM::p48() { //      REL -> ( = E E )
  return 0;
}
int tSM::p49() { //      REL -> ( < E E )
  return 0;
}
int tSM::p50() { //      SET -> HSET E )
  return 0;
}
int tSM::p51() { //     HSET -> ( set! $id
  auto &id = S3->name;
  switch (scope) {
  case 2:
    if (locals.count(id))
      break;
  case 1:
    if (params.count(id))
      break;
  default:
    tgName &ref = globals[id];
    if (ref.empty()) {
      ref = tgName(VAR | USED, S3->line);
      break;
    } else if (ref.test(VAR | BUILT)) {
      ferror_message += "Error[51-1] in line " + S3->line +
                        ": the built-in var '" + id + "' cannot be changed\n";
      // встроенная переменная e не может быть изменена
      // the built-in variable e cannot be changed
      return 1;
    } else if (ref.test(VAR)) {
      ref.set(USED);
    } else { // точно процедура
      ferror_message += "Error[51-2] in line " + S3->line + ": the name '" +
                        id + "' defined on " + ref.line +
                        " cannot be used as a variable\n";
      // имя "f", определенное на 15, не может использоваться в качестве
      // переменной the name 'f' defined on 15 cannot be used as a variable
      return 1;
    }
  } // switch...

  return 0;
}
int tSM::p52() { //  DISPSET -> ( display E )
  return 0;
}
int tSM::p53() { //  DISPSET -> ( display BOOL )
  return 0;
}
int tSM::p54() { //  DISPSET -> ( display STR )
  return 0;
}
int tSM::p55() { //  DISPSET -> ( newline )
  return 0;
}
int tSM::p56() { //  DISPSET -> SET
  return 0;
}
int tSM::p57() { //    INTER -> DISPSET
  return 0;
}
int tSM::p58() { //    INTER -> E
  return 0;
}
int tSM::p59() { //    CALCS -> CALC
  return 0;
}
int tSM::p60() { //    CALCS -> CALCS CALC
  return 0;
}
int tSM::p61() { //     CALC -> E
  return 0;
}
int tSM::p62() { //     CALC -> BOOL
  return 0;
}
int tSM::p63() { //     CALC -> STR
  return 0;
}
int tSM::p64() { //     CALC -> DISPSET
  return 0;
}
int tSM::p65() { //     DEFS -> DEF
  return 0;
}
int tSM::p66() { //     DEFS -> DEFS DEF
  return 0;
}
int tSM::p67() { //      DEF -> PRED
  return 0;
}
int tSM::p68() { //      DEF -> VAR
  return 0;
}
int tSM::p69() { //      DEF -> PROC
  auto &ref = globals[S1->name];
  if (ref.test(USED)) {
    if (ref.arity != S1->count) {
      ferror_message += "Error[69-1] in line " + S1->line + ": procedure " +
                        S1->name + " declared on " + ref.line + " with " +
                        to_string(ref.arity) +
                        " attributes"
                        "\n\tbut defined with " +
                        to_string(S1->count) + "\n";
      // процедура f объявлена на 1 с 2 атрибутами, но определенными с 1
      // procedure  f is declared on 1 with 2 attributes, but defined with 1
      return 1;
    }
  }
  ref.arity = S1->count;
  S1->count = 0;
  return 0;
}
int tSM::p70() { //     PRED -> HPRED BOOL )
  scope = 0;
  params.clear();
  return 0;
}
int tSM::p71() { //    HPRED -> PDPAR )
  auto &idq = globals[S1->name];
  if (idq.test(USED)) {
    if (idq.arity != S1->count) {
      ferror_message +=
          "Error[71-1] in line " + S1->line +
          ": the arity of the predicate differs from that declared on line " +
          idq.line + "\n";
      // арность предиката отличается от объявленного на  строке 2
      // the arity of the predicate differs from that declared on line 2
      return 1;
    }
  } else {
    idq.arity = S1->count;
  }
  S1->count = 0;
  scope = 1;
  return 0;
}
int tSM::p72() { //    PDPAR -> ( define ( $idq
  auto &idq = globals[S4->name];
  if (idq.test(DEFINED)) {
    ferror_message += "Error[72-1] in line " + S1->line + ": predicate " +
                      S1->name + " previous defined on " + idq.line + "\n";
    // предикат, ранее определенный на 2
    // predicate previous defined on 2
    return 1;
  } else if (idq.test(USED)) {
    idq.set(idq.properties | DEFINED | PROC);
  } else {
    idq = tgName(DEFINED | PROC, S4->line);
  }

  S1->name = move(S4->name);
  S1->count = 0;
  params.clear();
  return 0;
}
int tSM::p73() { //    PDPAR -> PDPAR $idq
  auto &ref = globals[S1->name];
  ++S1->count;
  if (params.count(S2->name)) {
    ferror_message += "Error[73-1] in line " + S1->line + ": predicate " +
                      S1->name + " parameter " + S2->name + " duplicated\n";
    // параметр b? дублируется
    // parameter b? duplicated
    return 1;
  } else if (S1->name == S2->name) {
    ferror_message += "Warning[73-1] in line " + S1->line + ": predicate " +
                      S1->name + " parameter " + S2->name +
                      " obscures name of predicate\n";
    // параметр a? затеняет имя предиката
    // parameter a? obscures the predicate name
  }
  params.insert(S2->name);

  if (ref.test(USED)) {
    if (ref.arity >= S1->count) {
      if (((1 << (S1->count - 1)) | ref.types) != ref.types) {
        ferror_message += "Error[73-2] in line " + S1->line + ": predicate " +
                          S1->name + " type of parameter " + S2->name +
                          " differ with declared before on " + ref.line + "\n";
        // тип параметра b? отличается от объявленного ранее на 2
        // type of parameter b? differ with declared before on 2
        return 1;
      }
    }
  } else {
    ref.types |= 1 << (S1->count - 1);
  }
  return 0;
}
int tSM::p74() { //    PDPAR -> PDPAR $id
  auto &ref = globals[S1->name];
  ++S1->count;
  if (params.count(S2->name)) {
    ferror_message += "Error[74-1] in line " + S1->line + ": predicate " +
                      S1->name + " parameter " + S2->name + " duplicated\n";
    // параметр b дублирован
    // parameter b duplicated
    return 1;
  } else {
    params.insert(S2->name);
  }
  if (ref.test(USED)) {
    if (ref.arity >= S1->count) {
      if (((1 << (S1->count - 1)) & ref.types) != 0) {
        ferror_message += "Error[74-2] in line " + S1->line + ": predicate " +
                          S1->name + " type of parameter " + S2->name +
                          " differ with declared before on " + ref.line + "\n";
        // тип параметра c отличается от объявленного ранее на 2
        // type of parameter c differ with declared before on 2
        return 1;
      }
    }
  }

  return 0;
}
int tSM::p75() { //      VAR -> VARDCL E )
  return 0;
}
int tSM::p76() { //   VARDCL -> ( define $id
  auto &ref = globals[S3->name];
  if (ref.empty()) {
    ref = tgName(VAR | DEFINED, S3->line);
    return 0;
  } else if (ref.test(VAR | USED)) {
    ref.set(ref.properties | DEFINED);
    return 0;
  }
  ferror_message +=
      "Error[76-1] in line " + S3->line + ": the name '" + S3->name +
      "' is already defined as " +
      ((ref.test(VAR)) ? "variable" : ("procedure " + Uint_to_str(ref.types))) +
      " in line " + ref.line + ".\n";
  // имя f уже определено как переменная в строке 15
  // the name f is already defined as variable in line 15
  return 1;
}
int tSM::p77() { //     PROC -> HPROC BLOCK )
  params.clear();
  scope = 0;
  return 0;
}

int tSM::p78() { //     PROC -> HPROC E )
  params.clear();
  scope = 0;
  return 0;
}
int tSM::p79() { //    HPROC -> PCPAR
  scope = 1;
  return 0;
}
int tSM::p80() { //    HPROC -> HPROC INTER
  return 0;
}
int tSM::p81() { //    PCPAR -> ( define ( $id
  auto &ref = globals[S4->name];
  if (ref.empty()) {
    ref = tgName(PROC | DEFINED, S4->line);
  } else if (ref.test(PROC)) {
    if (ref.test(BUILT)) {
      ferror_message += "Error[81-1] in line " + S4->line + ": procedure '" +
                        S4->name +
                        "' has the same name "
                        "as global procedure\n";
      // процедура 'abs' имеет то же имя что и глобальная процедура
      // procedure 'pr' has the same name as the global procedure
      return 1;
    } else if (ref.test(DEFINED)) { //
      ferror_message += "Error[81-2] in line " + S4->line + ": procedure '" +
                        S4->name + "' duplicates what is defined in line  " +
                        ref.line + "\n";
      // процедура a  дублирует определенное в строке 74
      // procedure a duplicates what is defined in line 74
      return 1;
    }
    ref.set(DEFINED);
  } else { // попали в переменную
    ferror_message += "Error[81-3] in line " + S4->line + ": procedure '" +
                      S4->name +
                      "' has the same name \n"
                      "\t\t\tas global var on line " +
                      ref.line + "\n";
    // процедура 'pr' имеет то же имя что и глобальная переменная на строке 12
    // procedure 'pr' has the same name as the global variable on line 12
    return 1;
  }
  S1->name = move(S4->name);
  params.clear();
  S1->count = 0;
  return 0;
}
int tSM::p82() { //    PCPAR -> PCPAR $id
  auto &id = S2->name;
  if (!params.count(id)) {
    if (id == S1->name) {
      ferror_message += "Warning[82-1] in line " + S2->line + ": procedure " +
                        id + " has same name as as its parameter!\n";
      //у процедуры 'f' такое же имя, как у ее параметра
      // procedure 'f' has the same name as its parameter
    }
    params.insert(id);
    S1->count++;
    return 0;
  }
  ferror_message += "Error[82-1] in line " + S1->line + ": procedure '" +
                    S1->name + "' has two identical parameters " + id + "\n";
  // процедура 'f' имеет два одинаковых параметра a
  // procedure 'f' has two identical parameters a

  return 1;
}
int tSM::p83() { //    BLOCK -> HBLOCK E )
  scope = 1;
  locals.clear();
  return 0;
}
int tSM::p84() { //   HBLOCK -> BLVAR )
  scope = 2;
  return 0;
}
int tSM::p85() { //   HBLOCK -> HBLOCK INTER
  return 0;
}
int tSM::p86() { //    BLVAR -> ( let ( LOCDEF
  return 0;
}
int tSM::p87() { //    BLVAR -> BLVAR LOCDEF
  return 0;
}
int tSM::p88() { //   LOCDEF -> ( $id E )
  if (locals.count(S2->name)) {
    ferror_message += "Error[88-1] in line " + S2->line + ": variable '" +
                      S2->name +
                      "'"
                      " duplicates locally\n";
    return 1;
    // переменная x дублируется локально
    // variable x duplicates locally
  }
  if (params.count(S2->name)) {
    ferror_message += "Warning[88-1] in line " + S2->line + ": variable '" +
                      S2->name +
                      "'"
                      " overrides the parameter locally\n";
    // переменная x перекрывает локально параметр
    // the variable x overrides the parameter locally
  }
  locals.insert(move(S2->name));
  return 0;
}
//_____________________
int tSM::p89() { return 0; }
int tSM::p90() { return 0; }
int tSM::p91() { return 0; }
int tSM::p92() { return 0; }
int tSM::p93() { return 0; }
int tSM::p94() { return 0; }
int tSM::p95() { return 0; }
int tSM::p96() { return 0; }
int tSM::p97() { return 0; }
int tSM::p98() { return 0; }
int tSM::p99() { return 0; }
int tSM::p100() { return 0; }
int tSM::p101() { return 0; }
int tSM::p102() { return 0; }
int tSM::p103() { return 0; }
int tSM::p104() { return 0; }
int tSM::p105() { return 0; }
int tSM::p106() { return 0; }
int tSM::p107() { return 0; }
int tSM::p108() { return 0; }
int tSM::p109() { return 0; }
int tSM::p110() { return 0; }
