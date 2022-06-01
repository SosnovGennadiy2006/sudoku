//
// Created by genas on 24.03.2022.
//

#ifndef LIB_SUDOKU_TABLE_H
#define LIB_SUDOKU_TABLE_H

#include <iostream>
#include "SudokuArea/SudokuArea.h"
#include "Iterator/SudokuIterator.h"

/**
 * Container for sudoku, without logics
 */
class SudokuTable {
public:
    // Iterator typedefs

    typedef SudokuIterator<SudokuArea> iterator;
    typedef SudokuIterator<const SudokuArea> const_iterator;

    typedef ReverseSudokuIterator<SudokuArea> reverse_iterator;
    typedef ReverseSudokuIterator<const SudokuArea> const_reverse_iterator;

    // Iterator types
    enum IteratorType
    {
        Row,
        Column,
        Square
    };

private:
    size_t size; // size

    int **table; // table
    SudokuArea *rows; // sudoku rows
    SudokuArea *columns; // sudoku columns
    SudokuArea *squares; // sudoku squares (rectangles)

    // the number of numbers in width in one rectangle
    size_t numberInRect_w = 0;
    // the number of numbers in height in one rectangle
    size_t numberInRect_h = 0;

    SudokuTable::IteratorType iteratorType;

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
     * @param size
     *  - new sudoku size
     */
    explicit SudokuTable(size_t size = 0);

    /**
     * Copy constructor
     */
    SudokuTable(const SudokuTable &other);

    /**
     * Destructor
     */
    ~SudokuTable();

    //-------------
    // Methods
    //-------------

    /**
     * Resize sudoku table
     * @param size
     *  - new size
     */
    void resize(size_t size);

    /**
     * Set the value for the selected element in sudoku
     * @param x
     *  - row for selected element
     * @param y
     *  - column for selected element
     * @param value
     *  - new value
     */
    void setValueAt(size_t x, size_t y, int value);

    /**
     * Method for entering sudoku
     * @param in
     *  - input stream
     */
    void enterSudoku(std::istream &in);

    /**
     * Static method for entering sudoku
     * @param in
     *  - input stream
     * @param _table
     *  - an instance of a sudoku table
     */
    static void enterSudoku(std::istream &in, SudokuTable& _table);

    //-------------
    // Getters
    //-------------

    // Getter for table size
    size_t getSize() const;

    // Getter for table
    int **getTable() const;

    // Getter for rows
    SudokuArea *getRows() const;

    // Getter for columns
    SudokuArea *getColumns() const;

    // Getter for squares (rectangle)
    SudokuArea *getSquares() const;

    /**
     * Getter for selected row
     * @param idx
     *  - index for selected row
     * @return
     *  - selected row
     */
    SudokuArea getRow(size_t idx) const;

    /**
     * Getter for selected column
     * @param idx
     *  - index for selected column
     * @return
     *  - selected column
     */
    SudokuArea getColumn(size_t idx) const;

    /**
     * Getter for selected square
     * @param idx
     *  - index for selected square
     * @return
     *  - selected square
     */
    SudokuArea getSquare(size_t idx) const;

    /**
     * Getter for selected row
     * @param idx
     *  - index for selected row
     * @return
     *  - link for selected row
     */
    SudokuArea& getRow(size_t idx);

    /**
     * Getter for selected column
     * @param idx
     *  - index for selected column
     * @return
     *  - link for selected column
     */
    SudokuArea& getColumn(size_t idx);

    /**
     * Getter for selected row
     * @param idx
     *  - index for selected row
     * @return
     *  - link for selected row
     */
    SudokuArea& getSquare(size_t idx);

    // Getter for number of numbers in one rect in width
    size_t getNumberInRectInWidth() const;

    // Getter for number of numbers in one rect in height
    size_t getNumberInRectInHeight() const;

    // Getter for table iterator type
    SudokuTable::IteratorType getIteratorType() const;

    //-------------
    // Setters
    //-------------

    /**
     * Setter for iterator type
     * @param new_type
     *  - new iterator type
     */
    void setIteratorType(SudokuTable::IteratorType new_type);

    //-------------
    // Operators
    //-------------

    // Indexers

    int operator()(size_t x, size_t y) const;

    // Input / output operators

    friend std::ostream &operator<<(std::ostream &out, const SudokuTable &table);

    friend std::istream &operator>>(std::istream &in, SudokuTable &table);

    //-------------
    // Iterators
    //-------------

    iterator begin();
    iterator end();

    const_iterator begin() const;
    const_iterator end() const;

    const_iterator cbegin() const;
    const_iterator cend() const;

    reverse_iterator rbegin();
    reverse_iterator rend();

    const_reverse_iterator rbegin() const;
    const_reverse_iterator rend() const;

    const_reverse_iterator crbegin() const;
    const_reverse_iterator crend() const;

    // iterator for rows

    iterator rows_begin();
    iterator rows_end();

    const_iterator rows_begin() const;
    const_iterator rows_end() const;

    const_iterator rows_cbegin() const;
    const_iterator rows_cend() const;

    reverse_iterator rows_rbegin();
    reverse_iterator rows_rend();

    const_reverse_iterator rows_rbegin() const;
    const_reverse_iterator rows_rend() const;

    const_reverse_iterator rows_crbegin() const;
    const_reverse_iterator rows_crend() const;

    // iterator for columns

    iterator columns_begin();
    iterator columns_end();

    const_iterator columns_begin() const;
    const_iterator columns_end() const;

    const_iterator columns_cbegin() const;
    const_iterator columns_cend() const;

    reverse_iterator columns_rbegin();
    reverse_iterator columns_rend();

    const_reverse_iterator columns_rbegin() const;
    const_reverse_iterator columns_rend() const;

    const_reverse_iterator columns_crbegin() const;
    const_reverse_iterator columns_crend() const;

    // iterator for squares

    iterator squares_begin();
    iterator squares_end();

    const_iterator squares_begin() const;
    const_iterator squares_end() const;

    const_iterator squares_cbegin() const;
    const_iterator squares_cend() const;

    reverse_iterator squares_rbegin();
    reverse_iterator squares_rend();

    const_reverse_iterator squares_rbegin() const;
    const_reverse_iterator squares_rend() const;

    const_reverse_iterator squares_crbegin() const;
    const_reverse_iterator squares_crend() const;
};


#endif //LIB_SUDOKU_TABLE_H
