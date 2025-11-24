#ifndef TEP_ADDOPNODE_H
#define TEP_ADDOPNODE_H
#include "../BinominalOperatorNode.h"


class AddOpNode : public BinominalOperatorNode {
public:
    AddOpNode(Node* left, Node* right);

    double evaluate() const;
    Node* clone() const;
};


#endif //TEP_ADDOPNODE_H