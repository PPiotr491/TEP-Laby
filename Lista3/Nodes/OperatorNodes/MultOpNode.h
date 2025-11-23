#ifndef TEP_MULTOPNODE_H
#define TEP_MULTOPNODE_H
#include "../BinominalOperatorNode.h"

class MultOpNode : public BinominalOperatorNode {
public:
    MultOpNode(Node* left, Node* right);

    double evaluate(const std::map<std::string, double>& variables) const;
    Node* clone() const;
};


#endif //TEP_MULTOPNODE_H