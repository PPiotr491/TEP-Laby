#ifndef TEP_EQUATIONTREE_H
#define TEP_EQUATIONTREE_H
#include "Nodes/Node.h"
#include <string>
#include <vector>

class EquationTree {
public:
    EquationTree();
    EquationTree(const EquationTree& treeToCopy);
    ~EquationTree();

    // Metody główne
    std::string enter(const std::string& formula);
    std::string vars() const;
    std::string print() const;
    double comp(const std::vector<double>& values) const;
    std::string join(const std::string& formula);

    Node* getRoot() const {
        return root;
    }

    void setRoot(Node* root) {
        this->root = root;
    }

    // Zwraca listę zmiennych w drzewie
    std::vector<std::string> getVariables() const;

    // Operatory
    EquationTree& operator=(const EquationTree& other);
    EquationTree operator+(const EquationTree& other) const;

private:
    Node* root;

    // Metoda pomocnicza do znajdowania dowolnego liścia w drzewie
    Node* findAnyLeaf(Node* node) const;

    // Metoda pomocnicza do klonowania drzewa
    Node* cloneTree(Node* node) const;

    // Metoda pomocnicza do zastępowania zmiennych stałymi w drzewie (statyczna)
    static void replaceVariablesWithValues(Node* node, const std::vector<std::string>& variables, const std::vector<double>& values);
};


#endif //TEP_EQUATIONTREE_H