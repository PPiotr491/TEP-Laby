#ifndef TEP_EQUATIONTREE_H
#define TEP_EQUATIONTREE_H
#include "../Tree/Nodes/Node.h"
#include "../Result.tpp"
#include "../Error.h"
#include <string>
#include <vector>

class EquationTree {
public:
    EquationTree();
    EquationTree(const EquationTree& treeToCopy);
    ~EquationTree();

    Result<void, Error> enter(const std::string& formula);

    Result<std::string, Error> vars() const;

    Result<std::string, Error> print() const;

    Result<double, Error> comp(const std::vector<double>& values) const;

    Result<void, Error> join(const std::string& formula);

    Node* getRoot() const {
        return root;
    }

    void setRoot(Node* root) {
        this->root = root;
    }

    std::vector<std::string> getVariables() const;
    Result<std::string, Error> mr();

    EquationTree& operator=(const EquationTree& other);
    EquationTree operator+(const EquationTree& other) const;

private:
    Node* root;

    Node* mostRight(Node* node);

    Node* findAnyLeaf(Node* node) const;

    Node* cloneTree(Node* node) const;

    static void replaceVariablesWithValues(Node* node, const std::vector<std::string>& variables, const std::vector<double>& values);
};


#endif //TEP_EQUATIONTREE_H