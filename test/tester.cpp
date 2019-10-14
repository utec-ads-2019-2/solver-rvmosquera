#include "tester.h"

void Tester::execute_test1() {
    auto *exp = new ExpressTree();

    string equations[] = {
            "7/4*((3+1)*3)+3",
            "2+(3)",
            "7/4*((1+2)^4*2)+3",
            "1-2*5/2+1-2^4+1",
            "((7*3)/4+6*(3^2)/2)",
            "((790*3)/4000             + 60*(3^       2)  /  20)",
            "((790*3)/4000+60*(3^2)/20)",
            "((19+45/16*100-(181^2-15*10)))"
    };

    float results[] = {
            24,
            5,
            286.5,
            -18,
            32.25,
            27.5925,
            27.5925,
            -32310.75
    };

    for (int i=0 ; i < 8 ; i++) {
        exp->generateFromInfixExp(equations[i]);
        exp->askvalueVariables();
        ASSERT(exp->evaluate() == results[i], "Wrong result in ", equations[i]);
    }

    delete exp;
}

void Tester::execute_test2() {
    auto *exp = new ExpressTree();

    string equations[] = {
            "7/4*((3+1)*3)+3",
            "7/4*((2+-+--8)*2)+3",
            "2+(3)",
            "7/4*((1+2)^4*2)+3",
            "1-2*5/2+1-2^4+1",
            "19+-+++-++++++9",
            "2+(3)",
            "((19--45/16*100-(181^2-15*10)))",
            "(5+-3)+(21/3*5)-(5^3-2)",
            "7*-1",
            "((7*3)/4+6*(3^2)/2)*(-1)"
    };

    float results[] = {
            24,
            -18,
            5,
            286.5,
            -18,
            28,
            5,
            -32310.75,
            -86,
            -7,
            -32.25
    };

    for (int i=0 ; i < 11 ; i++) {
        exp->generateFromInfixExp(equations[i]);
        exp->askvalueVariables();
        ASSERT(exp->evaluate() == results[i], "Wrong result in ", equations[i]);
    }
    delete exp;
}