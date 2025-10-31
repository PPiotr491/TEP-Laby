#include "CNumber.cpp"
#include "iostream"

int main() {
    CNumber *number = new CNumber();
    number->operator=(-2456);

    CNumber cnum0, cnum1;
    cnum0 = 368;
    cnum1 = 1567;
    cnum0 = cnum1;

    std::cout<<std::endl;
    std::cout<<std::endl<<number->toString();
    std::cout<<std::endl<<cnum0.toString();
    std::cout<<std::endl<<cnum1.toString();

    CNumber cnum3 = cnum0 + cnum1;
    std::cout<<std::endl<<cnum3.toString();
    std::cout<<std::endl<<cnum0.toString();
}