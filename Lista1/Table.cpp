#include "Table.h"

#include <iostream>

Table::Table() {
    this->name = DEFAULT_NAME;
    this->length = DEFAULT_LENGTH;
    this->array = new int[this->length];

    std::cout<<"bezp: "<<name<<std::endl;
}

Table::Table(std::string name, int length) {
    if (length <= 0) {
        std::cout<<"Invalid length, setting default value"<<std::endl;
        this -> length = DEFAULT_LENGTH;
    } else {
        this->length = length;
    }

    this->name = name;
    this->array = new int[this->length];

    std::cout<<"parametr: "<<name<<std::endl;
}

Table::Table(const Table &tableToCopy) {
    if (tableToCopy.array == NULL) {
        std::cout<<"Cannot copy from null array, creating default table"<<std::endl;
        // this->name = DEFAULT_NAME;
        // this->length = DEFAULT_LENGTH;
        // this->array = new int[this->length];

        new Table();

    } else {
        this->name = tableToCopy.name + "_copy";
        this->length = tableToCopy.length;
        this->array = new int[this->length];

        for (int i = 0; i < this->length; i++) {
            this->array[i] = tableToCopy.array[i];
        }
    }

    std::cout<<"kopiuj: "<<name<<std::endl;
}

Table::~Table() {
    if (this->array != NULL) {
        std::cout<<"usuwam: "<<name<<std::endl;

        delete[] this->array;
        this->length = 0;
        this->name = "";
    } else {
        std::cout<<"Table is already deleted"<<std::endl;
    }
}

Table *Table::Clone() {
    if (this->array == NULL) {
        std::cout<<"Cannot copy from null array, creating default table"<<std::endl;
        return new Table();
    }

    return new Table(*this);
}

void Table::setName(std::string newName) {
    this->name = newName;
}

bool Table::setLength(int newLength) {
    if (newLength <= 0) {
        std::cout<<"Invalid length, length not changed"<<std::endl;
        return false;
    }

    int* tempArray = new int[newLength];

    // jeśli nowy rozmiar tablicy jest mniejszy, to nie kopiuje wszystkich elementów
    int elementsToCopy = (newLength < length)? newLength : length;
    for (int i = 0; i < elementsToCopy; i++) {
        tempArray[i] = this->array[i];
    }

    delete[] this->array;

    this->array = tempArray;
    this->length = newLength;

    return true;
}

