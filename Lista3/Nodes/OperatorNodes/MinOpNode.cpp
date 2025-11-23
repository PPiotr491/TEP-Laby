#include "MinOpNode.h"

MinOpNode::MinOpNode(Node* left, Node* right)
    : BinominalOperatorNode("-", left, right)
{
}

double MinOpNode::evaluate(const std::map<std::string, double>& variables) const {
    return getLeftChild()->evaluate(variables) - getRightChild()->evaluate(variables);
}

Node* MinOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new MinOpNode(leftClone, rightClone);
}
