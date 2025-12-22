#include "ConstNode.h"
#include <string>
#include <sstream>

ConstNode::ConstNode(double val) {
    setName("const");
    this->value = val;
}

Result<double, Error> ConstNode::evaluate() const {
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

// nigdy nie ma błędów
Result<double, Error> ConstNode::collectErrors() const {
    return Result<double, Error>::resultOk(0.0);
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
