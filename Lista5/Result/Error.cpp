#include "Error.h"

Error::Error() {
    setErrorDescription("Default error message");
}

Error::Error(const std::string& errorDesc) {
    setErrorDescription(errorDesc);
}

Error::Error(const Error& other) {
    setErrorDescription(other.getErrorDescription());
}

Error::~Error() {
}

Error* Error::clone() const {
    return new Error(errorDescription);
}