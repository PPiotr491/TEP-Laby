#include "MinOpNode.h"

MinOpNode::MinOpNode(Node* left, Node* right)
    : BinominalOperatorNode("-", left, right)
{
}

double MinOpNode::evaluate() const {
    return getLeftChild()->evaluate() - getRightChild()->evaluate();
}

Node* MinOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new MinOpNode(leftClone, rightClone);
}
