//
// Created by ASMX108 on 28/09/2019.
//

#ifndef SOLVER_RVMOSQUERA_NODE_H
#define SOLVER_RVMOSQUERA_NODE_H

#include <stack>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <vector>

typedef float tipoDato;

using namespace std;

class node {
protected:
    string data;
    int precedence;
    bool isOperator;
    char type;
    node *left = nullptr;
    node *right = nullptr;
public:
    node(string data) : data(data) {};

    virtual tipoDato execute() = 0;

    const string &getData() const {
        return data;
    }

    bool isOperator1() const {
        return isOperator;
    }

    node *getLeft() const {
        return left;
    }

    void setLeft(node *left) {
        node::left = left;
    }

    node *getRight() const {
        return right;
    }

    void setRight(node *right) {
        node::right = right;
    }

    int getPrecedence() const {
        return precedence;
    }

    char getType() const {
        return type;
    }

    void killSelf() {
        if (this->left)
            this->left->killSelf();
        else if (this->right)
            this->right->killSelf();

        delete this;
    }
};


#endif //SOLVER_RVMOSQUERA_NODE_H
