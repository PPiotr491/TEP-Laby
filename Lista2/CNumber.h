#ifndef TEP_CNUMBER_H
#define TEP_CNUMBER_H


class CNumber {
public:
    CNumber();
    ~CNumber();

    CNumber& operator=(const int value);

    int * getNumTable() const {
        return numTable;
    }

    void setNumTable(int *newNumTable) {
        numTable = newNumTable;
    }

private:
    int* numTable;
};


#endif //TEP_CNUMBER_H