#include "VarNode.h"

VarNode::VarNode(const std::string& varName) {
    setName(varName);
    this->variableName = varName;
}

// VarNode jest zamieniany na ConstNode, więc evaluate nigdy nie będzie wywołany
Result<double, Error> VarNode::evaluate() const {
    return 0.0;
}

std::string VarNode::toString() const {
    return variableName;
}

void VarNode::collectVariables(std::vector<std::string>& variables) const {
    // Sprawdź czy zmienna już istnieje w wektorze
    bool found = false;
    for (size_t i = 0; i < variables.size(); i++) {
        if (variables[i] == variableName) {
            found = true;
            break;
        }
    }

    // Jeśli nie znaleziono, dodaj
    if (!found) {
        variables.push_back(variableName);
    }
}

// nigdy nie ma bledow
Result<double, Error> VarNode::collectErrors() const {
    return Result<double, Error>::resultOk(0.0);
}

bool VarNode::isLeaf() const {
    return true;
}

std::vector<Node*> VarNode::getChildren() const {
    return std::vector<Node*>();
}

Node* VarNode::clone() const {
    return new VarNode(variableName);
}
