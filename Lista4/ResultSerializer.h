#ifndef TEP_RESULTSERIALIZER_H
#define TEP_RESULTSERIALIZER_H

#include "Result.tpp"
#include "Error.h"
#include "Tree/EquationTree.h"
#include <string>
#include <fstream>
#include <vector>

// Klasa bazowa do serializacji Result
template <typename T, typename E>
class ResultSerializer {
public:
    ResultSerializer();
    ~ResultSerializer();

    // Zapisuje Result do pliku
    bool saveToFile(const std::string& filename, const Result<T, E>& result);

    // Odczytuje Result z pliku
    Result<T, E> loadFromFile(const std::string& filename);

private:
    // Zapisuje błędy do strumienia
    void writeErrors(std::ofstream& out, const std::vector<E*>& errors);

    // Odczytuje błędy ze strumienia
    std::vector<E*> readErrors(std::ifstream& in);
};

// Specjalizacja dla EquationTree*
template <typename E>
class ResultSerializer<EquationTree*, E> {
public:
    ResultSerializer();
    ~ResultSerializer();

    // Zapisuje Result do pliku
    bool saveToFile(const std::string& filename, const Result<EquationTree*, E>& result);

    // Odczytuje Result z pliku
    Result<EquationTree*, E> loadFromFile(const std::string& filename);

private:
    // Zapisuje błędy do strumienia
    void writeErrors(std::ofstream& out, const std::vector<E*>& errors);

    // Odczytuje błędy ze strumienia
    std::vector<E*> readErrors(std::ifstream& in);

    // Zapisuje drzewo w postaci prefiksowej
    void writeTree(std::ofstream& out, EquationTree* tree);

    // Odczytuje drzewo w postaci prefiksowej
    EquationTree* readTree(std::ifstream& in);
};

#include "ResultSerializer.tpp"

#endif //TEP_RESULTSERIALIZER_H

