#include "CosOpNode.h"
#include <cmath>

CosOpNode::CosOpNode(Node* child)
    : MonominalOperatorNode("cos", child)
{
}

double CosOpNode::evaluate() const {
    return std::cos(getChild()->evaluate());
}

Node* CosOpNode::clone() const {
    Node* childClone = getChild() ? getChild()->clone() : NULL;
    return new CosOpNode(childClone);
}
