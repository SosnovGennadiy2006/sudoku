//
// Created by genas on 27.03.2022.
//

#include "SudokuPrinter.h"

//-------------
// Private methods
//-------------

/**
 * Method that returns number order
 *
 * @param number
 *  - the number for which the order must be calculated
 * @return
 *  The order of the entered number
 */
int SudokuPrinter::numberOrder(int number) {
    if (number == 0)
        return 1;

    int order = 0;

    while (number) {
        number /= 10;

        ++order;
    }

    return order;
}

/**
 * Repeat std::string n times
 * @param str
 *  - repeatable string
 * @param n
 *  - number of repeating
 * @return
 *  a repeated string
 */
std::string SudokuPrinter::repeat(const std::string &str, int n) {
    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << str;
    return os.str();
}

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
void SudokuPrinter::printNumber(std::ostream &stream, int maxWidth, size_t i, size_t j,
                                numberFormat _format, bool _areZerosVisible) const {
    if (!_areZerosVisible && this->table(i, j) == 0)
    {
        fill_n(std::ostream_iterator<char>(stream), maxWidth, ' ');
        return;
    }
    if (_format == SudokuPrinter::numberFormat::dec) {
        stream << this->table(i, j);
        fill_n(std::ostream_iterator<char>(stream), \
                        maxWidth - SudokuPrinter::numberOrder(this->table(i, j)), ' ');
    } else {
        std::string number_hex = SudokuPrinter::convertToHex(this->table(i, j));
        stream << number_hex;
        fill_n(std::ostream_iterator<char>(stream), \
                        maxWidth - number_hex.size(), ' ');
    }
}

/**
 * Print horizontal line between two rows
 * @param stream
 *  - selected stream
 * @param maxWidth
 *  - max columns width
 * @param columns
 *  - number of columns
 * @param separator_t
 *  - table lines type for separator
 */
void SudokuPrinter::printHorizontalSeparator(std::ostream &stream, int maxWidth, int columns,
                                             HorizontalSeparator separator_pos) const {
    printHorizontalSeparator(stream, maxWidth, columns, separator_pos, this->getBorderType());
}

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
void SudokuPrinter::printHorizontalSeparator(std::ostream &stream, int maxWidth, int columns,
                                             HorizontalSeparator separator_pos, size_t borderType) const {
    for (int col = 0; col < columns; ++col) {
        switch (separator_pos) {
            case HorizontalSeparator::SEPARATOR_TOP: {
                stream << (col == 0 ? this->tableLines[borderType][7] : "");
                stream << SudokuPrinter::repeat(this->tableLines[borderType][0], maxWidth);
                stream << (col != columns - 1 ? this->tableLines[borderType][5] : this->tableLines[borderType][8]);
                stream << (col == columns - 1 ? "\n" : "");
                break;
            }
            case HorizontalSeparator::SEPARATOR_MIDDLE: {
                stream << (col == 0 ? this->tableLines[borderType][4] : "");
                stream << SudokuPrinter::repeat(this->tableLines[borderType][0], maxWidth);
                stream << (col != columns - 1 ? this->tableLines[borderType][2] : this->tableLines[borderType][3]);
                stream << (col == columns - 1 ? "\n" : "");
                break;
            }
            case HorizontalSeparator::SEPARATOR_BOTTOM: {
                stream << (col == 0 ? this->tableLines[borderType][9] : "");
                stream << SudokuPrinter::repeat(this->tableLines[borderType][0], maxWidth);
                stream
                        << (col != columns - 1 ? this->tableLines[borderType][6] : this->tableLines[borderType][10]);
                stream << (col == columns - 1 ? "\n" : "");
                break;
            }
        }
    }
}

/**
 * Return index in table lines table for selected border type
 * @param type
 *  - selected border type
 * @return
 */
