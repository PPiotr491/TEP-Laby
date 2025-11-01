#include "CNumber.h"

#include <iostream>
#include <sstream>

#include "cmath"

CNumber::CNumber() {
    setLength(DEFAULT_SIZE);
    setNumTable(new int[DEFAULT_SIZE]());
    setIsNegative(false);
}

CNumber::CNumber(int length, int* numTable, bool isNegative) {
    int* newNumTable = new int[length];
    for (int i = 0; i < length; i++) {
        newNumTable[i] = numTable[i];
    }

    setLength(length);
    setNumTable(newNumTable);
    setIsNegative(isNegative);
}

CNumber::CNumber(const CNumber &toCopy) {
    int* newNumTable = new int[toCopy.getLength()];
    for (int i = 0; i < toCopy.getLength(); i++) {
        newNumTable[i] = toCopy.getNumTable()[i];
    }

    setLength(toCopy.getLength());
    setNumTable(newNumTable);
    setIsNegative(toCopy.getIsNegative());
}

CNumber::~CNumber() {
    delete[] getNumTable();
}

CNumber& CNumber::operator=(const int value) {
    int valueCopy = value;
    if (valueCopy < 0) {
        setIsNegative(true);
        valueCopy = abs(valueCopy);
    } else {
        setIsNegative(false);
    }

    int newLen = (valueCopy == 0) ? 1 : std::log10(valueCopy) + 1;

    // Zwolnij starą pamięć
    delete[] getNumTable();

    // Stwórz nową lokalną tablicę
    int* newNumTable = new int[newLen]();

    for (int i = newLen - 1; i >= 0 && valueCopy != 0; i--) {
        newNumTable[i] = (valueCopy % NUMERICAL_SYSTEM);
        valueCopy = valueCopy / NUMERICAL_SYSTEM;
    }

    // Ustaw nową długość i tablicę
    setLength(newLen);
    setNumTable(newNumTable);

    std::cout<<std::endl;
    for (int i = 0; i < getLength(); i++) {
        std::cout<<getNumTable()[i];
    }

    return *this;
}

CNumber& CNumber::operator=(const CNumber &other) {
    if (this == &other) {
        return *this;
    }

    // Zwolnij starą pamięć
    delete[] getNumTable();

    // Stwórz nową lokalną tablicę i skopiuj dane
    int* newNumTable = new int[other.getLength()];
    for (int i = 0; i < other.getLength(); i++) {
        newNumTable[i] = other.getNumTable()[i];
    }

    // Ustaw nowe wartości przez settery
    setLength(other.getLength());
    setIsNegative(other.getIsNegative());
    setNumTable(newNumTable);

    return *this;
}

