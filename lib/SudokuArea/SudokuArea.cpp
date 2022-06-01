//
// Created by genas on 24.03.2022.
//

#include "SudokuArea.h"

/**
 * Default constructor
 * @param size
 *  - new size
 */
SudokuArea::SudokuArea(size_t size)
{
    this->size = size;
    this->area = new int[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->area[i] = 0;
    }
}

/**
 * Copy constructor
 */
SudokuArea::SudokuArea(const SudokuArea &other)
{
    this->size = other.getSize();
    this->area = new int[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->area[i] = other(i);
    }
}

/**
 * Destructor
 */
SudokuArea::~SudokuArea()
{
    delete this->area;
}

//-------------
// Methods
//-------------

/**
 * Resize sudoku area
 * @param size
 *  - new size
 */
void SudokuArea::resize(size_t _size)
{
    this->size = _size;
    this->area = new int[this->size];
    for (size_t i = 0; i < this->size; i++)
    {
        this->area[i] = 0;
    }
}

/**
 * Get the area element in the selected position
 * @param i
 *  - element index
 * @return
 *  - element
 */
int SudokuArea::at(size_t idx) const
{
    return this->area[idx];
}

/**
 * Set the area element in the selected position
 * @param idx
 *  - element index
 * @param val
 *  - new value for element
 */
void SudokuArea::setAt(size_t idx, int val)
{
    this->area[idx] = val;
}

//-------------
// Getters
//-------------

// Getter for area size
size_t SudokuArea::getSize() const
{
    return this->size;
}

//-------------
// Operators
//-------------

// Indexers

int &SudokuArea::operator()(size_t i)
{
    return this->area[i];
}

int SudokuArea::operator()(size_t i) const
{
    return this->area[i];
}

// Input / output operators

std::ostream& operator<< (std::ostream &out, const SudokuArea &table)
{
    for (size_t i = 0; i < table.size; i++)
    {
        out << table(i);
    }
    return out;
}

std::istream& operator>> (std::istream &in, SudokuArea &table)
{
    for (size_t i = 0; i < table.size; i++)
    {
        in >> table(i);
    }
    return in;
}