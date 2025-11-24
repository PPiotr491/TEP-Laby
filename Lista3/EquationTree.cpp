#include "EquationTree.h"

#include <cmath>

#include "Parser.h"
#include "Nodes/BinominalOperatorNode.h"
#include "Nodes/MonominalOperatorNode.h"
#include "Nodes/VarNode.h"
#include "Nodes/ConstNode.h"
#include <iostream>

EquationTree::EquationTree() {
    root = NULL;
}

EquationTree::EquationTree(const EquationTree& treeToCopy) {
    root = cloneTree(treeToCopy.root);
}

EquationTree::~EquationTree() {
    delete root;
}

std::string EquationTree::enter(const std::string& formula) {
    bool isValid = true;
    std::string correctedExpression;

    // Usuń stare drzewo
    delete root;

    // Parsuj nowe wyrażenie
    root = Parser::parse(formula, isValid, correctedExpression);

    if (!isValid) {
        return "Blad: Niepoprawne wyrazenie. Zostalo naprawione. \n Poprawiona formula: " + correctedExpression;
    } else {
        return "Formula zostala wczytana poprawnie.";
    }
}

std::string EquationTree::vars() const {
    if (root == NULL) {
        return "";
    }

    std::vector<std::string> variables = getVariables();
    std::string result = "";

    for (size_t i = 0; i < variables.size(); i++) {
        if (i > 0) result += " ";
        result += variables[i];
    }

    return result;
}

std::string EquationTree::print() const {
    if (root == NULL) {
        return "";
    }

    return root->toString();
}

double EquationTree::comp(const std::vector<double>& values) const {
    if (root == NULL) {
        std::cout << "Blad: Brak drzewa do obliczenia." << std::endl;
        return 0.0;
    }

    std::vector<std::string> variables = getVariables();

    if (values.size() != variables.size()) {
        std::cout << "Blad: Liczba podanych wartosci (" << values.size()
                  << ") nie odpowiada liczbie zmiennych (" << variables.size() << ")." << std::endl;
        return 0.0;
    }

    // Sklonuj drzewo, aby nie modyfikować oryginału
    Node* tempRoot = cloneTree(root);

    // Zamień wszystkie zmienne na stałe w sklonowanym drzewie
    replaceVariablesWithValues(tempRoot, variables, values);

    // Oblicz wartość (wszystkie VarNode zostały zamienione na ConstNode)
    double result = tempRoot->evaluate();

    // Usuń tymczasowe drzewo
    delete tempRoot;

    return result;
}

EquationTree& EquationTree::operator=(const EquationTree& other) {
    if (this != &other) {
        delete root;
        root = cloneTree(other.root);
    }
    return *this;
}

EquationTree EquationTree::operator+(const EquationTree& other) const {
    EquationTree result;

    // Klonuj obecne drzewo
    result.root = cloneTree(root);

    // Znajdź dowolny liść w sklonowanym drzewie
    Node* leafToReplace = findAnyLeaf(result.root);

    if (leafToReplace != NULL) {
        Node* parent = leafToReplace->getParent();
        Node* newSubTree = cloneTree(other.root);

        if (parent != NULL) {
            // Zastąp liść nowym poddrzewem
            BinominalOperatorNode* binParent = dynamic_cast<BinominalOperatorNode*>(parent);
            if (binParent != NULL) {
                // Sprawdź czy liść jest lewym czy prawym dzieckiem
                if (!binParent->getChildren().empty() && binParent->getChildren()[0] == leafToReplace) {
                    binParent->setLeftChild(newSubTree);
                } else if (binParent->getChildren().size() >= 2 && binParent->getChildren()[1] == leafToReplace) {
                    binParent->setRightChild(newSubTree);
                }

                leafToReplace->setParent(NULL);
                delete leafToReplace;
            } else {
                MonominalOperatorNode* monoParent = dynamic_cast<MonominalOperatorNode*>(parent);
                if (monoParent != NULL) {
                    monoParent->setChild(newSubTree);
                    leafToReplace->setParent(NULL);
                    delete leafToReplace;
                }
            }
        } else {
            // Liść jest korzeniem
            delete result.root;
            result.root = newSubTree;
        }
    }

    return result;
}

