#include "Parser.h"
#include "Nodes/ConstNode.h"
#include "Nodes/VarNode.h"
#include "Nodes/OperatorNodes/AddOpNode.h"
#include "Nodes/OperatorNodes/MinOpNode.h"
#include "Nodes/OperatorNodes/MultOpNode.h"
#include "Nodes/OperatorNodes/DivOpNode.h"
#include "Nodes/OperatorNodes/SinOpNode.h"
#include "Nodes/OperatorNodes/CosOpNode.h"
#include <sstream>
#include <cstdlib>

bool Parser::isOperator(const std::string& token) {
    return token == "+" || token == "-" || token == "*" || token == "/" ||
           token == "sin" || token == "cos";
}

int Parser::getOperatorArity(const std::string& token) {
    if (token == "sin" || token == "cos") {
        return 1;
    } else if (token == "+" || token == "-" || token == "*" || token == "/") {
        return 2;
    }
    return 0;
}

bool Parser::isNumber(const std::string& str) {
    if (str.empty())
        return false;

    size_t start = 0;
    if (str[0] == '-' || str[0] == '+') {
        if (str.length() == 1)
            return false;

        start = 1;
    }

    for (size_t i = start; i < str.length(); i++) {
        if (str[i] == '.')
            return false;

        if (str[i] < '0' || str[i] > '9')
            return false;
    }

    return true;
}

Node* Parser::createOperatorNode(const std::string& str, Node* left, Node* right) {
    if (str == "+") {
        return new AddOpNode(left, right);
    } else if (str == "-") {
        return new MinOpNode(left, right);
    } else if (str == "*") {
        return new MultOpNode(left, right);
    } else if (str == "/") {
        return new DivOpNode(left, right);
    }
    return NULL;
}

Node* Parser::createUnaryOperatorNode(const std::string& str, Node* child) {
    if (str == "sin") {
        return new SinOpNode(child);
    } else if (str == "cos") {
        return new CosOpNode(child);
    }
    return NULL;
}

Node* Parser::createLeafNode(const std::string& str) {
    if (isNumber(str)) {
        return new ConstNode(std::strtol(str.c_str(), NULL, 10));
    } else {
        return new VarNode(str);
    }
}

Node* Parser::createDefaultNode() {
    return new ConstNode(1);
}

Node* Parser::parseNode(std::istringstream& iss, bool& isValid, std::ostringstream& fixedStream, bool& firstToken) {
    std::string token;

    // Sprawdź czy są jeszcze tokeny
    if (!(iss >> token)) {
        isValid = false;
        if (!firstToken) {
            fixedStream << " ";
        }
        fixedStream << "1";
        firstToken = false;
        return createDefaultNode();
    }

    if (!firstToken) {
        fixedStream << " ";
    }
    fixedStream << token;
    firstToken = false;

    // Jeśli to operator, rekurencyjnie parsuj dzieci
    if (isOperator(token)) {
        int arity = getOperatorArity(token);

        if (arity == 1) {
            Node* child = parseNode(iss, isValid, fixedStream, firstToken);
            return createUnaryOperatorNode(token, child);
        } else if (arity == 2) {
            Node* left = parseNode(iss, isValid, fixedStream, firstToken);
            Node* right = parseNode(iss, isValid, fixedStream, firstToken);
            return createOperatorNode(token, left, right);
        }
    }

    // To jest liść (liczba lub zmienna)
    return createLeafNode(token);
}

Node* Parser::parse(const std::string& expression, bool& isValid, std::string& correctedExpression) {
    isValid = true;
    correctedExpression = "";

    if (expression.empty() || expression.find_first_not_of(" \t\n\r") == std::string::npos) {
        isValid = false;
        correctedExpression = "1";
        return createDefaultNode();
    }

    std::istringstream iss(expression);
    std::ostringstream fixedStream;
    bool firstToken = true;

    // Parsuj rekurencyjnie od korzenia
    Node* root = parseNode(iss, isValid, fixedStream, firstToken);

    isValid = false;
    correctedExpression = fixedStream.str();

    return root;
}