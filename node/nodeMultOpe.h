//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODEMULTOPE_H
#define SOLVER_RVMOSQUERA_NODEMULTOPE_H

#include "node.h"

class nodeMultOpe : public node{

public:
    nodeMultOpe(string data): node(data) {
        precedence = 2;
        isOperator = true;
        type = '*';
    };

    tipoDato execute() override {
        auto a = getLeft()->execute();
        auto b = getRight()->execute();

        return a * b;
    }
};


#endif //SOLVER_RVMOSQUERA_NODEMULTOPE_H
