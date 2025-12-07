#include <iostream>
#include <cmath>
#include <sstream>
#include <vector>

#include "Tree/EquationTree.h"
#include "Result.tpp"
#include "Error.h"

void printMenu() {
    std::cout << "\n=== KALKULATOR DRZEW WYRAZEN ===" << std::endl;
    std::cout << "Dostepne komendy:" << std::endl;
    std::cout << "  enter <formula>  - wczytaj nowa formule" << std::endl;
    std::cout << "  vars             - wyswietl zmienne" << std::endl;
    std::cout << "  print            - wyswietl drzewo" << std::endl;
    std::cout << "  comp <v1> ...    - oblicz wartosc" << std::endl;
    std::cout << "  join <formula>   - dolacz nowa formule" << std::endl;
    std::cout << "  help             - wyswietl pomoc" << std::endl;
    std::cout << "  mr               - zwraca lisc najbardziej po prawo" << std::endl;
    std::cout << "  exit             - zakoncz program" << std::endl;
    std::cout << "=================================" << std::endl;
}

int main() {
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
               std::cout << "Drzewo zbudowane poprawnie";
            } else {
                std::vector<Error*> errors = result.getErrors();
                for (Error* e : errors) {
                    std::cout << e->toString();
                }
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
                std::vector<Error*> errors = result.getErrors();
                for (Error* e : errors) {
                    std::cout << e->toString();
                }
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
                std::vector<Error*> errors = result.getErrors();
                for (Error* e : errors) {
                    std::cout << e->toString();
                }
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
                for (Error* e : errors) {
                    std::cout << e->toString();
                }
            }

        } else if (command == "join") {
            std::string formula;
            std::getline(iss, formula);
            if (!formula.empty() && formula[0] == ' ') {
                formula = formula.substr(1);
            }

            Result<void, Error> result = tree.join(formula);
            if (result.isSuccess()) {
                std::cout << "Drzewo zbudowane poprawnie";
            } else {
                std::vector<Error*> errors = result.getErrors();
                for (Error* e : errors) {
                    std::cout << e->toString();
                }
            }
        } else if (command == "mr") {
            Result<std::string, Error> result = tree.mr();
            if (result.isSuccess()) {
                std::cout << result.getValue() << std::endl;
            } else {
                std::vector<Error*> errors = result.getErrors();
                for (Error* e : errors) {
                    std::cout << e->toString();
                }
            }

        } else {
            std::cout << "Nieznana komenda. Wpisz 'help' aby zobaczyc dostepne komendy." << std::endl;
        }
    }

    return 0;
}