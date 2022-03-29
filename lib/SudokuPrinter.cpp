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
int SudokuPrinter::numberOrder(int number)
{
    if (number == 0) return 1;

    int order = 0;

    while(number){
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
std::string SudokuPrinter::repeat(const std::string& str, int n)
{
    std::ostringstream os;
    for (int i = 0; i < n; i++)
        os << str;
    return os.str();
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
void SudokuPrinter::printHorizontalSeparator(std::ostream& stream, int maxWidth, int columns, HorizontalSeparator separator_pos) const
{
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
void SudokuPrinter::printHorizontalSeparator(std::ostream& stream, int maxWidth, int columns, HorizontalSeparator separator_pos, size_t borderType) const
{
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
size_t SudokuPrinter::getLinesTypeIndex(const SudokuPrinter::borderTypes &type)
{
    switch (type) {
        case SudokuPrinter::borderTypes::borderNone:
        {
            return 3;
        }
        case SudokuPrinter::borderTypes::borderLined:
        {
            return 1;
        }
        case SudokuPrinter::borderTypes::borderBasic:
        {
            return 0;
        }
        case SudokuPrinter::borderTypes::borderDouble:
        {
            return 2;
        }
    }
}

//-------------
// Constructors and destructor
//-------------

/**
 * Default constructor
 * @param table
 *  - sudoku table, that will be printed
 */
SudokuPrinter::SudokuPrinter(const SudokuTable &table)
{
    this->table = table;
}

/**
 * Default constructor with table lines type
 * @param table
 *  - sudoku table, that will be printed
 * @param type
 *  - table lines type
 */
 SudokuPrinter::SudokuPrinter(const SudokuTable &table, SudokuPrinter::borderTypes type)
 {
     this->table = table;
 }

/**
 * Copy constructor
 *
 * Doesn't copy border type
 */
SudokuPrinter::SudokuPrinter(const SudokuPrinter& other)
{
    this->table = other.getTable();
}

//-------------
// Methods
//-------------

/**
 * Method to print sudoku to stream
 * @param stream
 *  - selected stream
 */
void SudokuPrinter::print(std::ostream& stream)
{
    this->print(stream, this->getBorderType());
}

/**
 * Method to print sudoku to stream
 * @param stream
 *  - selected stream
 * @param type
 *  - selected border type
 */
void SudokuPrinter::print(std::ostream& stream, const SudokuPrinter::borderTypes& type)
{
    if (this->table.getSize() == 0)
        return;

    size_t linesTypeIndex = this->getLinesTypeIndex(type);
    size_t tableSize = this->table.getSize();
    size_t numberInRect_w = this->table.getNumberInRectInWidth();
    size_t numberInRect_h = this->table.getNumberInRectInHeight();
    int cellSize = SudokuPrinter::numberOrder(static_cast<int>(tableSize));

    if (type == borderTypes::borderNone)
    {
        for (size_t i = 0; i < tableSize; i++)
        {
            for (size_t j = 0; j < tableSize; j++)
            {
                stream << this->table(i, j);
                fill_n(std::ostream_iterator<char>(stream), \
                        cellSize - SudokuPrinter::numberOrder(this->table(i, j)), ' ');
                stream << ' ';
            }
            stream << std::endl;
        }
    }else {
        int rectWidth = static_cast<int>(numberInRect_w * cellSize + numberInRect_w + 1);

        for (int i = 0; i < tableSize; i++) {
            if (i == 0) {
                this->printHorizontalSeparator(stream, rectWidth, static_cast<int>(numberInRect_h), \
                HorizontalSeparator::SEPARATOR_TOP, getLinesTypeIndex(type));
            }

            stream << this->tableLines[linesTypeIndex][1];
            for (int j = 0; j < tableSize; j++) {

                stream << ' ' << this->table(i, j);
                fill_n(std::ostream_iterator<char>(stream), \
                        cellSize - SudokuPrinter::numberOrder(this->table(i, j)), ' ');
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
SudokuTable SudokuPrinter::getTable() const
{
    return this->table;
}

/**
 * Getter for printer border type
 * @return
 *  - printer border type
 */
SudokuPrinter::borderTypes SudokuPrinter::getBorderType() const
{
    switch (this->tableLinesType)
    {
        case 3: return SudokuPrinter::borderTypes::borderNone;
        case 0: return SudokuPrinter::borderTypes::borderBasic;
        case 1: return SudokuPrinter::borderTypes::borderLined;
        case 2: return SudokuPrinter::borderTypes::borderDouble;
        default:
        {
            assert("Unknown error with border type!");
        }
    }
}

//-------------
// Setters
//-------------

/**
 * Set current printer border type
 * @param type
 *  - new table border type
 */
void SudokuPrinter::setBorderType(SudokuPrinter::borderTypes type)
{
    this->tableLinesType = SudokuPrinter::getLinesTypeIndex(type);
}

/**
 * Set current printer table
 * @param table
 *  - new printer table
 */
void SudokuPrinter::setTable(const SudokuTable& _table)
{
    this->table = _table;
}
