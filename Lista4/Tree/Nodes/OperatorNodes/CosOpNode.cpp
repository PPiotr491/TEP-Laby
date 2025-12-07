#include "CosOpNode.h"
#include <cmath>

CosOpNode::CosOpNode(Node* child)
    : MonominalOperatorNode("cos", child)
{
}

Result<double, Error> CosOpNode::evaluate() const {
    Result<double, Error> childResult = getChild()->evaluate();

    if (childResult.isSuccess()) {
        return Result<double, Error>::resultOk(std::cos(childResult.getValue()));
    } else {
        return collectErrors();
    }
}

Node* CosOpNode::clone() const {
    Node* childClone = getChild() ? getChild()->clone() : NULL;
    return new CosOpNode(childClone);
}
