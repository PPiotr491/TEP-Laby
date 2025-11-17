#ifndef TEP_NODE_H
#define TEP_NODE_H
#include <string>


class Node {
public:
    Node();
    Node(std::string value);
    Node(std::string value, Node* leftChild, Node* rightChild, Node* parent);
    Node(const Node& nodeToCopy);

    virtual ~Node() = 0;

    std::string getValue() const {
        return value;
    }

    void setValue(const std::string &value) {
        this->value = value;
    }

    Node* getLeftChild() const {
        return leftChild;
    }

    void setLeftChild(Node *leftChild) {
        this->leftChild = leftChild;
    }

    Node* getRightChild() const {
        return rightChild;
    }

    void setRightChild(Node *rightChild) {
        this->rightChild = rightChild;
    }

    Node* getParent() const {
        return parent;
    }

    void setParent(Node *parent) {
        this->parent = parent;
    }

private:
    std::string value;
    Node* leftChild;
    Node* rightChild; // lub vector jeśli jest więcej niż dwa argumenty
    Node* parent;
};


#endif //TEP_NODE_H