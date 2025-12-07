#ifndef TEP_RESULT_TPP
#define TEP_RESULT_TPP
#include <cstddef>
#include <vector>

template <typename T, typename E>
class Result {
    public:
        Result(const T& value) {
            this->value = new T(value);
            std::vector<E*> errors;
            this->errors = errors;
        }

        Result(E* error) {
            this->value = NULL;

            std::vector<E*> errors;
            errors.push_back(error);
            this->errors = errors;
        }

        Result(std::vector<E*>& errors) {
            this->value = NULL;
            this->errors = errors;
        }

        Result(const Result<T, E>& other) : value(NULL) {
            // errors jest automatycznie inicjalizowany jako pusty wektor
            copy(other);
        }

        ~Result() {
            if (value != NULL) {
                delete value;
            }

            std::vector<E*> errorsTemp = getErrors();
            for (size_t i = 0; i < errorsTemp.size(); i++) {
                E* err = errorsTemp[i];
                delete err;
            }
        }

        static Result<T, E> resultOk(const T& value) {
            return Result<T, E>(value);
        }

        static Result<T, E> resultFail(E* error) {
            return Result<T, E>(error);
        }

        static Result<T, E> resultFail(std::vector<E*>& errors) {
            return Result<T, E>(errors);
        }

        Result<T, E>& operator=(const Result<T, E>& other) {
            if (this != &other) {
                copy(other);
            }

            return *this;
        }

        bool isSuccess() {
            if (getErrors().size() > 0) {
                return false;
            }

            return true;
        }

        void copy(const Result<T, E>& other) {
            if (this->value != NULL) {
                delete this->value;
                this->value = NULL;
            }

            if (other.value != NULL) {
                this->value = new T(*other.value);
            }

            // Usuń stare błędy
            std::vector<E*>& currentErrors = getErrors();
            if (!currentErrors.empty()) {
                for (std::size_t i = 0; i < currentErrors.size(); i++) {
                    delete currentErrors[i];
                }
            }
            this->errors.clear();

            std::vector<E*> newErrors;
            const std::vector<E*>& otherErrors = other.errors;

            if (!otherErrors.empty()) {
                for (std::size_t i = 0; i < otherErrors.size(); i++) {
                    newErrors.push_back(otherErrors[i]->clone());
                }
            }

            this->errors = newErrors;
        }

        T getValue() {
            if (this->value != NULL) {
                return *this->value;
            }
            return T();
        }

        std::vector<E*>& getErrors() {
            return this->errors;
        }

    private:
        T *value;
        std::vector<E*> errors;
};



// ============================================================================================
// ||                                Specjalizacja dla void                                  ||
// ============================================================================================
template <typename E>
class Result<void, E> {
    public:
        Result() {
            std::vector<E*> errors;
            this->errors = errors;
        }

        Result(E *error) {
            std::vector<E*> errors;
            errors.push_back(error);
            this->errors = errors;
        }

        Result(std::vector<E*>& errors) {
            this->errors = errors;
        }

        Result(const Result<void, E>& other) {
            copy(other);
        }

        ~Result() {
            std::vector<E*> errorsTemp = getErrors();
            for (size_t i = 0; i < errorsTemp.size(); i++) {
                E* err = errorsTemp[i];
                delete err;
            }
        }

        static Result<void, E> resultOk() {
            return Result<void, E>();
        }

        static Result<void, E> resultFail(E* error) {
            return Result<void, E>(error);
        }

        static Result<void, E> resultFail(std::vector<E*>& errors) {
            return Result<void, E>(errors);
        }

        Result<void, E>& operator=(const Result<void, E>& other) {
            if (this != &other) {
                copy(other);
            }

            return *this;
        }

        bool isSuccess() {
            if (getErrors().size() > 0) {
                return false;
            }

            return true;
        }

        void copy(const Result<void, E>& other) {
            // Usuń stare błędy
            std::vector<E*>& currentErrors = getErrors();
            for (std::size_t i = 0; i < currentErrors.size(); i++) {
                delete currentErrors[i];
            }
            this->errors.clear();

            std::vector<E*> newErrors;

            const std::vector<E*>& otherErrors = other.errors;
            if (!otherErrors.empty()) {
                for (std::size_t i = 0; i < otherErrors.size(); i++) {
                    newErrors.push_back(otherErrors[i]->clone());
                }
            }

            this->errors = newErrors;
        }

        std::vector<E*>& getErrors() {
            return this->errors;
        }

    private:
        std::vector<E*> errors;
};
#endif //TEP_RESULT_TPP
