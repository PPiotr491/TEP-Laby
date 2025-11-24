//
// Created by Super on 17.11.2025.
//

#ifndef TEP_MINOPNODE_H
#define TEP_MINOPNODE_H
#include "../BinominalOperatorNode.h"

class MinOpNode : public BinominalOperatorNode {
public:
    MinOpNode(Node* left, Node* right);

    double evaluate() const;
    Node* clone() const;
};


#endif //TEP_MINOPNODE_H