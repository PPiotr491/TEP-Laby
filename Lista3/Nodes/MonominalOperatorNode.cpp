#include "MonominalOperatorNode.h"

MonominalOperatorNode::MonominalOperatorNode() {
    setName("mono");
    child = NULL;
}

MonominalOperatorNode::MonominalOperatorNode(std::string name, Node* c) {
    setName(name);
    child = c;
    if (child) child->setParent(this);
}

MonominalOperatorNode::~MonominalOperatorNode() {
    delete child;
}

std::string MonominalOperatorNode::toString() const {
    std::string result = getName() + " ";
    if (getChild()) result += getChild()->toString();
    return result;
}

void MonominalOperatorNode::collectVariables(std::vector<std::string>& variables) const {
    if (child) child->collectVariables(variables);
}

bool MonominalOperatorNode::isLeaf() const {
    return false;
}

std::vector<Node*> MonominalOperatorNode::getChildren() const {
    std::vector<Node*> children;
    if (child) children.push_back(child);
    return children;
}
