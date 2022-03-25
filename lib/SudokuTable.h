//
// Created by genas on 24.03.2022.
//

#ifndef LIB_SUDOKUTABLE_H
#define LIB_SUDOKUTABLE_H

#include <iostream>
#include <algorithm>
#include <iterator>

//-------------
// Enums
//-------------

enum borderTypes
{
    borderNone,
    borderOrdinary,
    borderDouble
};

enum HorizontalSeparator{
    SEPARATOR_TOP,
    SEPARATOR_MIDDLE,
    SEPARATOR_BOTTOM
};

// Container for sudoku, without logics
class SudokuTable {
private:
    size_t size; // size
    int** table; // table

    // Table Style variables
    std::string style_line_horizontal;
    std::string style_line_vertical;
    std::string style_line_cross;
    std::string style_t_intersect_right;
    std::string style_t_intersect_left;
    std::string style_t_intersect_top;
    std::string style_t_intersect_bottom;
    std::string style_edge_top_left;
    std::string style_edge_top_right;
    std::string style_edge_bottom_left;
    std::string style_edge_bottom_right;

    void printHorizontalSeparator(int maxWidth, const HorizontalSeparator& separator) const;
public:
    //-------------
    // Constructors and destructor
    //-------------

    /**
     * Default constructor
     *
     * @param size
     *  - new sudoku size
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
     * Method that returns number order
     *
     * @param number
     *  - the number for which the order must be calculated
     * @return
     *  The order of the entered number
     */
    static int numberOrder(int number);

    /**
     * Resize sudoku table
     *
     * @param size
     *  - new size
     */
    void resize(size_t size);

    /**
     * Print table with selected border type
     * @param type
     *  - border type
     */
    void print(const borderTypes& type = borderTypes::borderNone);

    //-------------
    // Getters
    //-------------

    // Getter for table size
    inline size_t getSize() const;
    // Getter for table
    inline int** getTable() const;

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
