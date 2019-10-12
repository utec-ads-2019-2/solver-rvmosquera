//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODECONS_H
#define SOLVER_RVMOSQUERA_NODECONS_H

#include "node.h"

class nodeCons : public node {
    int dataNumber=0;
public:
    nodeCons(string data):node(data) {
        dataNumber = atoi(data.c_str());
        isOperator = false;
        type = 'C';
    };

    tipoDato execute() override {
        return this->dataNumber;
    }

};

#endif //SOLVER_RVMOSQUERA_NODECONS_H