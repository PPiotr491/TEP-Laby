#ifndef TEP_TABLE_H
#define TEP_TABLE_H

#include <string>

class Table {

    const std::string DEFAULT_NAME = "DefaultTable";
    const static int DEFAULT_LENGTH = 1;

public:
    Table();
    Table(std::string name, int length);
    Table(const Table &tableToCopy);

    ~Table();
    Table *Clone();

    void setName(std::string newName);
    bool setLength(int newLength);

    std::string getName() {
        return name;
    }

    int getLength() {
        return length;
    }

private:
    std::string name;
    int length;
    int* array;
};


#endif //TEP_TABLE_H