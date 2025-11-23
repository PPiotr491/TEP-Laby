#ifndef TEP_SINOPNODE_H
#define TEP_SINOPNODE_H
#include "../MonominalOperatorNode.h"


class SinOpNode : public MonominalOperatorNode {
public:
    SinOpNode(Node* child);

    double evaluate(const std::map<std::string, double>& variables) const;
    Node* clone() const;
};


#endif //TEP_SINOPNODE_H