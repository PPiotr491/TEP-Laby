#ifndef TEP_NODE_H
#define TEP_NODE_H
#include <string>
#include <vector>
#include <map>


class Node {
public:
    Node();
    Node(std::string name);
    Node(const Node& nodeToCopy);

    virtual ~Node();

    // Metoda wirtualna do obliczania wartości węzła
    virtual double evaluate(const std::map<std::string, double>& variables) const = 0;

    // Metoda do wyświetlania drzewa (opcjonalna, pomocna przy debugowaniu)
    virtual std::string toString() const = 0;

    // Metoda do zbierania zmiennych
    virtual void collectVariables(std::vector<std::string>& variables) const = 0;

    // Metoda sprawdzająca czy węzeł jest liściem
    virtual bool isLeaf() const = 0;

    // Metoda do pobierania dzieci węzła (dla operatorów)
    virtual std::vector<Node*> getChildren() const = 0;

    // Metoda do klonowania węzła (tworzy głęboką kopię)
    virtual Node* clone() const = 0;

    std::string getName() const {
        return name;
    }

    void setName(const std::string name) {
        this->name = name;
    }

    Node* getParent() const {
        return parent;
    }

    void setParent(Node *parent) {
        this->parent = parent;
    }

private:
    std::string name;
    Node* parent;
};


#endif //TEP_NODE_H