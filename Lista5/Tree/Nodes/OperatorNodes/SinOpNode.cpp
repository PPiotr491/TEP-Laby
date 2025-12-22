#include "SinOpNode.h"
#include <cmath>

SinOpNode::SinOpNode(Node* child)
    : MonominalOperatorNode("sin", child)
{
}

Result<double, Error> SinOpNode::evaluate() const {
    Result<double, Error> childResult = getChild()->evaluate();

    if (childResult.isSuccess()) {
        return Result<double, Error>::resultOk(std::sin(childResult.getValue()));
    } else {
        return collectErrors();
    }
}

Node* SinOpNode::clone() const {
    Node* childClone = getChild() ? getChild()->clone() : NULL;
    return new SinOpNode(childClone);
}
