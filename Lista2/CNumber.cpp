#include "CNumber.h"

#include <iostream>
#include <sstream>

#include "cmath"

CNumber::CNumber() {
    this -> length = DEFAULT_SIZE;
    this -> numTable = new int[length];
    this -> isNegative = false;
}

CNumber::CNumber(int length, int* numTable, bool isNegative) {
    this -> length = length;
    this -> numTable = new int[length];
    this -> isNegative = isNegative;

    for (int i = 0; i < length; i++) {
        this->numTable[i] = numTable[i];
    }
}

// CNumber::CNumber(const CNumber &toCopy) {
//     setLength(toCopy.getLength());
//
// }

CNumber::~CNumber() {
    delete[] getNumTable();
}

CNumber& CNumber::operator=(const int value) {
    int valueCopy = value;
    if (valueCopy < 0) {
        setIsNegative(true);
        valueCopy = abs(valueCopy);
    }

    setLength(std::log10(valueCopy)+1);

    int* decimal = new int[getLength()]();

    for (int i = getLength() - 1; i >= 0 && valueCopy != 0; i--) {
        decimal[i] = (valueCopy % NUMERICAL_SYSTEM);
        valueCopy = valueCopy / NUMERICAL_SYSTEM;
    }

    std::cout<<std::endl;
    for (int i = 0; i < getLength(); i++) {
        std::cout<<decimal[i];
    }

    delete[] getNumTable();
    setNumTable(decimal);

    return *this;
}

CNumber& CNumber::operator=(const CNumber &other) {
    if (this == &other) {
        return *this;
    }

    delete[] this->getNumTable();
    setLength(other.getLength());
    setNumTable(new int[getLength()]);

    for (int i = 0; i < getLength(); i++) {
        getNumTable()[i] = other.getNumTable()[i];
    }

    return *this;
}

CNumber CNumber::operator+(const CNumber &numToAdd) {
    bool newIsNegative = false;
    int newLength;
    if (this->getLength() >= numToAdd.getLength()) {
        newLength = this->getLength() + 1;
    } else {
        newLength = numToAdd.getLength() + 1;
    }

    int* fstNum = ExpandNumber(newLength, *this);
    int* secNum = ExpandNumber(newLength, numToAdd);

    int* newNumber = new int[newLength]();

    if (!this->getIsNegative() && !numToAdd.getIsNegative()) {
        newIsNegative = false;
    } else if (this->getIsNegative() && numToAdd.getIsNegative()) {
        newIsNegative = true;
    } else {
        newIsNegative = true;
    }

    for (int i = newLength - 1; i >= 0; i--) {
        newNumber[i] += fstNum[i] + secNum[i];

        if (newNumber[i] > MAX_NUMBER_VALUE) {
            newNumber[i-1] += newNumber[i] / NUMERICAL_SYSTEM;
            newNumber[i] = newNumber[i] % NUMERICAL_SYSTEM;
        }
    }

    delete[] fstNum;
    delete[] secNum;

    CNumber result(newLength, newNumber, newIsNegative);
    delete[] newNumber;  // Zwolnij pamięć po skopiowaniu do konstruktora

    return result;
}

CNumber CNumber::operator-(const CNumber &numToAdd) {
    bool newIsNegative = false;
    int newLength;
    if (this->getLength() >= numToAdd.getLength()) {
        newLength = this->getLength() + 1;
    } else {
        newLength = numToAdd.getLength() + 1;
    }

    int* fstNum = ExpandNumber(newLength, *this);
    int* secNum = ExpandNumber(newLength, numToAdd);

    int* newNumber = new int[newLength]();
}

CNumber CNumber::operator*(const CNumber &numToAdd) {
}

CNumber CNumber::operator/(const CNumber &numToAdd) {
}

int* CNumber::ExpandNumber(int newLength, const CNumber& numTable) {
    int* expanded = new int[newLength]();
    for (int i = numTable.getLength() - 1, j = newLength - 1; i >= 0; i--, j--) {
        expanded[j] = numTable.getNumTable()[i];
    }

    return expanded;
}

std::string CNumber::toString() const {
    std::stringstream stream;

    if (getLength() < 1) {
        stream << "Null number";
    } else {
        if (getIsNegative()) {
            stream << "-";
        }

        for (int i = 0; i < getLength(); i++) {
           stream << getNumTable()[i];
        }
    }

    return stream.str();
}