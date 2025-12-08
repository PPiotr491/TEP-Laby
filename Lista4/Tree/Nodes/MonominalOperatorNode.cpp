#include "MonominalOperatorNode.h"

MonominalOperatorNode::MonominalOperatorNode() {
    setName("mono");
    child = NULL;
}

MonominalOperatorNode::MonominalOperatorNode(std::string name, Node* c) {
    setName(name);
    child = c;
    if (child)
        child->setParent(this);
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
    if (child)
        child->collectVariables(variables);
}

Result<double, Error> MonominalOperatorNode::collectErrors() const {
    std::vector<Error*> thisErrors;

    if (child) {
        Result<double, Error> childResult = child->evaluate();
        std::vector<Error*> childErrors = childResult.getErrors();

        // Klonuje błędy, aby uniknąć podwójnego usuwania
        for (size_t i = 0; i < childErrors.size(); i++) {
            thisErrors.push_back(childErrors[i]->clone());
        }
    }

    return Result<double, Error>::resultFail(thisErrors);
}

bool MonominalOperatorNode::isLeaf() const {
    return false;
}

std::vector<Node*> MonominalOperatorNode::getChildren() const {
    std::vector<Node*> children;
    if (child)
        children.push_back(child);
    return children;
}
