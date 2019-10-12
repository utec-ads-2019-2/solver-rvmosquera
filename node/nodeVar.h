//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODEVAR_H
#define SOLVER_RVMOSQUERA_NODEVAR_H

#include "node.h"

class nodeVar : public node{
private:
    int value;
public:
    nodeVar(string data):node(data) {
        value = 0;
        type = 'V';
        isOperator = false;
    };

    void setValue(int value) {
        nodeVar::value = value;
    }

    tipoDato execute() override {

        return value;
    }
};


#endif //SOLVER_RVMOSQUERA_NODEVAR_H