#ifndef TEP_ERROR_H
#define TEP_ERROR_H
#include <string>


class Error {
public:
    Error();
    Error(const std::string& description);
    Error(const Error& other);
    ~Error();

    Error* clone() const;

    std::string toString() const {
        return getErrorDescription();
    }

    std::string getErrorDescription() const {
        return errorDescription;
    }

    void setErrorDescription(const std::string& errorDesc) {
        this->errorDescription = errorDesc;
    }

private:
    std::string errorDescription;
};

#endif //TEP_ERROR_H