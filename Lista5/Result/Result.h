#ifndef TEP_RESULT_H
#define TEP_RESULT_H
#include <vector>

template <typename T, typename E>
class Result {
    public:
        Result(const T& value);
        Result(E* error);
        Result(std::vector<E*>& errors);
        Result(const Result<T, E>& other);
        ~Result();

        static Result<T, E> resultOk(const T& value);
        static Result<T, E> resultFail(E* error);
        static Result<T, E> resultFail(std::vector<E*>& errors);

        Result<T, E>& operator=(const Result<T, E>& other);

        bool isSuccess();

        void copy(const Result<T, E>& other);

        // T getValue();
        T getValue() const;

        // std::vector<E*>& getErrors();
        const std::vector<E*>& getErrors() const;

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
        Result();
        Result(E *error);
        Result(std::vector<E*>& errors);
        Result(const Result<void, E>& other);
        ~Result();

        static Result<void, E> resultOk();
        static Result<void, E> resultFail(E* error);
        static Result<void, E> resultFail(std::vector<E*>& errors);

        Result<void, E>& operator=(const Result<void, E>& other);

        bool isSuccess();

        void copy(const Result<void, E>& other);

        const std::vector<E*>& getErrors() const;

    private:
        std::vector<E*> errors;
};


// ============================================================================================
// ||                                Specjalizacja dla <TE*, TE>                             ||
// ============================================================================================
template <typename TE>
class Result<TE*, TE>
{
public:
    Result(const Result<TE*, TE>& other);
    ~Result();

    Result(TE* value);
    Result(std::vector<TE*>& errors);

    static Result<TE*, TE> resultOk(TE* value);
    static Result<TE*, TE> resultFail(TE* error);
    static Result<TE*, TE> resultFail(std::vector<TE*>& errors);

    Result<TE*, TE>& operator=(const Result<TE*, TE>& other);

    void copy(const Result<TE*, TE>& other);
    bool isSuccess();
    TE* getValue();
    std::vector<TE*>& getErrors();

private:
    TE* value;
    std::vector<TE*> errors;
};
#endif //TEP_RESULT_H