//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODESUBOPE_H
#define SOLVER_RVMOSQUERA_NODESUBOPE_H

#include "node.h"

class nodeSubOpe : public node{
public:
    nodeSubOpe(string data): node(data) {
        precedence = 1;
        isOperator = true;
        type = '-';
    };

    tipoDato execute() override {
        auto a = getLeft()->execute();
        auto b = getRight()->execute();

        return a - b;
    }
};


#endif //SOLVER_RVMOSQUERA_NODESUBOPE_H
