#include "VarNode.h"

VarNode::VarNode(const std::string& varName) {
    setName(varName);
    this->variableName = varName;
}

double VarNode::evaluate(const std::map<std::string, double>& variables) const {
    std::map<std::string, double>::const_iterator it = variables.find(variableName);
    if (it != variables.end()) {
        return it->second;
    }
    throw std::runtime_error("Variable '" + variableName + "' not found in variables map");
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

bool VarNode::isLeaf() const {
    return true;
}

std::vector<Node*> VarNode::getChildren() const {
    return std::vector<Node*>();
}

Node* VarNode::clone() const {
    return new VarNode(variableName);
}
