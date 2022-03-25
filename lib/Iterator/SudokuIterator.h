//
// Created by genas on 24.03.2022.
//

#ifndef LIB_SUDOKUITERATOR_H
#define LIB_SUDOKUITERATOR_H

#include <iterator> // For std::forward_iterator_tag
#include <cstddef>  // For std::ptrdiff_t

struct Iterator
{
    using iterator_category = std::random_access_iterator_tag;
    using difference_type   = std::ptrdiff_t;
    using value_type        = int;
    using pointer           = int*;  // or also value_type*
    using reference         = int&;  // or also value_type&

    Iterator(pointer ptr) : m_ptr(ptr) {}

    reference operator*() const { return *m_ptr; }
    pointer operator->() { return m_ptr; }

    // Prefix increment
    Iterator& operator++() { m_ptr++; return *this; }

    // Postfix increment
    Iterator operator++(int) { Iterator tmp = *this; ++(*this); return tmp; }

    friend bool operator== (const Iterator& a, const Iterator& b) { return a.m_ptr == b.m_ptr; };
    friend bool operator!= (const Iterator& a, const Iterator& b) { return a.m_ptr != b.m_ptr; };

private:

    pointer m_ptr;
};

#endif //LIB_SUDOKUITERATOR_H