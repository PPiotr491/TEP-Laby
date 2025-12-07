#include "AddOpNode.h"

AddOpNode::AddOpNode(Node* left, Node* right)
    : BinominalOperatorNode("+", left, right)
{
}

Result<double, Error> AddOpNode::evaluate() const {
    Result<double, Error> leftResult = getLeftChild()->evaluate();
    Result<double, Error> rightResult = getRightChild()->evaluate();

    if (leftResult.isSuccess() && rightResult.isSuccess()) {
        return Result<double, Error>::resultOk(leftResult.getValue() + rightResult.getValue());
    } else {
        return collectErrors();
    }
}

Node* AddOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new AddOpNode(leftClone, rightClone);
}
