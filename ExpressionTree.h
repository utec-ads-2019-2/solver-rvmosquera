//
// Created by ASMX108 on 02/10/2019.
//

#include <algorithm>
#include "node/nodeCons.h"
#include "node/nodeVar.h"
#include "node/nodePowOpe.h"
#include "node/nodeDivOpe.h"
#include "node/nodeSumOpe.h"
#include "node/nodeSubOpe.h"
#include "node/nodeMultOpe.h"
#include "node/nodeParenth.h"

#ifndef SOLVER_RVMOSQUERA_TREEEXPRESSION_H
#define SOLVER_RVMOSQUERA_TREEEXPRESSION_H

class ExpressTree {
private:
    node *root;
    stack<node *> *postFix;
    vector<nodeVar *> *variables;
    node * prevNode;
public:
    ExpressTree() {
        root = nullptr;
        postFix = new stack<node *>();
    }

    float evaluate() {
        return this->root->execute();
    }

    void generateFromInfixExp(string infixExp) {
        auto stack2 = new stack<node *>();
        node *newNode = nullptr;
        string numberStr;
        string alphaStr;
        int sum_sub=0;

        variables = new vector<nodeVar *>();
        prevNode = nullptr;
        for (auto it = infixExp.begin(); it != infixExp.end(); ++it) {
            auto character = *it;

            if (isdigit(character)) {
                numberStr = numberStr + character;

            } else if (isalpha(character)) {
                alphaStr = alphaStr + character;

            /*} else if ( character == '+' ) {

                if ( prevNode->getType() == '+' || prevNode->getType() == '-' )
                    sum_sub = sum_sub * 1;
                else
                    sum_sub = 1;

            } else if ( character == '-' ) {

                if ( prevNode->getType() == '+' || prevNode->getType() == '-' )
                    sum_sub = sum_sub * -1;
                else
                    sum_sub = -1;*/

            } else {
                if (numberStr != "") {
                    newNode = new nodeCons(numberStr);
                    postFix->push(newNode);
                    numberStr = "";

                    prevNode = newNode;
                }

                getVariable(&alphaStr);

                /*if ( sum_sub < 0 ) {
                    newNode = new nodeSubOpe(string(1, '-'));

                    validatePrecedence(stack2, newNode);
                    prevNode = newNode;
                    sum_sub = 0;
                    continue;

                } else if (sum_sub > 0 ) {
                    newNode = new nodeSumOpe(string(1, '+'));

                    validatePrecedence(stack2, newNode);
                    prevNode = newNode;
                    sum_sub = 0;
                    continue;
                }*/

                switch (character) {
                    case ' ':
                        continue;
                    case '(': {
                        newNode = new nodeParenth(string(1, character));
                        stack2->push(newNode);
                        prevNode = newNode;
                    }
                        break;

                    case ')': {
                        auto node = stack2->top();
                        newNode = new nodeParenth(string(1, character));

                        while (node->getType() != '(') {
                            postFix->push(node);
                            stack2->pop();
                            node = stack2->top();
                        }

                        if (node->getType() == '(')
                            stack2->pop();

                        prevNode = newNode;
                    }
                        break;
                    default: { // is operator
                        newNode = moveOperators(character);
                        validatePrecedence(stack2, newNode);

                        prevNode = newNode;
                    }
                }
            }

            if (it == infixExp.end() - 1) {
                if (numberStr != "")
                    postFix->push(new nodeCons(numberStr));

                getVariable(&alphaStr);

                while (!stack2->empty()) {
                    postFix->push(stack2->top());
                    stack2->pop();
                }
            }
        }
        buildTree();
    }

    void getVariable(string *alphaStr) const {

        string aux = *alphaStr;

        if (*alphaStr != "") {
            auto exists = find_if(variables->begin(), variables->end(),
                                  [aux](nodeVar *var) { return var->getData() == aux; }
            );

            if (exists != variables->end()) {
                postFix->push(*exists);
            } else {
                auto pNodeVar = new nodeVar(*alphaStr);
                postFix->push(pNodeVar);
                variables->push_back(pNodeVar);
            }

            *alphaStr = "";
        }
    }

    void buildTree() {//Tree
        auto stack2 = new stack<node *>();

        while (!postFix->empty()) {
            stack2->push(postFix->top());
            postFix->pop();
        }

        while (!stack2->empty()) {
            auto node = stack2->top();

            if (node->isOperator1()) {
                auto nodeRight = postFix->top();
                postFix->pop();
                auto nodeLeft = postFix->top();
                postFix->pop();

                node->setRight(nodeRight);
                node->setLeft(nodeLeft);
            }
            postFix->push(node);
            stack2->pop();
        }
        if (!postFix->empty()) {
            root = postFix->top();
            postFix->pop();
        }
    }

    void askvalueVariables() {
        int value;
        for (auto elem: *variables) {
            cout << "Value for variable " << elem->getData() << " = ";
            cin >> value;
            elem->setValue(value);
        }
    }

    void printPostFix() {
        while (!postFix->empty()) {
            auto aux = postFix->top();
            cout << aux->getData() << endl;
            postFix->pop();
        }
    }

    node *moveOperators( char character) {
        node *newNode = nullptr;
        switch (character) {
            case '^':
                newNode = new nodePowOpe(string(1, character));
                break;
            case '/': {
                newNode = new nodeDivOpe(string(1, character));
            }
                break;
            case '*': {
                newNode = new nodeMultOpe(string(1, character));
            }
                break;
            case '+': {
                newNode = new nodeSumOpe(string(1, character));
            }
                break;
            case '-': {
                newNode = new nodeSubOpe(string(1, character));
            }
                break;
        }

        return newNode;
    }

    void validatePrecedence(stack<node *> *aux, node *newNode) const {
        if (aux->empty())
            aux->push(newNode);
        else {
//          Validate operators precedence
            if (newNode->getPrecedence() > aux->top()->getPrecedence()) {
                aux->push(newNode);
            } else if (newNode->getPrecedence() < aux->top()->getPrecedence()) {

                while (!aux->empty()) {
                    auto node = aux->top();
                    if (node->getType() == '(')
                        break;
                    postFix->push(node);
                    aux->pop();
                }
                aux->push(newNode);
            } else { // Equal
                postFix->push(aux->top());
                aux->pop();
                aux->push(newNode);
            }
        }
    }

    ~ExpressTree() {
        variables->clear();
        variables = nullptr;

        if (!this->root)
            return;
        else
            this->root->killSelf();
    }
};


#endif //SOLVER_RVMOSQUERA_TREEEXPRESSION_H
