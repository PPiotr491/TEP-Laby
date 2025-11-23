#include "AddOpNode.h"

AddOpNode::AddOpNode(Node* left, Node* right)
    : BinominalOperatorNode("+", left, right)
{
}

double AddOpNode::evaluate(const std::map<std::string, double>& variables) const {
    return getLeftChild()->evaluate(variables) + getRightChild()->evaluate(variables);
}

Node* AddOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new AddOpNode(leftClone, rightClone);
}
