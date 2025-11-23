#include "MultOpNode.h"

MultOpNode::MultOpNode(Node* left, Node* right)
    : BinominalOperatorNode("*", left, right)
{
}

double MultOpNode::evaluate(const std::map<std::string, double>& variables) const {
    return getLeftChild()->evaluate(variables) * getRightChild()->evaluate(variables);
}

Node* MultOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new MultOpNode(leftClone, rightClone);
}
