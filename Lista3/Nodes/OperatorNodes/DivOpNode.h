//
// Created by Super on 17.11.2025.
//

#ifndef TEP_DIVOPNODE_H
#define TEP_DIVOPNODE_H
#include "../BinominalOperatorNode.h"

class DivOpNode : public BinominalOperatorNode {
public:
    DivOpNode(Node* left, Node* right);

    double evaluate() const;
    Node* clone() const;
};


#endif //TEP_DIVOPNODE_H