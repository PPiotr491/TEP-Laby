#ifndef TEP_CONSTNODE_H
#define TEP_CONSTNODE_H
#include "Node.h"


class ConstNode : public Node {
public:
    ConstNode(double value);

    double evaluate() const;
    std::string toString() const;
    void collectVariables(std::vector<std::string>& variables) const;
    bool isLeaf() const;
    std::vector<Node*> getChildren() const;
    Node* clone() const;

    double getValue() const {
        return value;
    }

private:
    double value;
};


#endif //TEP_CONSTNODE_H