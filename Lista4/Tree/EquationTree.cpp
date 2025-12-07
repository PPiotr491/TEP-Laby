#include "EquationTree.h"

#include <cmath>
#include <sstream>

#include "Parser.h"
#include "../Tree/Nodes/BinominalOperatorNode.h"
#include "../Tree/Nodes/MonominalOperatorNode.h"
#include "../Tree/Nodes/VarNode.h"
#include "../Tree/Nodes/ConstNode.h"
#include "../Result.tpp"
#include "../Error.h"
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

Result<void, Error> EquationTree::enter(const std::string& formula) {
    bool isValid = true;
    std::string correctedExpression;

    // Usuń stare drzewo
    delete root;

    // Parsuj nowe wyrażenie
    root = Parser::parse(formula, isValid, correctedExpression);

    if (!isValid) {
        return Result<void, Error>::resultFail(new Error("Blad: Niepoprawne wyrazenie. Zostalo naprawione. "
                                                          "\nPoprawiona formula: " + correctedExpression));
    } else {
        return Result<void, Error>::resultOk();
    }
}

Result<std::string, Error> EquationTree::vars() const {
    if (root == NULL) {
        return Result<std::string, Error>::resultFail(new Error("Blad: Brak drzewa."));
    }

    std::vector<std::string> variables = getVariables();
    std::string result = "";

    for (size_t i = 0; i < variables.size(); i++) {
        if (i > 0) result += " ";
        result += variables[i];
    }

    return Result<std::string, Error>::resultOk(result);
}

Result<std::string, Error> EquationTree::print() const {
    if (root == NULL) {
        return Result<std::string, Error>::resultFail(new Error("Blad: Brak drzewa."));
    }

    return Result<std::string, Error>::resultOk(root->toString());
}

Result<double, Error> EquationTree::comp(const std::vector<double>& values) const {
    if (root == NULL) {
        return Result<double, Error>::resultFail(new Error("Blad: Brak drzewa do obliczenia."));
    }

    std::vector<std::string> variables = getVariables();

    if (values.size() != variables.size()) {
        std::ostringstream oss;
        oss << "Blad: Liczba podanych wartosci (" << values.size()
            << ") nie odpowiada liczbie zmiennych (" << variables.size() << ").";
        return Result<double, Error>::resultFail(new Error(oss.str()));
    }

    // Sklonuj drzewo, aby nie modyfikować oryginału
    Node* tempRoot = cloneTree(root);

    // Zamień wszystkie zmienne na stałe w sklonowanym drzewie
    replaceVariablesWithValues(tempRoot, variables, values);

    // Oblicz wartość (wszystkie VarNode zostały zamienione na ConstNode)
    Result<double, Error> result = tempRoot->evaluate();

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

Result<void, Error> EquationTree::join(const std::string& formula) {
    bool isValid = true;
    std::string correctedExpression;

    // Parsuj nowe wyrażenie
    Node* newTree = Parser::parse(formula, isValid, correctedExpression);

    if (this->root == NULL) {
        this->root = newTree;
        if (!isValid) {
            return Result<void, Error>::resultFail(
                new Error("Blad: Glowne drzewo jest puste. Tworze nowe drzewo. "
                          "\nBlad: Niepoprawne wyrazenie. Zostalo naprawione. \nPoprawiona formula: " + correctedExpression));
        } else {
            return Result<void, Error>::resultFail(
                new Error("Blad: Glowne drzewo jest puste. Zwracam nowe drzewo."));
        }
    }

    // Stwórz tymczasowe drzewo z nowym wyrażeniem
    EquationTree newEquationTree;
    newEquationTree.root = newTree;

    *this = *this + newEquationTree;

    // Zapobiegnij podwójnemu usunięciu
    newEquationTree.root = NULL;

    if (!isValid) {
        return Result<void, Error>::resultFail(
            new Error("Blad: Niepoprawne wyrazenie. Zostalo naprawione. \nPoprawiona formula: " + correctedExpression +
                      "\nDrzewo zostalo polaczone."));
    }

    return Result<void, Error>::resultOk();
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

Result<std::string, Error> EquationTree::mr() {
    Node* node = mostRight(root);
    if (node != NULL) {
        return Result<std::string, Error>::resultOk(node->toString());
    }
    return Result<std::string, Error>::resultFail(new Error("Blad. Nie znaleziono liscia"));
}

Node* EquationTree::mostRight(Node* node) {
    if (node == NULL) {
        return NULL;
    }

    // Jeśli węzeł jest liściem, zwróć go
    if (node->isLeaf()) {
        return node;
    }

    BinominalOperatorNode* binNode = dynamic_cast<BinominalOperatorNode*>(node);
    if (binNode != NULL) {
        std::vector<Node*> children = binNode->getChildren();
        if (children.size() >= 2 && children[1] != NULL) {
            return mostRight(children[1]);
        }
    } else {
        MonominalOperatorNode* monoNode = dynamic_cast<MonominalOperatorNode*>(node);
        if (monoNode != NULL) {
            return mostRight(monoNode->getChild());
        }
    }

    return NULL;
}
