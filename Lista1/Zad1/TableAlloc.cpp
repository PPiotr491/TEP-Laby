#include "TableAlloc.h"

#include <iostream>

void AllocTableFill(const int size) {
    const int FILL_VALUE = 34;

    double *table = new double[size];

    for (int i = 0; i < size; i++) {
        table[i] = FILL_VALUE;
    }

    for (int i = 0; i < size; i++) {
        std::cout<<table[i]<<"; ";
    }

    delete[] table;
}

int main() {
    AllocTableFill(10);

    return 0;
}
