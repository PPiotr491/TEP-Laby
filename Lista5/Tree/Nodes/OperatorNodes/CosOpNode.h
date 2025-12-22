#ifndef TEP_COSOPNODE_H
#define TEP_COSOPNODE_H
#include "../MonominalOperatorNode.h"


class CosOpNode : public MonominalOperatorNode {
public:
    CosOpNode(Node* child);

    Result<double, Error> evaluate() const;
    Node* clone() const;
};


#endif //TEP_COSOPNODE_H