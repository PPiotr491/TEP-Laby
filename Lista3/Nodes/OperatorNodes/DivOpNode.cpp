//
// Created by Super on 17.11.2025.
//

#include "DivOpNode.h"
#include <stdexcept>

DivOpNode::DivOpNode(Node* left, Node* right)
    : BinominalOperatorNode("/", left, right)
{
}

double DivOpNode::evaluate(const std::map<std::string, double>& variables) const {
    double divisor = getRightChild()->evaluate(variables);
    if (divisor == 0.0) {
        throw std::runtime_error("Division by zero");
    }
    return getLeftChild()->evaluate(variables) / divisor;
}

Node* DivOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new DivOpNode(leftClone, rightClone);
}
