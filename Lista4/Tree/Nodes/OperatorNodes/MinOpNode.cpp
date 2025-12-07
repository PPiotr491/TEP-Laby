#include "MinOpNode.h"

MinOpNode::MinOpNode(Node* left, Node* right)
    : BinominalOperatorNode("-", left, right)
{
}

Result<double, Error> MinOpNode::evaluate() const {
    Result<double, Error> leftResult = getLeftChild()->evaluate();
    Result<double, Error> rightResult = getRightChild()->evaluate();

    if (leftResult.isSuccess() && rightResult.isSuccess()) {
        return Result<double, Error>::resultOk(leftResult.getValue() - rightResult.getValue());
    } else {
        return collectErrors();
    }
}

Node* MinOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new MinOpNode(leftClone, rightClone);
}
