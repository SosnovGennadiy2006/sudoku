//
// Created by genas on 24.03.2022.
//

#ifndef LIB_SUDOKU_AREA_H
#define LIB_SUDOKU_AREA_H

#include <iostream>
#include "../Iterator/SudokuIterator.h"

/**
 * Container for sudoku elements such as row, column or square
 */
class SudokuArea {
public:
    // Iterator typedefs

    typedef SudokuIterator<int> iterator;
    typedef SudokuIterator<const int> const_iterator;

    typedef ReverseSudokuIterator<int> reverse_iterator;
    typedef ReverseSudokuIterator<const int> const_reverse_iterator;

private:
    /**
     * Area size
     */
    size_t size;

    /**
     * Area pointer
     */
    int* area;
public:
    //-------------
    // Constructors and destructor
    //-------------

    /**
     * Default constructor
     * @param size
     *  - new size
     */
    explicit SudokuArea(size_t size = 0);

    /**
     * Copy constructor
     */
    SudokuArea(const SudokuArea& other);

    /**
     * Destructor
     */
    ~SudokuArea();

    //-------------
    // Methods
    //-------------

    /**
     * Resize sudoku area
     * @param size
     *  - new size
     */
    void resize(size_t size);

    /**
     * Get the area element in the selected position
     * @param idx
     *  - element index
     * @return
     *  - element
     */
    int at(size_t idx) const;

    /**
     * Set the area element in the selected position
     * @param idx
     *  - element index
     * @param val
     *  - new value for element
     */
    void setAt(size_t idx, int val);

    //-------------
    // Getters
    //-------------

    // Getter for area size
    size_t getSize() const;

    //-------------
    // Operators
    //-------------

    // Indexers

    int operator()(size_t i) const;

    int &operator()(size_t i);

    // Input / output operators

    friend std::ostream &operator<<(std::ostream &out, const SudokuArea &table);

    friend std::istream &operator>>(std::istream &in, SudokuArea &table);

    //-------------
    // Iterators
    //-------------

    iterator begin(){return iterator(&this->area[0]);}
    iterator end(){return iterator(&this->area[this->size]);}

    const_iterator begin() const {return const_iterator(&this->area[0]);}
    const_iterator end() const {return const_iterator(&this->area[this->size]);}

    const_iterator cbegin() const {return const_iterator(&this->area[0]);}
    const_iterator cend() const {return const_iterator(&this->area[this->size]);}

    reverse_iterator rbegin(){return reverse_iterator(&this->area[this->size - 1]);}
    reverse_iterator rend(){return reverse_iterator(&this->area[-1]);}

    const_reverse_iterator rbegin() const {return const_reverse_iterator(&this->area[this->size - 1]);}
    const_reverse_iterator rend() const {return const_reverse_iterator(&this->area[-1]);}

    const_reverse_iterator crbegin() const {return const_reverse_iterator(&this->area[this->size - 1]);}
    const_reverse_iterator crend() const {return const_reverse_iterator(&this->area[-1]);}
};


#endif //LIB_SUDOKU_AREA_H
