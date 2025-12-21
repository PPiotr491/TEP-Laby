#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include "Tree/EquationTree.h"
#include "Result.tpp"
#include "Error.h"
#include "ResultSerializer.h"

Result<int*, int> eTest(int value) {
    if (value % 2 == 0) {
        return Result<int*, int>::resultFail(new int(1));
    }

    return Result<int*, int>::resultOk(new int(2));
}

// Funkcja automatycznie zapisująca błędy do pliku errors.txt
void saveErrorsToFile(const std::vector<Error*>& errors) {
    if (errors.empty()) return;

    // Klonuj błędy do wektora
    std::vector<Error*> errorsCopy;
    for (size_t i = 0; i < errors.size(); i++) {
        errorsCopy.push_back(errors[i]->clone());
    }

    // Utwórz Result z błędami i zapisz do pliku
    Result<EquationTree*, Error> errorResult(errorsCopy);
    ResultSerializer<EquationTree*, Error> serializer;
    serializer.saveToFile("errors.txt", errorResult);
}

void printMenu() {
    std::cout << "\n=== KALKULATOR DRZEW WYRAZEN ===" << std::endl;
    std::cout << "Dostepne komendy:" << std::endl;
    std::cout << "  enter <formula>  - wczytaj nowa formule" << std::endl;
    std::cout << "  vars             - wyswietl zmienne" << std::endl;
    std::cout << "  print            - wyswietl drzewo" << std::endl;
    std::cout << "  comp <v1> ...    - oblicz wartosc" << std::endl;
    std::cout << "  join <formula>   - dolacz nowa formule" << std::endl;
    std::cout << "  save <file>      - zapisz drzewo do pliku" << std::endl;
    std::cout << "  load <file>      - wczytaj drzewo z pliku" << std::endl;
    std::cout << "  mr               - zwraca lisc najbardziej po prawo" << std::endl;
    std::cout << "  help             - wyswietl pomoc" << std::endl;
    std::cout << "  exit             - zakoncz program" << std::endl;
    std::cout << "=================================" << std::endl;
}

