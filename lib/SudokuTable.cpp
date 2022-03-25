//
// Created by genas on 24.03.2022.
//

#include "SudokuTable.h"

//-------------
// Constructors and destructor
//-------------

/**
 * Default constructor
 *
 * @param size
 *  - new sudoku size
 */
SudokuTable::SudokuTable(size_t size)
{
    this->size = 0;
    this->table = new int*[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++)
        {
            this->table[i][j] = 0;
        }
    }
}

/**
 * Copy constructor
 */
SudokuTable::SudokuTable(const SudokuTable &other)
{
    this->size = other.size;
    this->table = new int*[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++)
        {
            this->table[i][j] = 0;
        }
    }
}

/**
 * Destructor
 */
SudokuTable::~SudokuTable()
{
    for (int i = 0; i < this->size; i++)
    {
        delete[] this->table[i];
    }
    delete[] table;
}

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
int SudokuTable::numberOrder(int number)
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
 * Resize sudoku table
 *
 * @param size
 *  - new size
 */
void SudokuTable::resize(size_t size)
{
    this->size = size;
    this->table = new int*[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++)
        {
            this->table[i][j] = 0;
        }
    }
}

/**
 * Print table with selected border type
 * @param type
 *  - border type
 */
void SudokuTable::print(const borderTypes& type)
{
    int cellSize = SudokuTable::numberOrder(static_cast<int>(this->size));

    if (type == borderTypes::borderNone)
    {
        for (size_t i = 0; i < this->size; i++)
        {
            for (size_t j = 0; j < this->size; j++)
            {
                std::cout << this->table[i][j];
                fill_n(std::ostream_iterator<char>(std::cout), \
                        cellSize - SudokuTable::numberOrder(this->table[i][j]), ' ');
                std::cout << ' ';
            }
            std::cout << std::endl;
        }
    }
}

//-------------
// Getters
//-------------

// Getter for table size
inline size_t SudokuTable::getSize() const
{
    return this->size;
}

// Getter for table
inline int** SudokuTable::getTable() const
{
    return this->table;
}

//-------------
// Operators
//-------------

// Indexers
int SudokuTable::operator()(size_t x, size_t y) const
{
    return this->table[x][y];
}

int& SudokuTable::operator()(size_t x, size_t y)
{
    return this->table[x][y];
}

// Input / output operators
std::ostream& operator<< (std::ostream &out, const SudokuTable &table)
{
    for (size_t i = 0; i < table.size; i++)
    {
        for (size_t j = 0; j < table.size; j++)
        {
            out << table(i, j) << ' ';
        }
        out << std::endl;
    }
    return out;
}

std::istream& operator>> (std::istream &in, SudokuTable &table)
{
    for (size_t i = 0; i < table.size; i++)
    {
        for (size_t j = 0; j < table.size; j++)
        {
            std::cin >> table(i, j);
        }
    }
    return in;
}