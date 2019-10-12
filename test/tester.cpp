#include "tester.h"

void Tester::execute_test1() {
    auto *exp = new ExpressTree();

    string equations_test1[] = {
            "7/4*((3+1)*3)+3",
            "2+(3)",
            "7/4*((1+2)^4*2)+3",
            "1-2*5/2+1-2^4+1",
            "((7*3)/4+6*(3^2)/2)"
    };

    float results1[] = {
            24,
            5,
            286.5,
            -18,
            32.25
    };

    for (int i=0 ; i < 5 ; i++) {
        exp->generateFromInfixExp(equations_test1[i]);
        exp->askvalueVariables();
        ASSERT(exp->evaluate() == results1[i], "Wrong result in ", equations_test1[i]);
    }
}

void Tester::execute_test2() {
    string equations[] = {
            "7/4*((3+1)*3)+3",
            "7/4*((2+-+--8)*2)+3",
            "2+(3)",
            "7/4*((1+2)^4*2)+3",
            "7*-1",
            "1-2*5/2+1-2^4+1",
            "19+-+++-++++++9",
            "((7*3)/4+6*(3^2)/2)*(-1)",
            "(5+-3)+(21/3*5)-(5^3-2)",
            "((19--45/16*100-(181^2-15*10)))","2+(3)"
    };

    float results[] = {
            24,
            -18,
            5,
            286.5,
            -7,
            -18,
            28,
            -32.25,
            -86,
            -32310.75,5
    };
}
