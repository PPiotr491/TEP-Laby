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

Result<double, Error> BinominalOperatorNode::collectErrors() const {
    std::vector<Error*> thisErrors;
    std::vector<Error*> leftErrors;
    std::vector<Error*> rightErrors;

    if (leftChild)
        leftErrors = leftChild->evaluate().getErrors();
    if (rightChild)
        rightErrors = rightChild->evaluate().getErrors();

    for (size_t i = 0; i < leftErrors.size(); i++) {
        thisErrors.push_back(leftErrors[i]);
    }

    for (size_t i = 0; i < rightErrors.size(); i++) {
        thisErrors.push_back(rightErrors[i]);
    }

    return Result<double, Error>::resultFail(thisErrors);
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