// a + b
// a + (-b) = a - b
// (-a) + b = b - a
// (-a) + (-b) = -(a + b)
CNumber CNumber::operator+(const CNumber &other) {
    // Przypadek: a + (-b) = a - b
    if (!this->getIsNegative() && other.getIsNegative()) {
        CNumber positiveOther(other.getLength(), other.getNumTable(), false);
        return this->operator-(positiveOther);
    }

    // Przypadek: (-a) + b = a - b
    if (this->getIsNegative() && !other.getIsNegative()) {
        CNumber positiveThis(this->getLength(), this->getNumTable(), false);
        CNumber result = positiveThis.operator-(other);
        return result;
    }

    // Przypadek: (-a) - (-b) = -(a + b)
    if (this->getIsNegative() && other.getIsNegative()) {
        CNumber positiveThis(this->getLength(), this->getNumTable(), false);
        CNumber positiveOther(other.getLength(), other.getNumTable(), false);
        return positiveOther.operator-(positiveThis);
    }

    // Przypadek: a + b
    bool newIsNegative = false;
    int newLength = (this->getLength() >= other.getLength()) ? this->getLength() + 1 : other.getLength() + 1;

    int* fstNum = ExpandNumber(newLength, *this);
    int* secNum = ExpandNumber(newLength, other);

    int* newNumber = new int[newLength]();

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

// a - b
// a - (-b) = a + b
// -a - b = -(a + b)
// -a - (-b) = b - a
CNumber CNumber::operator-(const CNumber &other) {
    // Przypadek: a - (-b) = a + b
    if (!this->getIsNegative() && other.getIsNegative()) {
        CNumber positiveOther(other.getLength(), other.getNumTable(), false);
        return this->operator+(positiveOther);
    }

    // Przypadek: -a - b = -(a + b)
    if (this->getIsNegative() && !other.getIsNegative()) {
        CNumber positiveThis(this->getLength(), this->getNumTable(), false);
        CNumber result = positiveThis.operator+(other);
        result.setIsNegative(true);
        return result;
    }

    // Przypadek: -a - (-b) = b - a
    if (this->getIsNegative() && other.getIsNegative()) {
        CNumber positiveThis(this->getLength(), this->getNumTable(), false);
        CNumber positiveOther(other.getLength(), other.getNumTable(), false);
        return positiveOther.operator-(positiveThis);
    }

    // Przypadek: a - b (obie dodatnie)
    int newLength = (this->getLength() >= other.getLength()) ? this->getLength() : other.getLength();
    bool newIsNegative = false;

    int* fstNum;
    int* secNum;

    // Sprawdź która liczba jest większa
    if (*this >= other) {
        fstNum = ExpandNumber(newLength, *this);
        secNum = ExpandNumber(newLength, other);
        newIsNegative = false;
    } else {
        // Jeśli this < other, odwróć kolejność i ustaw znak ujemny
        fstNum = ExpandNumber(newLength, other);
        secNum = ExpandNumber(newLength, *this);
        newIsNegative = true;
    }

    int* newNumber = new int[newLength]();

    // Odejmowanie z pożyczką
    for (int i = newLength - 1; i >= 0; i--) {
        newNumber[i] = fstNum[i] - secNum[i];

        // Jeśli wynik jest ujemny, pożycz z poprzedniej pozycji
        if (newNumber[i] < 0) {
            newNumber[i] += NUMERICAL_SYSTEM;
            if (i > 0) {
                fstNum[i-1]--;
            }
        }
    }

    delete[] fstNum;
    delete[] secNum;

    CNumber result(newLength, newNumber, newIsNegative);
    delete[] newNumber;

    return result;
}

CNumber CNumber::operator*(const CNumber &numToAdd) {
}

CNumber CNumber::operator/(const CNumber &numToAdd) {
}

int CNumber::compare(const CNumber &other) const {
    // Sprawdź znaki
    if (!this->getIsNegative() && other.getIsNegative()) return 1;   // dodatnia > ujemna
    if (this->getIsNegative() && !other.getIsNegative()) return -1;  // ujemna < dodatnia

    // Obie mają ten sam znak
    int newLength = (this->getLength() >= other.getLength()) ? this->getLength() : other.getLength();
    int* fstNum = ExpandNumber(newLength, *this);
    int* secNum = ExpandNumber(newLength, other);

    int result = 0;
    for (int i = 0; i < newLength; i++) {
        if (fstNum[i] > secNum[i]) {
            result = 1;
            break;
        }
        if (fstNum[i] < secNum[i]) {
            result = -1;
            break;
        }
    }

    delete[] fstNum;
    delete[] secNum;

    // Jeśli obie ujemne, odwróć wynik
    if (this->getIsNegative() && other.getIsNegative()) {
        result = -result;
    }

    return result;
}

bool CNumber::operator>(const CNumber &other) {
    return compare(other) > 0;
}

bool CNumber::operator<(const CNumber &other) {
    return compare(other) < 0;
}

bool CNumber::operator>=(const CNumber &other) {
    return compare(other) >= 0;
}


bool CNumber::operator<=(const CNumber &other) {
    return compare(other) <= 0;
}

int* CNumber::ExpandNumber(int newLength, const CNumber& numTable) const {
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