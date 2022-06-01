//
// Created by genas on 27.03.2022.
//

#ifndef LIB_SUDOKU_PRINTER_H
#define LIB_SUDOKU_PRINTER_H

#include <string>
#include <cassert>
#include <sstream>
#include <iterator>
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
    enum borderTypes {
        borderNone,
        borderBasic,
        borderLined,
        borderDouble
    };

    /**
     * Table number format for numbers in table
     */
    enum numberFormat {
        dec,
        hex
    };

private:
    /**
     * Method that returns number order     *
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
    static std::string repeat(const std::string &str, int n);

    /**
     * Positions for horizontal separator
     */
    enum HorizontalSeparator {
        SEPARATOR_TOP,
        SEPARATOR_MIDDLE,
        SEPARATOR_BOTTOM
    };

    /**
     * Print the number in the selected position in the table
     * @param stream
     *  - selected stream
     * @param maxWidth
     *  - max width for number
     * @param i
     *  - row
     * @param j
     *  - column
     * @param format
     *  - selected format (dec / hex)
     */
    virtual void printNumber(std::ostream &stream, int maxWidth, size_t i, size_t j,
                     numberFormat format, bool areZerosVisible) const;

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
    virtual void printHorizontalSeparator(std::ostream &stream, int maxWidth, int columns, HorizontalSeparator separator_pos) const;

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
    virtual void printHorizontalSeparator(std::ostream &stream, int maxWidth, int columns, HorizontalSeparator separator_pos,
                                  size_t borderType) const;

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
    static size_t getLinesTypeIndex(const SudokuPrinter::borderTypes &type);

    // Sudoku table to be printed
    SudokuTable table;

    // The format for numbers in table
    numberFormat format = numberFormat::dec;

    // Are zeros visible
    bool areZerosVisible = true;

public:
    //-------------
    // Constructors and destructor
    //-------------

    /**
     * Default constructor
     * @param table
     *  - sudoku table, that will be printed
     */
    explicit SudokuPrinter(const SudokuTable &table);

    /**
     * Default constructor with table lines type
     * @param table
     *  - sudoku table, that will be printed
     * @param type
     *  - table lines type
     * @param format
     *  - table numbers format
     */
    explicit SudokuPrinter(const SudokuTable &table, SudokuPrinter::borderTypes type, \
    SudokuPrinter::numberFormat format = SudokuPrinter::numberFormat::dec, bool areZerosVisible = true);

    /**
     * Copy constructor
     */
    SudokuPrinter(const SudokuPrinter &other);

    //-------------
    // Methods
    //-------------

    /**
     * Convert decimal to hexadecimal
     * @param number
     *  - number to convert
     * @return
     *  - hexadecimal in string
     */
    static std::string convertToHex(int number);

    /**
     * Static method that print sudoku table
     * @param stream
     *  - selected stream
     * @param table
     *  - sudoku table for print
     * @param type
     *  - selected border type
     */
    static void print(std::ostream &stream, const SudokuTable &table,
                      const borderTypes &type = borderTypes::borderNone, const numberFormat &format = numberFormat::dec,
                      bool areZerosVisible = true);

    /**
     * Method to print sudoku to stream
     * @param stream
     *  - selected stream
     */
    void print(std::ostream &stream) const;

    /**
     * Method to print sudoku to stream
     * @param stream
     *  - selected stream
     * @param type
     *  - selected border type
     */
    void print(std::ostream &stream, const borderTypes &type) const;

    /**
     * Method to print sudoku to stream
     * @param stream
     *  - selected stream
     * @param type
     *  - selected border type
     * @param format
     *  - selected format for table numbers
     */
    void print(std::ostream &stream, const borderTypes &type, const numberFormat &format,
               bool areZerosVisible) const;

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

    /**
     * Getter for number format for numbers in the table
     * @return
     *  - number format
     */
    SudokuPrinter::numberFormat getNumberFormat() const;

    /**
     * Getter for zeros visibility for numbers in the table
     * @return
     *  - zeros visibility
     */
    bool getZerosVisibility() const;

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
    void setTable(const SudokuTable &_table);

    /**
     * Set current printer number format
     * @param format
     *  - new number format for numbers in printer
     */
    void setNumberFormat(const SudokuPrinter::numberFormat &format);

    /**
     * Set current printer zeros visibility
     * @param state
     *  - new value for zeros visibility
     */
    void setZerosVisible(bool state);
};


#endif //LIB_SUDOKU_PRINTER_H
