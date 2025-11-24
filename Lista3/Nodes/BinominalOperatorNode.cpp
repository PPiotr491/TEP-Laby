#include "BinominalOperatorNode.h"

BinominalOperatorNode::BinominalOperatorNode() {
    setName("binop");
    leftChild = NULL;
    rightChild = NULL;
}

BinominalOperatorNode::BinominalOperatorNode(std::string name, Node* left, Node* right)
    : Node(name) {
    leftChild = left;
    rightChild = right;
    if (leftChild) leftChild->setParent(this);
    if (rightChild) rightChild->setParent(this);
}

BinominalOperatorNode::~BinominalOperatorNode() {
    delete leftChild;
    delete rightChild;
}

std::string BinominalOperatorNode::toString() const {
    std::string result = getName() + " ";
    if (getLeftChild()) result += getLeftChild()->toString() + " ";
    if (getRightChild()) result += getRightChild()->toString();
    return result;
}

void BinominalOperatorNode::collectVariables(std::vector<std::string>& variables) const {
    if (leftChild)
        leftChild->collectVariables(variables);
    if (rightChild)
        rightChild->collectVariables(variables);
}

bool BinominalOperatorNode::isLeaf() const {
    return false;
}

std::vector<Node*> BinominalOperatorNode::getChildren() const {
    std::vector<Node*> children;
    if (leftChild) children.push_back(leftChild);
    if (rightChild) children.push_back(rightChild);
    return children;
}
