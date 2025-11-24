#include "SinOpNode.h"
#include <cmath>

SinOpNode::SinOpNode(Node* child)
    : MonominalOperatorNode("sin", child)
{
}

double SinOpNode::evaluate() const {
    return std::sin(getChild()->evaluate());
}

Node* SinOpNode::clone() const {
    Node* childClone = getChild() ? getChild()->clone() : NULL;
    return new SinOpNode(childClone);
}
