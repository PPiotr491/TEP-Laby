#include "CNumber.cpp"
#include "iostream"

int main() {
    CNumber *number = new CNumber();
    number->operator=(-2456);

    CNumber cnum0, cnum1;
    cnum0 = INT_MAX;
    cnum1 = INT_MAX;

    std::cout<<std::endl;
    std::cout<<std::endl<<number->toString();
    std::cout<<std::endl<<cnum0.toString();
    std::cout<<std::endl<<cnum1.toString();

    std::cout<<std::endl<<"Dodawanie: ";
    CNumber cnum3 = cnum0 + cnum1;
    std::cout<<std::endl<<cnum3.toString();
    std::cout<<std::endl<<cnum0.toString();

    std::cout<<std::endl<<"Odejmowanie: ";
    CNumber cnum4 = cnum0 - cnum3;
    std::cout<<std::endl<<cnum4.toString();
    std::cout<<std::endl<<cnum0.toString();

    std::cout<<std::endl<<"Mnozenie: ";
    CNumber cnum5 = cnum4 * cnum3;
    std::cout<<std::endl<<cnum5.toString();
    std::cout<<std::endl<<cnum0.toString();

    std::cout<<std::endl<<"Dzielenie: ";
    CNumber cnum6 = cnum5 / cnum1;
    std::cout<<std::endl<<cnum6.toString();
    std::cout<<std::endl<<cnum0.toString();

    delete number;

    return 0;
}