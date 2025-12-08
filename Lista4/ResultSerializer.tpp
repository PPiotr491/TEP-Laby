#ifndef TEP_RESULTSERIALIZER_TPP
#define TEP_RESULTSERIALIZER_TPP

#include "ResultSerializer.h"
#include <sstream>

// ============================================================================================
// ||                          Implementacja klasy bazowej                                   ||
// ============================================================================================

template <typename T, typename E>
ResultSerializer<T, E>::ResultSerializer() {
}

template <typename T, typename E>
ResultSerializer<T, E>::~ResultSerializer() {
}

template <typename T, typename E>
bool ResultSerializer<T, E>::saveToFile(const std::string& filename, const Result<T, E>& result) {
    std::ofstream out(filename.c_str());
    if (!out.is_open()) {
        return false;
    }

    // Dla typów innych niż EquationTree* zapisujemy tylko błędy
    const std::vector<E*>& errors = result.getErrors();

    if (errors.empty()) {
        out << "NO_ERRORS" << std::endl;
    } else {
        out << "ERRORS" << std::endl;
        writeErrors(out, errors);
    }

    out.close();
    return true;
}

template <typename T, typename E>
Result<T, E> ResultSerializer<T, E>::loadFromFile(const std::string& filename) {
    std::ifstream in(filename.c_str());
    if (!in.is_open()) {
        E* error = new E("Nie mozna otworzyc pliku: " + filename);
        return Result<T, E>::resultFail(error);
    }

    std::string line;
    std::getline(in, line);

    if (line == "NO_ERRORS") {
        in.close();
        // Nie ma błędów, ale nie możemy zwrócić poprawnego wyniku bez wartości
        E* error = new E("Brak danych wartosci w pliku");
        return Result<T, E>::resultFail(error);
    } else if (line == "ERRORS") {
        std::vector<E*> errors = readErrors(in);
        in.close();
        return Result<T, E>::resultFail(errors);
    }

    in.close();
    E* error = new E("Niepoprawny format pliku");
    return Result<T, E>::resultFail(error);
}

template <typename T, typename E>
void ResultSerializer<T, E>::writeErrors(std::ofstream& out, const std::vector<E*>& errors) {
    out << errors.size() << std::endl;
    for (size_t i = 0; i < errors.size(); i++) {
        out << errors[i]->toString() << std::endl;
    }
}

template <typename T, typename E>
std::vector<E*> ResultSerializer<T, E>::readErrors(std::ifstream& in) {
    std::vector<E*> errors;
    size_t errorCount = 0;
    in >> errorCount;
    in.ignore(); // Ignoruj znak nowej linii

    for (size_t i = 0; i < errorCount; i++) {
        std::string errorDesc;
        std::getline(in, errorDesc);
        E* error = new E(errorDesc);
        errors.push_back(error);
    }

    return errors;
}

// ============================================================================================
// ||                     Specjalizacja dla EquationTree*                                    ||
// ============================================================================================

template <typename E>
ResultSerializer<EquationTree*, E>::ResultSerializer() {
}

template <typename E>
ResultSerializer<EquationTree*, E>::~ResultSerializer() {
}

template <typename E>
bool ResultSerializer<EquationTree*, E>::saveToFile(const std::string& filename, const Result<EquationTree*, E>& result) {
    std::ofstream out(filename.c_str());
    if (!out.is_open()) {
        return false;
    }

    // Sprawdzamy czy są błędy
    const std::vector<E*>& errors = result.getErrors();

    if (errors.empty()) {
        // Brak błędów - zapisujemy drzewo
        out << "TREE" << std::endl;
        EquationTree* tree = result.getValue();
        writeTree(out, tree);
    } else {
        // Są błędy - zapisujemy błędy
        out << "ERRORS" << std::endl;
        writeErrors(out, errors);
    }

    out.close();
    return true;
}

template <typename E>
Result<EquationTree*, E> ResultSerializer<EquationTree*, E>::loadFromFile(const std::string& filename) {
    std::ifstream in(filename.c_str());
    if (!in.is_open()) {
        E* error = new E("Nie mozna otworzyc pliku: " + filename);
        return Result<EquationTree*, E>::resultFail(error);
    }

    std::string line;
    std::getline(in, line);

    if (line == "TREE") {
        EquationTree* tree = readTree(in);
        in.close();
        if (tree != NULL) {
            return Result<EquationTree*, E>::resultOk(tree);
        } else {
            E* error = new E("Blad podczas odczytu drzewa z pliku");
            return Result<EquationTree*, E>::resultFail(error);
        }
    } else if (line == "ERRORS") {
        std::vector<E*> errors = readErrors(in);
        in.close();
        return Result<EquationTree*, E>::resultFail(errors);
    }

    in.close();
    E* error = new E("Niepoprawny format pliku");
    return Result<EquationTree*, E>::resultFail(error);
}

template <typename E>
void ResultSerializer<EquationTree*, E>::writeErrors(std::ofstream& out, const std::vector<E*>& errors) {
    out << errors.size() << std::endl;
    for (size_t i = 0; i < errors.size(); i++) {
        out << errors[i]->getErrorDescription() << std::endl;
    }
}

template <typename E>
std::vector<E*> ResultSerializer<EquationTree*, E>::readErrors(std::ifstream& in) {
    std::vector<E*> errors;
    size_t errorCount = 0;
    in >> errorCount;
    in.ignore(); // Ignoruj znak nowej linii

    for (size_t i = 0; i < errorCount; i++) {
        std::string errorDesc;
        std::getline(in, errorDesc);
        E* error = new E(errorDesc);
        errors.push_back(error);
    }

    return errors;
}

template <typename E>
void ResultSerializer<EquationTree*, E>::writeTree(std::ofstream& out, EquationTree* tree) {
    if (tree == NULL) {
        out << "NULL" << std::endl;
        return;
    }

    // Pobieram drzewo używając print()
    Result<std::string, E> printResult = tree->print();

    if (printResult.isSuccess()) {
        std::string treeString = printResult.getValue();
        out << treeString << std::endl;
    } else {
        out << "NULL" << std::endl;
    }
}

template <typename E>
EquationTree* ResultSerializer<EquationTree*, E>::readTree(std::ifstream& in) {
    std::string line;
    std::getline(in, line);

    if (line == "NULL" || line.empty()) {
        return NULL;
    }

    // Tworze nowe drzewo i wczytuje metoda enter
    EquationTree* tree = new EquationTree();
    Result<void, E> enterResult = tree->enter(line);

    if (enterResult.isSuccess()) {
        return tree;
    } else {
        delete tree;
        return NULL;
    }
}

#endif //TEP_RESULTSERIALIZER_TPP