size_t SudokuPrinter::getLinesTypeIndex(const SudokuPrinter::borderTypes &type) {
    switch (type) {
        case SudokuPrinter::borderTypes::borderNone: {
            return 3;
        }
        case SudokuPrinter::borderTypes::borderLined: {
            return 1;
        }
        case SudokuPrinter::borderTypes::borderBasic: {
            return 0;
        }
        case SudokuPrinter::borderTypes::borderDouble: {
            return 2;
        }
    }
    return 0;
}

//-------------
// Constructors and destructor
//-------------

/**
 * Default constructor
 * @param table
 *  - sudoku table, that will be printed
 */
SudokuPrinter::SudokuPrinter(const SudokuTable &table) {
    this->table = table;
}

/**
 * Default constructor with table lines type
 * @param table
 *  - sudoku table, that will be printed
 * @param type
 *  - table lines type
 * @param format
 *  - table numbers format
 */
SudokuPrinter::SudokuPrinter(const SudokuTable &table, SudokuPrinter::borderTypes type,
                             SudokuPrinter::numberFormat _format,
                             bool areZerosVisible) {
    this->table = table;
    this->tableLinesType = getLinesTypeIndex(type);
    this->format = _format;
    this->areZerosVisible = areZerosVisible;
}

/**
 * Copy constructor
 *
 * Doesn't copy border type
 */
SudokuPrinter::SudokuPrinter(const SudokuPrinter &other) {
    this->table = other.getTable();
}

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
std::string SudokuPrinter::convertToHex(int number) {
    if (number == 0)
        return "0";

    std::string ans;
    int rem;

    while (number > 0) {
        rem = number % 17;

        switch (rem) {
            case 0:
                ans += "0";
                break;
            case 1:
                ans += "1";
                break;
            case 2:
                ans += "2";
                break;
            case 3:
                ans += "3";
                break;
            case 4:
                ans += "4";
                break;
            case 5:
                ans += "5";
                break;
            case 6:
                ans += "6";
                break;
            case 7:
                ans += "7";
                break;
            case 8:
                ans += "8";
                break;
            case 9:
                ans += "9";
                break;
            case 10:
                ans += "A";
                break;
            case 11:
                ans += "B";
                break;
            case 12:
                ans += "C";
                break;
            case 13:
                ans += "D";
                break;
            case 14:
                ans += "E";
                break;
            case 15:
                ans += "F";
                break;
            case 16:
                ans += "G";
                break;
            default:
                break;
        }

        number /= 17;
    }

    return ans;
}

/**
 * Static method that print sudoku table
 * @param stream
 *  - selected stream
 * @param table
 *  - sudoku table for print
 * @param type
 *  - selected border type
 */
void SudokuPrinter::print(std::ostream &stream, const SudokuTable &table,
                          const borderTypes &type, const numberFormat &format, bool areZerosVisibility) {
    SudokuPrinter printer(table);
    printer.print(stream, type, format, areZerosVisibility);
}

/**
 * Method to print sudoku to stream
 * @param stream
 *  - selected stream
 */
void SudokuPrinter::print(std::ostream &stream) const {
    this->print(stream, this->getBorderType(), this->format, this->areZerosVisible);
}

/**
 * Method to print sudoku to stream
 * @param stream
 *  - selected stream
 * @param type
 *  - selected border type
 */
void SudokuPrinter::print(std::ostream &stream, const borderTypes &type) const {
    this->print(stream, type, this->format, this->areZerosVisible);
}

/**
 * Method to print sudoku to stream
 * @param stream
 *  - selected stream
 * @param type
 *  - selected border type
 */
