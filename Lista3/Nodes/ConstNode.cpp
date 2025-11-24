#include "ConstNode.h"
#include <string>
#include <sstream>

ConstNode::ConstNode(double val) {
    setName("const");
    this->value = val;
}

double ConstNode::evaluate() const {
    return value;
}

std::string ConstNode::toString() const {
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

void ConstNode::collectVariables(std::vector<std::string>& variables) const {
    // Stała nie ma zmiennych. Nic nie rób
}

bool ConstNode::isLeaf() const {
    return true;
}

std::vector<Node*> ConstNode::getChildren() const {
    return std::vector<Node*>();
}

Node* ConstNode::clone() const {
    return new ConstNode(value);
}
