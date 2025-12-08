#ifndef TEP_RESULT_TPP
#define TEP_RESULT_TPP
#include <cstddef>
#include <vector>
#include "Result.h"

template <typename T, typename E>
Result<T, E>::Result(const T& value) {
    this->value = new T(value);
    std::vector<E*> errors;
    this->errors = errors;
}

template <typename T, typename E>
Result<T, E>::Result(E* error) {
    this->value = NULL;

    std::vector<E*> errors;
    errors.push_back(error);
    this->errors = errors;
}

template <typename T, typename E>
Result<T, E>::Result(std::vector<E*>& errors) {
    this->value = NULL;
    this->errors = errors;
}

template <typename T, typename E>
Result<T, E>::Result(const Result<T, E>& other) : value(NULL) {
    // errors jest automatycznie inicjalizowany jako pusty wektor
    copy(other);
}

template <typename T, typename E>
Result<T, E>::~Result() {
    if (value != NULL) {
        delete value;
    }

    std::vector<E*> errorsTemp = getErrors();
    for (size_t i = 0; i < errorsTemp.size(); i++) {
        E* err = errorsTemp[i];
        delete err;
    }
}

template <typename T, typename E>
Result<T, E> Result<T, E>::resultOk(const T& value) {
    return Result<T, E>(value);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::resultFail(E* error) {
    return Result<T, E>(error);
}

template <typename T, typename E>
Result<T, E> Result<T, E>::resultFail(std::vector<E*>& errors) {
    return Result<T, E>(errors);
}

template <typename T, typename E>
Result<T, E>& Result<T, E>::operator=(const Result<T, E>& other) {
    if (this != &other) {
        copy(other);
    }

    return *this;
}

template <typename T, typename E>
bool Result<T, E>::isSuccess() {
    if (getErrors().size() > 0) {
        return false;
    }

    return true;
}

template <typename T, typename E>
void Result<T, E>::copy(const Result<T, E>& other) {
    if (this->value != NULL) {
        delete this->value;
        this->value = NULL;
    }

    if (other.value != NULL) {
        this->value = new T(*other.value);
    }

    // Usuń stare błędy
    const std::vector<E*>& currentErrors = getErrors();
    if (!currentErrors.empty()) {
        for (std::size_t i = 0; i < currentErrors.size(); i++) {
            delete currentErrors[i];
        }
    }
    this->errors.clear();

    std::vector<E*> newErrors;
    const std::vector<E*>& otherErrors = other.getErrors();

    if (!otherErrors.empty()) {
        for (std::size_t i = 0; i < otherErrors.size(); i++) {
            newErrors.push_back(otherErrors[i]->clone());
        }
    }

    this->errors = newErrors;
}

// template <typename T, typename E>
// T Result<T, E>::getValue() {
//     if (this->value != NULL) {
//         return *this->value;
//     }
//     return T();
// }

template <typename T, typename E>
T Result<T, E>::getValue() const {
    if (this->value != NULL) {
        return *this->value;
    }
    return T();
}

// template <typename T, typename E>
// std::vector<E*>& Result<T, E>::getErrors() {
//     return this->errors;
// }

template <typename T, typename E>
const std::vector<E*>& Result<T, E>::getErrors() const {
    return this->errors;
}


// ============================================================================================
// ||                                Specjalizacja dla void                                  ||
// ============================================================================================
template <typename E>
Result<void, E>::Result() {
    std::vector<E*> errors;
    this->errors = errors;
}

template <typename E>
Result<void, E>::Result(E* error) {
    std::vector<E*> errors;
    errors.push_back(error);
    this->errors = errors;
}

template <typename E>
Result<void, E>::Result(std::vector<E*>& errors) {
    this->errors = errors;
}

template <typename E>
Result<void, E>::Result(const Result<void, E>& other) {
    copy(other);
}

template <typename E>
Result<void, E>::~Result() {
    std::vector<E*> errorsTemp = getErrors();
    for (size_t i = 0; i < errorsTemp.size(); i++) {
        E* err = errorsTemp[i];
        delete err;
    }
}

template <typename E>
Result<void, E> Result<void, E>::resultOk() {
    return Result<void, E>();
}

template <typename E>
Result<void, E> Result<void, E>::resultFail(E* error) {
    return Result<void, E>(error);
}

template <typename E>
Result<void, E> Result<void, E>::resultFail(std::vector<E*>& errors) {
    return Result<void, E>(errors);
}

template <typename E>
Result<void, E>& Result<void, E>::operator=(const Result<void, E>& other) {
    if (this != &other) {
        copy(other);
    }

    return *this;
}

template <typename E>
bool Result<void, E>::isSuccess() {
    if (getErrors().size() > 0) {
        return false;
    }

    return true;
}

template <typename E>
void Result<void, E>::copy(const Result<void, E>& other) {
    // Usuń stare błędy
    const std::vector<E*>& currentErrors = getErrors();
    for (std::size_t i = 0; i < currentErrors.size(); i++) {
        delete currentErrors[i];
    }
    this->errors.clear();

    std::vector<E*> newErrors;

    const std::vector<E*>& otherErrors = other.getErrors();
    if (!otherErrors.empty()) {
        for (std::size_t i = 0; i < otherErrors.size(); i++) {
            newErrors.push_back(otherErrors[i]->clone());
        }
    }

    this->errors = newErrors;
}

template <typename E>
const std::vector<E*>& Result<void, E>::getErrors() const {
    return this->errors;
}


#endif //TEP_RESULT_TPP
