//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODEPOWOPE_H
#define SOLVER_RVMOSQUERA_NODEPOWOPE_H

#include "node.h"

class nodePowOpe : public node{
public:
    nodePowOpe(string data): node(data) {
        precedence = 3;
        isOperator = true;
        type = '^';
    };

    retDataType execute() override {
        auto a = getLeft()->execute();
        auto b = getRight()->execute();

        return pow(a, b);
    }
};


#endif //SOLVER_RVMOSQUERA_NODEPOWOPE_H