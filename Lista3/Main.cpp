#include "EquationTree.h"
#include <iostream>
#include <sstream>
#include <vector>

void printMenu() {
    std::cout << "\n=== KALKULATOR DRZEW WYRAZEN ===" << std::endl;
    std::cout << "Dostepne komendy:" << std::endl;
    std::cout << "  enter <formula>  - wczytaj nowa formule" << std::endl;
    std::cout << "  vars             - wyswietl zmienne" << std::endl;
    std::cout << "  print            - wyswietl drzewo" << std::endl;
    std::cout << "  comp <v1> ...    - oblicz wartosc" << std::endl;
    std::cout << "  join <formula>   - dolacz nowa formule" << std::endl;
    std::cout << "  help             - wyswietl pomoc" << std::endl;
    std::cout << "  exit             - zakoncz program" << std::endl;
    std::cout << "=================================" << std::endl;
}

int main() {
    EquationTree tree;
    std::string line;

    std::cout << "Kalkulator drzew wyrazen (notacja polska)" << std::endl;
    std::cout << "Przyklad: + 2 3  (oznacza 2 + 3)" << std::endl;
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

        if (command == "exit" || command == "quit") {
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
            std::cout << tree.enter(formula);

        } else if (command == "vars") {
            std::string vars = tree.vars();
            if (vars.empty()) {
                std::cout << "Brak zmiennych w drzewie." << std::endl;
            } else {
                std::cout << "Zmienne: " << vars << std::endl;
            }

        } else if (command == "print") {
            std::string result = tree.print();
            if (result.empty()) {
                std::cout << "Drzewo jest puste." << std::endl;
            } else {
                std::cout << "Drzewo: " << result << std::endl;
            }

        } else if (command == "comp") {
            std::vector<double> values;
            double value;

            while (iss >> value) {
                values.push_back(value);
            }

            double result = tree.comp(values);
            std::cout << "Wynik: " << result << std::endl;

        } else if (command == "join") {
            std::string formula;
            std::getline(iss, formula);
            if (!formula.empty() && formula[0] == ' ') {
                formula = formula.substr(1);
            }
            std::cout << tree.join(formula);
        } else {
            std::cout << "Nieznana komenda. Wpisz 'help' aby zobaczyc dostepne komendy." << std::endl;
        }
    }

    return 0;
}