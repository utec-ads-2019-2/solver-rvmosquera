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
    int cantSigns;
public:
    ExpressTree() {
        root = nullptr;
        postFix = new stack<node *>();
        cantSigns = 1;
    }

    float evaluate() {
        return this->root->execute();
    }

    void generateFromInfixExp(string infixExp) {
        auto stack2 = new stack<node *>();
        string numberStr;
        string alphaStr;

        variables = new vector<nodeVar*>();

//        for (int i = 0; i < len; i++) {
        for( auto it = infixExp.begin(); it != infixExp.end(); ++it) {
            auto character = *it; //infixExp[i];

            if (isdigit(character)) {
                numberStr = numberStr + character;
            } else if (isalpha(character)) {
                alphaStr = alphaStr + character;
            } else {
                if (numberStr != "") {
                    postFix->push(new nodeCons(numberStr));
                    numberStr = "";
                }
                getVariable(&alphaStr);

                switch (character) {
                    case ' ':
                        continue;
                    case '(': {
                        stack2->push(new nodeParenth(string(1, character) ));
                    }
                        break;

                    case ')': {
                        auto node = stack2->top();
                        while (node->getType() != '(') {
                            postFix->push(node);
                            stack2->pop();
                            node = stack2->top();
                        }

                        if (node->getType() == '(')
                            stack2->pop();
                    }
                        break;
                    default: { // is operator
                        moveOperators(stack2, character);
                    }
                }
            }

            //if (i == len - 1) {
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
                auto nodevariable = new nodeVar(*alphaStr);
                postFix->push(nodevariable);
                variables->push_back(nodevariable);
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
        for(auto elem: *variables) {
            cout << "Value for variable " <<elem->getData()<<" = ";
            cin >> value;
            elem->setValue( value );
        }
    }

    void printPostFix() {
        while (!postFix->empty()) {
            auto aux = postFix->top();
            cout << aux->getData() << endl;
            postFix->pop();
        }
    }

    void moveOperators(stack<node *> *aux, char character) {
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
                //cantSigns = cantSigns * 1;
            }
                break;
            case '-': {
                newNode = new nodeSubOpe(string(1, character));
                //cantSigns = cantSigns * -1;
            }
                break;
        }

        if (aux->empty())
            aux->push(newNode);
        else {
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
