//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODESUMOPE_H
#define SOLVER_RVMOSQUERA_NODESUMOPE_H

#include "node.h"

class nodeSumOpe : public node {

public:
    nodeSumOpe(string data): node(data) {
        precedence = 1;
        isOperator = true;
        type = '+';
    };

    tipoDato execute() override {
        auto a = getLeft()->execute();
        auto b = getRight()->execute();

        return a + b;
    }
};


#endif //SOLVER_RVMOSQUERA_NODESUMOPE_H