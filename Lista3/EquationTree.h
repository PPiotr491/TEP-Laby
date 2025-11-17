#ifndef TEP_EQUATIONTREE_H
#define TEP_EQUATIONTREE_H
#include "Nodes/Node.h"
#include <string>


class EquationTree {

public:
    EquationTree();
    EquationTree(std::string equation);
    EquationTree(const EquationTree& nodeToCopy);

    EquationTree& operator=(const int value);
    EquationTree& operator+(const EquationTree &other);

    Node getRoot() const {
        return root;
    }

    void setRoot(const Node &root) {
        this->root = root;
    }

private:
    Node root;

    std::string enterNewEquation(std::string equation);
    std::string vars();
    std::string print();
    double comp(double* varTable);
    void join(std::string);
};


#endif //TEP_EQUATIONTREE_H