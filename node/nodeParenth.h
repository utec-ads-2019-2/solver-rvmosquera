//
// Created by ASMX108 on 01/10/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODEPARENTH_H
#define SOLVER_RVMOSQUERA_NODEPARENTH_H

#include "node.h"

class nodeParenth : public node{
public:
    nodeParenth(string data): node(data) {
        precedence = 0;
        isOperator = false;
        type = '(';
    };

    tipoDato execute() override {

        return 0;
    }
};


#endif //SOLVER_RVMOSQUERA_NODEPARENTH_H
