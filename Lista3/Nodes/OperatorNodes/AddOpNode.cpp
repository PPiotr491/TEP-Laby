#include "AddOpNode.h"

AddOpNode::AddOpNode(Node* left, Node* right)
    : BinominalOperatorNode("+", left, right)
{
}

double AddOpNode::evaluate() const {
    return getLeftChild()->evaluate() + getRightChild()->evaluate();
}

Node* AddOpNode::clone() const {
    Node* leftClone = getLeftChild() ? getLeftChild()->clone() : NULL;
    Node* rightClone = getRightChild() ? getRightChild()->clone() : NULL;
    return new AddOpNode(leftClone, rightClone);
}
