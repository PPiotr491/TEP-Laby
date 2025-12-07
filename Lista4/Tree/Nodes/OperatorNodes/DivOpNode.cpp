#include "DivOpNode.h"

#include <limits>
#include <stdexcept>

DivOpNode::DivOpNode(Node* left, Node* right)
    : BinominalOperatorNode("/", left, right)
{
}

Result<double, Error> DivOpNode::evaluate() const {
    Result<double, Error> leftResult = getLeftChild()->evaluate();
    Result<double, Error> rightResult = getRightChild()->evaluate();

    if (leftResult.isSuccess() && rightResult.isSuccess()) {
        double divisor = rightResult.getValue();
        if (divisor == 0.0) {
            return Result<double, Error>::resultFail(new Error("Blad: Dzielenie przez zero"));
        }
        return Result<double, Error>::resultOk(leftResult.getValue() / divisor);
    } else {
        return collectErrors();
    }
}

Node* DivOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new DivOpNode(leftClone, rightClone);
}
