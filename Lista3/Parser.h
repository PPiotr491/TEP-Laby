#ifndef TEP_PARSER_H
#define TEP_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include "Nodes/Node.h"

class Parser {
public:
    // Parsuje wyrażenie w notacji polskiej i zwraca korzeń drzewa
    static Node* parse(const std::string& expression, bool& isValid, std::string& correctedExpression);

private:
    // Sprawdza czy token jest operatorem
    static bool isOperator(const std::string& token);

    // Zwraca liczbę argumentów dla operatora
    static int getOperatorArity(const std::string& token);

    // Sprawdza czy string jest liczbą
    static bool isNumber(const std::string& str);

    // Tworzy węzeł operatora z podanymi dziećmi
    static Node* createOperatorNode(const std::string& str, Node* left, Node* right);

    // Tworzy węzeł operatora jednoargumentowego
    static Node* createUnaryOperatorNode(const std::string& str, Node* child);

    // Tworzy węzeł stałej lub zmiennej
    static Node* createLeafNode(const std::string& str);

    // Tworzy domyślny węzeł (stała 1)
    static Node* createDefaultNode();

    // Rekurencyjne parsowanie wyrażenia w notacji polskiej
    static Node* parseNode(std::istringstream& iss, bool& isValid, std::ostringstream& fixedStream, bool& firstToken);
};


#endif //TEP_PARSER_H