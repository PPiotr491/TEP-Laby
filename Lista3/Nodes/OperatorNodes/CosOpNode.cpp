//
// Created by Super on 19.11.2025.
//

#include "CosOpNode.h"
#include <cmath>

CosOpNode::CosOpNode(Node* child)
    : MonominalOperatorNode("cos", child)
{
}

double CosOpNode::evaluate(const std::map<std::string, double>& variables) const {
    return std::cos(getChild()->evaluate(variables));
}

Node* CosOpNode::clone() const {
    Node* childClone = getChild() ? getChild()->clone() : NULL;
    return new CosOpNode(childClone);
}