std::string EquationTree::join(const std::string& formula) {
    bool isValid = true;
    std::string correctedExpression;

    // Parsuj nowe wyrażenie
    Node* newTree = Parser::parse(formula, isValid, correctedExpression);

    if (this->root == NULL) {
        this->root = newTree;
        if (!isValid) {
            return "Blad: Glowne drzewo jest puste. Tworze nowe drzewo. "
                   "\nBlad: Niepoprawne wyrazenie. Zostalo naprawione. \nPoprawiona formula: " + correctedExpression;
        } else {
            return "Blad: Glowne drzewo jest puste. Zwracam nowe drzewo.";
        }
    }

    // Stwórz tymczasowe drzewo z nowym wyrażeniem
    EquationTree newEquationTree;
    newEquationTree.root = newTree;

    *this = *this + newEquationTree;

    // Zapobiegnij podwójnemu usunięciu
    newEquationTree.root = NULL;

    if (!isValid) {
        return "Blad: Niepoprawne wyrazenie. Zostalo naprawione. \nPoprawiona formula: " + correctedExpression +
            "\nDrzewo zostalo polaczone.";
    }

    return "Drzewo zostalo polaczone.";
}

Node* EquationTree::findAnyLeaf(Node* node) const {
    if (node == NULL) {
        return NULL;
    }

    // Jeśli węzeł jest liściem, zwróć go
    if (node->isLeaf()) {
        return node;
    }

    // W przeciwnym razie, przeszukaj dzieci
    std::vector<Node*> children = node->getChildren();
    for (size_t i = 0; i < children.size(); i++) {
        Node* leaf = findAnyLeaf(children[i]);
        if (leaf != NULL) {
            return leaf;
        }
    }

    return NULL;
}

Node* EquationTree::cloneTree(Node* node) const {
    if (node == NULL) {
        return NULL;
    }
    return node->clone();
}

void EquationTree::replaceVariablesWithValues(Node* node, const std::vector<std::string>& variables, const std::vector<double>& values) {
    if (node == NULL) {
        return;
    }

    // Sprawdź czy węzeł jest VarNode
    VarNode* varNode = dynamic_cast<VarNode*>(node);
    if (varNode != NULL) {
        // Znajdź indeks zmiennej w wektorze zmiennych
        std::string varName = varNode->getVariableName();
        for (size_t i = 0; i < variables.size(); i++) {
            if (variables[i] == varName) {
                // Znaleziono zmienną - trzeba zamienić VarNode na ConstNode
                Node* parent = node->getParent();
                ConstNode* constNode = new ConstNode(values[i]);

                if (parent != NULL) {
                    BinominalOperatorNode* binParent = dynamic_cast<BinominalOperatorNode*>(parent);
                    if (binParent != NULL) {
                        std::vector<Node*> children = binParent->getChildren();
                        if (children.size() >= 1 && children[0] == node) {
                            binParent->setLeftChild(constNode);
                        } else if (children.size() >= 2 && children[1] == node) {
                            binParent->setRightChild(constNode);
                        }
                    } else {
                        MonominalOperatorNode* monoParent = dynamic_cast<MonominalOperatorNode*>(parent);
                        if (monoParent != NULL) {
                            monoParent->setChild(constNode);
                        }
                    }
                    // Usuń stary węzeł zmiennej
                    node->setParent(NULL);
                    delete node;
                }
                return;
            }
        }
    }

    // Rekurencyjnie przejdź przez dzieci
    std::vector<Node*> children = node->getChildren();
    for (size_t i = 0; i < children.size(); i++) {
        replaceVariablesWithValues(children[i], variables, values);
    }
}

std::vector<std::string> EquationTree::getVariables() const {
    std::vector<std::string> variables;
    if (root != NULL) {
        root->collectVariables(variables);
    }
    return variables;
}
