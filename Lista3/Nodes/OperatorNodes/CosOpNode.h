//
// Created by Super on 19.11.2025.
//

#ifndef TEP_COSOPNODE_H
#define TEP_COSOPNODE_H
#include "../MonominalOperatorNode.h"


class CosOpNode : public MonominalOperatorNode {
public:
    CosOpNode(Node* child);

    double evaluate(const std::map<std::string, double>& variables) const;
    Node* clone() const;
};


#endif //TEP_COSOPNODE_H