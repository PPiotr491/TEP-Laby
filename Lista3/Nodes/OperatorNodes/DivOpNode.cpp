#include "DivOpNode.h"

#include <limits>
#include <stdexcept>

DivOpNode::DivOpNode(Node* left, Node* right)
    : BinominalOperatorNode("/", left, right)
{
}

double DivOpNode::evaluate() const {
    double divisor = getRightChild()->evaluate();
    if (divisor == 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return getLeftChild()->evaluate() / divisor;
}

Node* DivOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new DivOpNode(leftClone, rightClone);
}