int main() {
    std::cout << eTest(2).isSuccess() << std::endl;
    std::cout << eTest(3).isSuccess() << std::endl;

    EquationTree tree;
    std::string line;

    std::cout << "Kalkulator drzew wyrazen (notacja polska)" << std::endl;
    std::cout << "Wpisz 'help' aby zobaczyc pomoc" << std::endl;

    while (true) {
        std::cout << "\n> ";

        if (!std::getline(std::cin, line)) {
            break;
        }

        if (line.empty()) {
            continue;
        }

        std::istringstream iss(line);
        std::string command;
        iss >> command;

        if (command == "exit") {
            std::cout << "Do widzenia!" << std::endl;
            break;
        } else if (command == "help") {
            printMenu();

        } else if (command == "enter") {
            std::string formula;
            std::getline(iss, formula);
            if (!formula.empty() && formula[0] == ' ') {
                formula = formula.substr(1);
            }

            Result<void, Error> result = tree.enter(formula);
            if (result.isSuccess()) {
               std::cout << "Drzewo zbudowane poprawnie" << std::endl;
            } else {
                const std::vector<Error*>& errors = result.getErrors();
                for (size_t i = 0; i < errors.size(); i++) {
                    std::cout << errors[i]->toString() << std::endl;
                }
                saveErrorsToFile(errors);
            }

        } else if (command == "vars") {
            Result<std::string, Error> result = tree.vars();
            if (result.isSuccess()) {
                std::string vars = result.getValue();
                if (vars.empty()) {
                    std::cout << "Brak zmiennych w drzewie." << std::endl;
                } else {
                    std::cout << "Zmienne: " << vars << std::endl;
                }
            } else {
                const std::vector<Error*>& errors = result.getErrors();
                for (size_t i = 0; i < errors.size(); i++) {
                    std::cout << errors[i]->toString() << std::endl;
                }
                saveErrorsToFile(errors);
            }

        } else if (command == "print") {
            Result<std::string, Error> result = tree.print();
            if (result.isSuccess()) {
                if (result.getValue().empty()) {
                    std::cout << "Drzewo jest puste." << std::endl;
                } else {
                    std::cout << "Drzewo: " << result.getValue() << std::endl;
                }
            } else {
                const std::vector<Error*>& errors = result.getErrors();
                for (size_t i = 0; i < errors.size(); i++) {
                    std::cout << errors[i]->toString() << std::endl;
                }
                saveErrorsToFile(errors);
            }

        } else if (command == "comp") {
            std::vector<double> values;
            double value;

            while (iss >> value) {
                values.push_back(value);
            }

            Result<double, Error> result = tree.comp(values);
            if (result.isSuccess()) {
                std::cout << "Wynik: " << result.getValue() << std::endl;
            } else {
                std::vector<Error*> errors = result.getErrors();
                for (size_t i = 0; i < errors.size(); i++) {
                    std::cout << errors[i]->toString() << std::endl;
                }
                saveErrorsToFile(errors);
            }

        } else if (command == "join") {
            std::string formula;
            std::getline(iss, formula);
            if (!formula.empty() && formula[0] == ' ') {
                formula = formula.substr(1);
            }

            Result<void, Error> result = tree.join(formula);
            if (result.isSuccess()) {
                std::cout << "Drzewo zbudowane poprawnie" << std::endl;
            } else {
                const std::vector<Error*>& errors = result.getErrors();
                for (size_t i = 0; i < errors.size(); i++) {
                    std::cout << errors[i]->toString() << std::endl;
                }
                saveErrorsToFile(errors);
            }
        } else if (command == "mr") {
            Result<std::string, Error> result = tree.mr();
            if (result.isSuccess()) {
                std::cout << result.getValue() << std::endl;
            } else {
                const std::vector<Error*>& errors = result.getErrors();
                for (size_t i = 0; i < errors.size(); i++) {
                    std::cout << errors[i]->toString() << std::endl;
                }
                saveErrorsToFile(errors);
            }

        } else if (command == "save") {
            std::string filename;
            iss >> filename;

            if (filename.empty()) {
                std::cout << "Brak nazwy pliku. Uzycie: save <nazwa_pliku>" << std::endl;
            } else {
                // Zapisz poprawne drzewo do pliku podanego przez użytkownika
                EquationTree* treeCopy = new EquationTree(tree);
                Result<EquationTree*, Error> treeResult(treeCopy);
                ResultSerializer<EquationTree*, Error> serializer;

                if (serializer.saveToFile(filename, treeResult)) {
                    std::cout << "Drzewo zapisane do pliku: " << filename << std::endl;
                } else {
                    std::cout << "Blad podczas zapisu do pliku: " << filename << std::endl;
                }
            }

        } else if (command == "load") {
            std::string filename;
            iss >> filename;

            if (filename.empty()) {
                std::cout << "Brak nazwy pliku. Uzycie: load <nazwa_pliku>" << std::endl;
            } else {
                ResultSerializer<EquationTree*, Error> serializer;
                Result<EquationTree*, Error> loadedResult = serializer.loadFromFile(filename);

                if (loadedResult.isSuccess()) {
                    EquationTree* loadedTree = loadedResult.getValue();
                    tree = *loadedTree;
                    delete loadedTree;
                    std::cout << "Drzewo wczytane z pliku: " << filename << std::endl;
                } else {
                    std::cout << "Blad podczas wczytywania z pliku:" << std::endl;
                    const std::vector<Error*>& errors = loadedResult.getErrors();
                    for (size_t i = 0; i < errors.size(); i++) {
                        std::cout << "  " << errors[i]->toString() << std::endl;
                    }
                    saveErrorsToFile(errors);
                }
            }

        } else {
            std::cout << "Nieznana komenda. Wpisz 'help' aby zobaczyc dostepne komendy." << std::endl;
        }
    }


    return 0;
}