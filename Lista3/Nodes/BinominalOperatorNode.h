#ifndef TEP_BINOMINALOPERATORNODE_H
#define TEP_BINOMINALOPERATORNODE_H
#include "Node.h"


class BinominalOperatorNode : public Node {
public:
    BinominalOperatorNode();
    BinominalOperatorNode(std::string name, Node* left, Node* right);

    virtual ~BinominalOperatorNode();

    // Implementacja metody z klasy bazowej (można nadpisać w podklasach)
    virtual double evaluate(const std::map<std::string, double>& variables) const = 0;
    virtual std::string toString() const;
    virtual void collectVariables(std::vector<std::string>& variables) const;
    virtual bool isLeaf() const;
    virtual std::vector<Node*> getChildren() const;
    virtual Node* clone() const = 0;

    // Pomocnicze metody do modyfikowania dzieci (publiczne dla join)
    void setLeftChild(Node* left) {
        leftChild = left;
        if (leftChild) leftChild->setParent(this);
    }
    void setRightChild(Node* right) {
        rightChild = right;
        if (rightChild) rightChild->setParent(this);
    }

    Node* getLeftChild() const {
        return leftChild;
    }

    Node* getRightChild() const {
        return rightChild;
    }

private:
    Node* leftChild;
    Node* rightChild;
};


#endif //TEP_BINOMINALOPERATORNODE_H