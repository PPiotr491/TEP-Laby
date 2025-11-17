#ifndef TEP_CNUMBER_H
#define TEP_CNUMBER_H
#include <string>


class CNumber {
    const static int NUMERICAL_SYSTEM = 10;
    const static int MAX_NUMBER_VALUE = NUMERICAL_SYSTEM - 1;
    const static int DEFAULT_SIZE = 1;
public:
    CNumber();

    CNumber(int length, int *numTable, bool isNegative);

    CNumber(int length, int *numTable);

    ~CNumber();
    CNumber(const CNumber &toCopy);

    CNumber& operator=(const int value);
    CNumber& operator=(const CNumber &other);

    CNumber operator+(const CNumber &other);
    CNumber operator-(const CNumber &other);
    CNumber operator*(const CNumber &numToAdd);
    CNumber operator/(const CNumber &other);

    CNumber operator!();

    bool operator>(const CNumber &other);

    bool operator<=(const CNumber &other);

    bool operator<(const CNumber &other);

    bool operator>=(const CNumber &other);

    int *ExpandNumber(int newLength, const CNumber &numTable) const;

    std::string toString() const;

    int* getNumTable() const {
        return numTable;
    }

    void setNumTable(int *newNumTable) {
        this->numTable = newNumTable;
    }

    int getLength() const {
        return length;
    }

    void setLength(const int newLength) {
        this->length = newLength;
    }

    bool getIsNegative() const {
        return isNegative;
    }

    void setIsNegative(bool isNegative) {
        this->isNegative = isNegative;
    }

private:
    int length;
    int* numTable;
    bool isNegative;

    int compare(const CNumber &other) const;
};


#endif //TEP_CNUMBER_H