//
// Created by Super on 19.11.2025.
//

#include "SinOpNode.h"
#include <cmath>

SinOpNode::SinOpNode(Node* child)
    : MonominalOperatorNode("sin", child)
{
}

double SinOpNode::evaluate(const std::map<std::string, double>& variables) const {
    return std::sin(getChild()->evaluate(variables));
}

Node* SinOpNode::clone() const {
    Node* childClone = getChild() ? getChild()->clone() : NULL;
    return new SinOpNode(childClone);
}
