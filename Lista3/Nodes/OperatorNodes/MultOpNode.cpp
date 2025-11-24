#include "MultOpNode.h"

MultOpNode::MultOpNode(Node* left, Node* right)
    : BinominalOperatorNode("*", left, right)
{
}

double MultOpNode::evaluate() const {
    return getLeftChild()->evaluate() * getRightChild()->evaluate();
}

Node* MultOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new MultOpNode(leftClone, rightClone);
}
