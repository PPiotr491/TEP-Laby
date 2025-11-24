#ifndef TEP_MONOMINALOPERATORNODE_H
#define TEP_MONOMINALOPERATORNODE_H
#include <string>

#include "Node.h"


class MonominalOperatorNode : public Node {
public:
    MonominalOperatorNode();
    MonominalOperatorNode(std::string name, Node* child);

    virtual ~MonominalOperatorNode();

    // Implementacja metody z klasy bazowej
    virtual double evaluate() const = 0;

    virtual std::string toString() const;

    virtual void collectVariables(std::vector<std::string>& variables) const;

    virtual bool isLeaf() const;

    virtual std::vector<Node*> getChildren() const;

    virtual Node* clone() const = 0;

    void setChild(Node* c) {
        child = c;
        if (child)
            child->setParent(this);
    }

    Node* getChild() const {
        return child;
    }


private:
    Node* child;
};


#endif //TEP_MONOMINALOPERATORNODE_H