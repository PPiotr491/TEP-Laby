#include "Node.h"

Node::Node() {
    setName("");
    setParent(NULL);
}

Node::Node(std::string name) {
    setName(name);
    setParent(NULL);
}

Node::Node(const Node& nodeToCopy) {
    setName(nodeToCopy.getName());
    setParent(nodeToCopy.getParent());
}

Node::~Node() {
}