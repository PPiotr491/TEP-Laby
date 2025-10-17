#include "Zad123.h"
#include "ConstValues.h"

#include <iostream>

// ZADANIE 1

// stałe zostały zadeklarowane w osobnym pliku nagłówkowym ConstValues.h
void AllocTableFill(const int size) {
    if (size <= 0) {
        std::cout<<"Invalid size"<<std::endl;
        return;
    }

    int *table = new int[size];

    for (int i = 0; i < size; i++) {
        table[i] = ZAD1_FILL_VALUE;
    }

    for (int i = 0; i < size; i++) {
        std::cout<<table[i]<<"; ";
    }

    delete[] table;
}

// ZADANIE 2

bool AllocTable2Dim(int ***tablePointer, const int sizeX, const int sizeY) {
    if (tablePointer == NULL) {
        std::cout<<"Null pointer provided"<<std::endl;
        return false;
    }

    if (sizeX <= 0 || sizeY <= 0) {
        std::cout<<"Invalid size"<<std::endl;
        return false;
    }

    *tablePointer = new int*[sizeY];

    for (int i = 0; i < sizeY; i++) {
        (*tablePointer)[i] = new int[sizeX];

        // jeśli nie udało się zaalokować i-tego wiersza, zwalniam pamięć całej tablicy
        if ((*tablePointer)[i] == NULL) {
            for (int j = 0; j < i; j++) {
                delete[] (*tablePointer)[j];
            }
            delete[] *tablePointer;
            *tablePointer = NULL;

            return false;
        }
    }

    return true;
}

// ZADANIE 3
bool DeallocTable2Dim(int ***tablePointer, const int sizeY) {
    if (tablePointer == NULL || *tablePointer == NULL) {
        std::cout<<"Null pointer or empty table provided"<<std::endl;
        return false;
    }

    for (int i = 0; i < sizeY; i++) {
        delete[] (*tablePointer)[i];
    }
    delete[] *tablePointer;

    *tablePointer = NULL;

    return true;
}


int main() {
    AllocTableFill(10);
    std::cout<<std::endl;

    int sizeX = 5, sizeY = 3;
    int **tablePointer;
    if (AllocTable2Dim(&tablePointer, sizeX, sizeY)) {
        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                tablePointer[i][j] = ZAD1_FILL_VALUE;
            }
        }

        for (int i = 0; i < sizeY; i++) {
            for (int j = 0; j < sizeX; j++) {
                std::cout<<tablePointer[i][j]<<" ";
            }
            std::cout<<std::endl;
        }

        if (DeallocTable2Dim(&tablePointer, sizeY)) {
            std::cout<<"Deallocated the table"<<std::endl;
        } else {
            std::cout<<"Deallocation failed"<<std::endl;
        }
    }

    return 0;
}
