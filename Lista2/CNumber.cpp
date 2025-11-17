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

    // std::cout<<std::endl;
    // for (int i = 0; i < getLength(); i++) {
    //     std::cout<<getNumTable()[i];
    // }

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

    // Przypadek: (-a) + b = -(a - b)
    if (this->getIsNegative() && !other.getIsNegative()) {
        CNumber positiveThis(this->getLength(), this->getNumTable(), false);
        CNumber result = positiveThis.operator-(other);
        result.setIsNegative(true);
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

    // Usuń zera wiodące (ale zostaw przynajmniej jedną cyfrę)
    int firstNonZero = 0;
    while (firstNonZero < newLength - 1 && newNumber[firstNonZero] == 0) {
        firstNonZero++;
    }

    // Jeśli są zera wiodące, utwórz nową tablicę bez nich
    int finalLength = newLength - firstNonZero;
    int* finalNumber = new int[finalLength];
    for (int i = 0; i < finalLength; i++) {
        finalNumber[i] = newNumber[firstNonZero + i];
    }

    delete[] newNumber;

    CNumber result(finalLength, finalNumber, newIsNegative);
    delete[] finalNumber;

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

    // Usuń zera wiodące (ale zostaw przynajmniej jedną cyfrę)
    int firstNonZero = 0;
    while (firstNonZero < newLength - 1 && newNumber[firstNonZero] == 0) {
        firstNonZero++;
    }

    // Jeśli są zera wiodące, utwórz nową tablicę bez nich
    int finalLength = newLength - firstNonZero;
    int* finalNumber = new int[finalLength];
    for (int i = 0; i < finalLength; i++) {
        finalNumber[i] = newNumber[firstNonZero + i];
    }

    delete[] newNumber;

    CNumber result(finalLength, finalNumber, newIsNegative);
    delete[] finalNumber;

    return result;
}

CNumber CNumber::operator*(const CNumber &other) {
    bool newIsNegative = false;

    // oba dodatnie lub oba ujemne
    if ((!this->getIsNegative() && !other.getIsNegative()) || (this->getIsNegative() && other.getIsNegative())) {
        newIsNegative = false;
    } else {
        newIsNegative = true;
    }

    // Wynik mnożenia może mieć długość sumy długości obu liczb
    int resultLength = this->getLength() + other.getLength();
    int* newNumber = new int[resultLength]();

    // Mnożenie każdej cyfry z każdą
    for (int i = this->getLength() - 1; i >= 0; i--) {
        for (int j = other.getLength() - 1; j >= 0; j--) {
            int pos = i + j + 1; // Pozycja w tablicy wynikowej
            newNumber[pos] += this->getNumTable()[i] * other.getNumTable()[j];

            // Propaguj przeniesienie
            if (newNumber[pos] >= NUMERICAL_SYSTEM) {
                newNumber[pos - 1] += newNumber[pos] / NUMERICAL_SYSTEM;
                newNumber[pos] = newNumber[pos] % NUMERICAL_SYSTEM;
            }
        }
    }

    // Usuń zera wiodące (ale zostaw przynajmniej jedną cyfrę)
    int firstNonZero = 0;
    while (firstNonZero < resultLength - 1 && newNumber[firstNonZero] == 0) {
        firstNonZero++;
    }

    // Jeśli są zera wiodące, utwórz nową tablicę bez nich
    int finalLength = resultLength - firstNonZero;
    int* finalNumber = new int[finalLength];
    for (int i = 0; i < finalLength; i++) {
        finalNumber[i] = newNumber[firstNonZero + i];
    }

    delete[] newNumber;

    CNumber result(finalLength, finalNumber, newIsNegative);
    delete[] finalNumber;

    return result;
}

CNumber CNumber::operator/(const CNumber &other) {
    // Sprawdź dzielenie przez zero
    if (other.getLength() == 1 && other.getNumTable()[0] == 0) {
        std::cout << "Error: Division by zero!" << std::endl;
        CNumber zero;
        zero = 0;
        return zero;
    }

    // Utwórz pozytywne wersje liczb do obliczeń
    CNumber dividend(this->getLength(), this->getNumTable(), false);
    CNumber divisor(other.getLength(), other.getNumTable(), false);

    // Jeśli dzielna jest mniejsza od dzielnika, wynik to 0
    if (dividend < divisor) {
        CNumber zero;
        zero = 0;
        return zero;
    }

    // Wynik dzielenia
    int* newNumber = new int[this->getLength()];
    int resultLength = 0;

    // Reszta z dzielenia
    CNumber remainder;
    remainder = 0;

    // Dzielenie pisemne - przetwarzaj cyfrę po cyfrze
    for (int i = 0; i < dividend.getLength(); i++) {
        // Przesuń remainder w lewo (mnożenie przez 10) i dodaj następną cyfrę
        int* newRemainderTable = new int[remainder.getLength() + 1];
        for (int j = 0; j < remainder.getLength(); j++) {
            newRemainderTable[j] = remainder.getNumTable()[j];
        }
        newRemainderTable[remainder.getLength()] = dividend.getNumTable()[i];

        CNumber oldRemainder = remainder;
        remainder = CNumber(remainder.getLength() + 1, newRemainderTable, false);
        delete[] newRemainderTable;

        // Znajdź ile razy divisor mieści się w remainder
        int digitResult = 0;
        CNumber temp;
        temp = 0;

        int d = 0;
        while (temp <= remainder && d <= 9) {
            CNumber multiplier;
            multiplier = d;
            temp = divisor * multiplier;
            if (temp <= remainder) {
                digitResult = d;
                d++;
            }
        }

        // Zapisz cyfrę wyniku
        newNumber[resultLength++] = digitResult;

        // Oblicz nową resztę
        CNumber mult;
        mult = digitResult;
        CNumber subtrahend = divisor * mult;
        remainder = remainder - subtrahend;
    }

    // Jeśli nie ma cyfr w wyniku, zwróć 0
    if (resultLength == 0) {
        delete[] newNumber;
        CNumber zero;
        zero = 0;
        return zero;
    }

    // Usuń zera wiodące (ale zostaw przynajmniej jedną cyfrę)
    int firstNonZero = 0;
    while (firstNonZero < resultLength - 1 && newNumber[firstNonZero] == 0) {
        firstNonZero++;
    }

    // Jeśli są zera wiodące, utwórz nową tablicę bez nich
    int finalLength = resultLength - firstNonZero;
    int* finalDigits = new int[finalLength];
    for (int i = 0; i < finalLength; i++) {
        finalDigits[i] = newNumber[firstNonZero + i];
    }

    delete[] newNumber;

    // Określ znak wyniku
    bool newIsNegative = false;
    if ((!this->getIsNegative() && other.getIsNegative()) ||
        (this->getIsNegative() && !other.getIsNegative())) {
        newIsNegative = true;
    }

    CNumber result(finalLength, finalDigits, newIsNegative);
    delete[] finalDigits;

    return result;
}

CNumber CNumber::operator!() {
    CNumber resultCNum;
    CNumber temp;
    resultCNum = 1;

    for (int i = 0; i < getLength(); i++) {
        temp = getNumTable()[i];
        resultCNum = resultCNum * temp;
    }

    resultCNum.setIsNegative(this->getIsNegative());
    return resultCNum;
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