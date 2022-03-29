//
// Created by genas on 24.03.2022.
//

#ifndef LIB_SUDOKUTABLE_H
#define LIB_SUDOKUTABLE_H

#include <iostream>
#include <algorithm>
#include <iterator>
#include <sstream>

/**
 * Container for sudoku, without logics
 */
class SudokuTable {
private:
    size_t size; // size
    int** table; // table

    // the number of numbers in width in one rectangle
    size_t numberInRect_w = 0;
    // the number of numbers in height in one rectangle
    size_t numberInRect_h = 0;

    /**
     * Function sets number of numbers in sudoku
     * in one rectangle
     */
    void init_numbers();

public:
    //-------------
    // Constructors and destructor
    //-------------

     /**
      * Default constructor
      *
      * @param size
     *   - new sudoku size
      */
    explicit SudokuTable(size_t size = 0);

    /**
     * Copy constructor
     */
    SudokuTable(const SudokuTable& other);

    /**
     * Destructor
     */
    ~SudokuTable();

    //-------------
    // Methods
    //-------------

    /**
     * Resize sudoku table
     *
     * @param size
     *  - new size
     */
    void resize(size_t size);

    //-------------
    // Getters
    //-------------

    // Getter for table size
    size_t getSize() const;
    // Getter for table
    int** getTable() const;

    // Getter for number of numbers in one rect in width
    size_t getNumberInRectInWidth() const;
    // Getter for number of numbers in one rect in height
    size_t getNumberInRectInHeight() const;

    //-------------
    // Operators
    //-------------

    // Indexers
    int operator()(size_t x, size_t y) const;
    int& operator()(size_t x, size_t y);

    // Input / output operators
    friend std::ostream& operator<< (std::ostream &out, const SudokuTable &table);
    friend std::istream& operator>> (std::istream &in, SudokuTable &table);
};


#endif //LIB_SUDOKUTABLE_H
