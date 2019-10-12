//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODEDIVOPE_H
#define SOLVER_RVMOSQUERA_NODEDIVOPE_H

#include "node.h"

class nodeDivOpe : public node{
public:
    nodeDivOpe(string data): node(data) {
        precedence = 2;
        isOperator = true;
        type = '/';
    };

    tipoDato execute() override {
        auto a = getLeft()->execute();
        auto b = getRight()->execute();

        return a / b;
    }
};


#endif //SOLVER_RVMOSQUERA_NODEDIVOPE_H