void SudokuPrinter::print(std::ostream &stream, const SudokuPrinter::borderTypes &type,
                          const numberFormat &_format, bool _areZerosVisible) const {
    if (this->table.getSize() == 0)
        return;

    size_t linesTypeIndex = this->getLinesTypeIndex(type);
    size_t tableSize = this->table.getSize();
    size_t numberInRect_w = this->table.getNumberInRectInWidth();
    size_t numberInRect_h = this->table.getNumberInRectInHeight();
    int cellSize;

    if (_format == numberFormat::dec) {
        cellSize = SudokuPrinter::numberOrder(static_cast<int>(tableSize));
    } else {
        cellSize = static_cast<int>(SudokuPrinter::convertToHex(static_cast<int>(tableSize)).size());
    }

    if (type == borderTypes::borderNone) {
        for (size_t i = 0; i < tableSize; i++) {
            for (size_t j = 0; j < tableSize; j++) {
                this->printNumber(stream, cellSize, i, j, _format, this->areZerosVisible);
                stream << ' ';
            }
            stream << std::endl;
        }
    } else {
        int rectWidth = static_cast<int>(numberInRect_w * cellSize + numberInRect_w + 1);

        for (size_t i = 0; i < tableSize; i++) {
            if (i == 0) {
                this->printHorizontalSeparator(stream, rectWidth, static_cast<int>(numberInRect_h), \
                HorizontalSeparator::SEPARATOR_TOP, getLinesTypeIndex(type));
            }

            stream << this->tableLines[linesTypeIndex][1];
            for (size_t j = 0; j < tableSize; j++) {
                stream << ' ';
                this->printNumber(stream, cellSize, i, j, _format, this->areZerosVisible);
                if (j % numberInRect_w == numberInRect_w - 1)
                    stream << ' ' << this->tableLines[linesTypeIndex][1];
            }
            stream << std::endl;

            if (i == tableSize - 1) {
                this->printHorizontalSeparator(stream, rectWidth, static_cast<int>(numberInRect_h), \
                                               HorizontalSeparator::SEPARATOR_BOTTOM, getLinesTypeIndex(type));
            } else if (i % numberInRect_h == numberInRect_h - 1)
                this->printHorizontalSeparator(stream, rectWidth, static_cast<int>(numberInRect_h), \
                                               HorizontalSeparator::SEPARATOR_MIDDLE, getLinesTypeIndex(type));
        }
        stream << std::endl;
    }
}

//-------------
// Getters
//-------------

/**
 * Getter for table
 * @return
 *  - printer table
 */
SudokuTable SudokuPrinter::getTable() const {
    return this->table;
}

/**
 * Getter for printer border type
 * @return
 *  - printer border type
 */
SudokuPrinter::borderTypes SudokuPrinter::getBorderType() const {
    switch (this->tableLinesType) {
        case 3:
            return SudokuPrinter::borderTypes::borderNone;
        case 0:
            return SudokuPrinter::borderTypes::borderBasic;
        case 1:
            return SudokuPrinter::borderTypes::borderLined;
        case 2:
            return SudokuPrinter::borderTypes::borderDouble;
        default: {
            assert("Unknown error with border type!");
        }
    }
    return SudokuPrinter::borderTypes::borderNone;
}

/**
 * Getter for number format for numbers in the table
 * @return
 *  - number format
 */
SudokuPrinter::numberFormat SudokuPrinter::getNumberFormat() const {
    return this->format;
}

/**
     * Getter for zeros visibility for numbers in the table
     * @return
     *  - zeros visibility
     */
bool SudokuPrinter::getZerosVisibility() const {
    return this->areZerosVisible;
}

//-------------
// Setters
//-------------

/**
 * Set current printer border type
 * @param type
 *  - new table border type
 */
void SudokuPrinter::setBorderType(SudokuPrinter::borderTypes type) {
    this->tableLinesType = SudokuPrinter::getLinesTypeIndex(type);
}

/**
 * Set current printer table
 * @param table
 *  - new printer table
 */
void SudokuPrinter::setTable(const SudokuTable &_table) {
    this->table = _table;
}

/**
 * Set current printer number format
 * @param format
 *  - new number format for numbers in printer
 */
void SudokuPrinter::setNumberFormat(const SudokuPrinter::numberFormat &_format) {
    this->format = _format;
}

/**
 * Set current printer zeros visibility
 * @param state
 *  - new value for zeros visibility
 */
void SudokuPrinter::setZerosVisible(bool state) {
    this->areZerosVisible = state;
}
