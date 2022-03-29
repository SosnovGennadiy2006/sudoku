//
// Created by genas on 24.03.2022.
//

#include "SudokuTable.h"

//-------------
// Private methods
//-------------

/**
 * Function sets number of numbers in sudoku
 * in one rectangle
 */
void SudokuTable::init_numbers()
{
    if (this->size == 0)
        return;

    this->numberInRect_h = static_cast<int>(this->size);
    for (int i = 2; i * i <= this->size; i++)
    {
        if (this->size % i == 0)
        {
            this->numberInRect_h = i;
        }
    }
    this->numberInRect_w = static_cast<int>(this->size) / this->numberInRect_h;
    if (this->numberInRect_h == this->size)
        std::swap(this->numberInRect_h, this->numberInRect_w);
}

//-------------
// Constructors and destructor
//-------------

/**
 * Default constructor
 *
 * @param size
*   - new sudoku size
 * @param borderType
 *  - new sudoku border type
 */
SudokuTable::SudokuTable(size_t size)
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

    this->init_numbers();
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

    this->init_numbers();
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
 * Resize sudoku table
 *
 * @param size
 *  - new size
 */
void SudokuTable::resize(size_t _size)
{
    this->size = _size;
    this->table = new int*[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++)
        {
            this->table[i][j] = 0;
        }
    }

    this->init_numbers();
}

//-------------
// Getters
//-------------

// Getter for table size
size_t SudokuTable::getSize() const
{
    return this->size;
}

// Getter for table
int** SudokuTable::getTable() const
{
    return this->table;
}

// Getter for number of numbers in one rect in width
size_t SudokuTable::getNumberInRectInWidth() const
{
    return this->numberInRect_w;
}

// Getter for number of numbers in one rect in height
size_t SudokuTable::getNumberInRectInHeight() const
{
    return this->numberInRect_h;
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