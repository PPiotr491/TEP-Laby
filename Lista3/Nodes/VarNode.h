#ifndef TEP_VARNODE_H
#define TEP_VARNODE_H
#include "Node.h"
#include <stdexcept>

class VarNode : public Node {
public:
    VarNode(const std::string& variableName);

    double evaluate() const;

    std::string toString() const;

    void collectVariables(std::vector<std::string>& variables) const;

    bool isLeaf() const;

    std::vector<Node*> getChildren() const;

    Node* clone() const;

    std::string getVariableName() const {
        return variableName;
    }

private:
    std::string variableName;
};

#endif //TEP_VARNODE_H