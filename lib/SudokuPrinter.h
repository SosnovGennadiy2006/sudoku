//
// Created by genas on 27.03.2022.
//

#ifndef LIB_SUDOKUPRINTER_H
#define LIB_SUDOKUPRINTER_H

#include <string>
#include <cassert>
#include "SudokuTable.h"

/**
 * Class for printing sudoku table to std::ostream
 */
class SudokuPrinter {
public:
    //-------------
    // Enums
    //-------------

    /**
     * Table border types
     */
    enum borderTypes
    {
        borderNone,
        borderBasic,
        borderLined,
        borderDouble
    };

private:
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
     * Repeat std::string n times
     * @param str
     *  - repeatable string
     * @param n
     *  - number of repeating
     * @return
     *  a repeated string
     */
    static std::string repeat(const std::string& str, int n);

    /**
     * Positions for horizontal separator
     */
    enum HorizontalSeparator{
        SEPARATOR_TOP,
        SEPARATOR_MIDDLE,
        SEPARATOR_BOTTOM
    };

    /**
     * Print horizontal line between two rows
     * @param stream
     *  - selected stream
     * @param maxWidth
     *  - max columns width
     * @param columns
     *  - number of columns
     * @param separator_pos
     *  - position for separator in table
     */
    void printHorizontalSeparator(std::ostream& stream, int maxWidth, int columns, HorizontalSeparator separator_pos) const;

    /**
     * Print horizontal line between two rows
     * @param stream
     *  - selected stream
     * @param maxWidth
     *  - max columns width
     * @param columns
     *  - number of columns
     * @param separator_pos
     *  - position for separator in table
     * @param borderType
     *  - selected type for separator border lines
     */
    void printHorizontalSeparator(std::ostream& stream, int maxWidth, int columns, HorizontalSeparator separator_pos, size_t borderType) const;

    /**
     * All table lines types
     */
    const std::string tableLines[3][11] = {
            {"-", "|", "+", "+", "+", "+", "+", "+", "+", "+", "+"},
            {"━", "┃", "╋", "┫", "┣", "┳", "┻", "┏", "┓", "┗", "┛"},
            {"═", "║", "╬", "╣", "╠", "╦", "╩", "╔", "╗", "╚", "╝"}
    };

    // The index of current table lines
    size_t tableLinesType = 3;

    /**
     * Return index in table lines table for selected border type
     * @param type
     *  - selected border type
     * @return
     *  - index for selected border type in table
     */
    static size_t getLinesTypeIndex(const SudokuPrinter::borderTypes& type);

    SudokuTable table;
public:
    //-------------
    // Constructors and destructor
    //-------------

    /**
     * Default constructor
     * @param table
     *  - sudoku table, that will be printed
     */
    explicit SudokuPrinter(const SudokuTable& table);

    /**
     * Default constructor with table lines type
     * @param table
     *  - sudoku table, that will be printed
     * @param type
     *  - table lines type
     */
    SudokuPrinter(const SudokuTable& table, SudokuPrinter::borderTypes type);

    /**
     * Copy constructor
     */
    SudokuPrinter(const SudokuPrinter& other);

    //-------------
    // Methods
    //-------------

    /**
     * Method to print sudoku to stream
     * @param stream
     *  - selected stream
     */
    void print(std::ostream& stream);

    /**
     * Method to print sudoku to stream
     * @param stream
     *  - selected stream
     * @param type
     *  - selected border type
     */
    void print(std::ostream& stream, const borderTypes& type);

    //-------------
    // Getters
    //-------------

    /**
     * Getter for table
     * @return
     *  - printer table
     */
    SudokuTable getTable() const;

    /**
     * Getter for printer border type
     * @return
     *  - printer border type
     */
    SudokuPrinter::borderTypes getBorderType() const;

    //-------------
    // Setters
    //-------------

    /**
     * Set current printer border type
     * @param type
     *  - new table border type
     */
    void setBorderType(SudokuPrinter::borderTypes type);

    /**
     * Set current printer table
     * @param table
     *  - new printer table
     */
    void setTable(const SudokuTable& _table);
};


#endif //LIB_SUDOKUPRINTER_H
