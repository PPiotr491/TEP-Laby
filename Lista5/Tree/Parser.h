#ifndef TEP_PARSER_H
#define TEP_PARSER_H

#include <string>
#include <vector>
#include <sstream>
#include "../Tree/Nodes/Node.h"

class Parser {
public:
    // Parsuje wyrażenie w notacji polskiej i zwraca korzeń drzewa
    // Jeśli wyrażenie jest błędne, zwraca NULL i ustawia isValid na false
    static Node* parse(const std::string& expression, bool& isValid);

private:
    static bool isOperator(const std::string& token);

    // Zwraca liczbę argumentów dla operatora
    static int getOperatorArity(const std::string& token);

    static bool isNumber(const std::string& str);

    static Node* createOperatorNode(const std::string& str, Node* left, Node* right);

    static Node* createUnaryOperatorNode(const std::string& str, Node* child);

    static Node* createLeafNode(const std::string& str);

    static Node* parseNode(std::istringstream& iss, bool& isValid);
};


#endif //TEP_PARSER_H