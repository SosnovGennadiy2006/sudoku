//
// Created by genas on 21.05.2022.
//

#ifndef LIB_SUDOKU_ITERATOR_H
#define LIB_SUDOKU_ITERATOR_H


/**
 * Iterator for sudoku
 */
template<typename dataType>
class SudokuIterator {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = dataType;
    using difference_type = std::ptrdiff_t;
    using pointer = dataType *;
    using reference = dataType &;

public:
    explicit SudokuIterator(dataType *ptr = nullptr) { m_ptr = ptr; }

    SudokuIterator(const SudokuIterator<dataType> &rawIterator) { m_ptr = rawIterator.getPtr(); }

    ~SudokuIterator() = default;

    virtual SudokuIterator<dataType> &operator=(const SudokuIterator<dataType> &rawIterator) {
        m_ptr = rawIterator.getPtr();
        return (*this);
    }

    virtual SudokuIterator<dataType> &operator=(dataType *ptr) {
        m_ptr = ptr;
        return (*this);
    }

    explicit operator bool() const {
        if (m_ptr)
            return true;
        else
            return false;
    }

    bool operator==(const SudokuIterator<dataType> &rawIterator) const { return (m_ptr == rawIterator.getConstPtr()); }

    bool operator!=(const SudokuIterator<dataType> &rawIterator) const { return (m_ptr != rawIterator.getConstPtr()); }

    virtual SudokuIterator<dataType> &operator+=(const difference_type &movement) {
        m_ptr += movement;
        return (*this);
    }

    virtual SudokuIterator<dataType> &operator-=(const difference_type &movement) {
        m_ptr -= movement;
        return (*this);
    }

    virtual SudokuIterator<dataType> &operator++() {
        ++m_ptr;
        return (*this);
    }

    virtual SudokuIterator<dataType> &operator--() {
        --m_ptr;
        return (*this);
    }

    SudokuIterator<dataType> operator++(int) {
        auto temp(*this);
        ++m_ptr;
        return temp;
    }

    SudokuIterator<dataType> operator--(int) {
        auto temp(*this);
        --m_ptr;
        return temp;
    }

    SudokuIterator<dataType> operator+(const difference_type &movement) {
        auto oldPtr = m_ptr;
        m_ptr += movement;
        auto temp(*this);
        m_ptr = oldPtr;
        return temp;
    }

    SudokuIterator<dataType> operator-(const difference_type &movement) {
        auto oldPtr = m_ptr;
        m_ptr -= movement;
        auto temp(*this);
        m_ptr = oldPtr;
        return temp;
    }

    difference_type operator-(const SudokuIterator<dataType> &rawIterator) {
        return std::distance(rawIterator.getPtr(), this->getPtr());
    }

    dataType &operator*() { return *m_ptr; }

    const dataType &operator*() const { return *m_ptr; }

    dataType *operator->() { return m_ptr; }

    dataType *getPtr() const { return m_ptr; }

    const dataType *getConstPtr() const { return m_ptr; }

protected:
    dataType *m_ptr;
};

/**
 * Reverse iterator for sudoku
 */
template<typename dataType>
class ReverseSudokuIterator : public SudokuIterator<dataType> {
public:
    using iterator_category = std::random_access_iterator_tag;
    using value_type = dataType;
    using difference_type = std::ptrdiff_t;
    using pointer = dataType *;
    using reference = dataType &;

public:
    explicit ReverseSudokuIterator(dataType *ptr = nullptr) : SudokuIterator<dataType>(ptr) {}

    explicit ReverseSudokuIterator(const SudokuIterator<dataType> &rawIterator) { this->m_ptr = rawIterator.getPtr(); }

    ReverseSudokuIterator(
            const ReverseSudokuIterator<dataType> &rawReverseIterator) { this->m_ptr = rawReverseIterator.getPtr(); }

    ~ReverseSudokuIterator() = default;

    ReverseSudokuIterator<dataType> &operator=(const ReverseSudokuIterator<dataType> &rawReverseIterator) = default;

    ReverseSudokuIterator<dataType> &operator=(const SudokuIterator<dataType> &rawIterator) {
        this->m_ptr = rawIterator.getPtr();
        return (*this);
    }

    ReverseSudokuIterator<dataType> &operator=(dataType *ptr) {
        this->m_ptr = ptr;
        return (*this);
    }

    ReverseSudokuIterator<dataType> &operator+=(const difference_type &movement) {
        this->m_ptr -= movement;
        return (*this);
    }

    ReverseSudokuIterator<dataType> &operator-=(const difference_type &movement) {
        this->m_ptr += movement;
        return (*this);
    }

    ReverseSudokuIterator<dataType> &operator++() {
        --this->m_ptr;
        return (*this);
    }

    ReverseSudokuIterator<dataType> &operator--() {
        ++this->m_ptr;
        return (*this);
    }

    ReverseSudokuIterator<dataType> operator++(int) {
        ReverseSudokuIterator<dataType> temp(*this);
        --this->m_ptr;
        return temp;
    }

    ReverseSudokuIterator<dataType> operator--(int) {
        ReverseSudokuIterator<dataType> temp(*this);
        ++this->m_ptr;
        return temp;
    }

    ReverseSudokuIterator<dataType> operator+(const int &movement) {
        auto oldPtr = this->m_ptr;
        this->m_ptr -= movement;
        auto temp(*this);
        this->m_ptr = oldPtr;
        return temp;
    }

    ReverseSudokuIterator<dataType> operator-(const int &movement) {
        auto oldPtr = this->m_ptr;
        this->m_ptr += movement;
        auto temp(*this);
        this->m_ptr = oldPtr;
        return temp;
    }

    difference_type operator-(const ReverseSudokuIterator<dataType> &rawReverseIterator) {
        return std::distance(this->getPtr(), rawReverseIterator.getPtr());
    }

    SudokuIterator<dataType> base() {
        SudokuIterator<dataType> forwardIterator(this->m_ptr);
        ++forwardIterator;
        return forwardIterator;
    }
};

#endif //LIB_SUDOKU_ITERATOR_H
