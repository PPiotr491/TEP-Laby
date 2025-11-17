#include "CNumber.cpp"
#include "iostream"

int main() {
    CNumber *number = new CNumber();
    number->operator=(-2456);

    // CNumber cnum0, cnum1, cnum8;
    // cnum0 = INT_MAX;
    // cnum1 = INT_MAX;
    // cnum8 = 123456;

    CNumber cnum0, cnum1, cnum2;
    cnum0 = 379;
    cnum1 = -999;
    cnum2 = cnum0 + cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" + "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = 379;
    cnum1 = 999;
    cnum2 = cnum0 - cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" - "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = -1000;
    cnum1 = 22;
    cnum2 = cnum0 + cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" + "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = 999;
    cnum1 = 1;
    cnum2 = cnum0 + cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" + "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = 37;
    cnum1 = -11;
    cnum2 = cnum0 * cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" * "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = -99;
    cnum1 = -2;
    cnum2 = cnum0 * cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" * "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = 121;
    cnum1 = 3012;
    cnum2 = cnum0 * cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" * "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = 364452;
    cnum1 = 13;
    cnum2 = cnum0 / cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" / "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = 3448182;
    cnum1 = -123;
    cnum2 = cnum0 / cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" / "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = -89998;
    cnum1 = -7777;
    cnum2 = cnum0 / cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" / "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = INT_MAX;
    cnum1 = INT_MAX;
    cnum2 = cnum0 * cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" * "<<cnum1.toString()<<" = "<<cnum2.toString();

    cnum0 = INT_MAX;
    cnum1 = 2;
    cnum2 = cnum0 / cnum1;
    std::cout<<std::endl<<cnum0.toString()<<" + "<<cnum1.toString()<<" = "<<cnum2.toString();

    std::cout<<std::endl<<"Silnia: ";
    cnum0 = INT_MAX;
    cnum2 = !cnum0;
    std::cout<<std::endl<<"!"<<cnum0.toString()<<" = "<<cnum2.toString();

    delete number;

    return 0;
}