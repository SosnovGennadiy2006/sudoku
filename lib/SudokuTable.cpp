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
void SudokuTable::init_numbers() {
    if (this->size == 0)
        return;

    this->numberInRect_h = static_cast<int>(this->size);
    for (int i = 2; i * i <= this->size; i++) {
        if (this->size % i == 0) {
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
SudokuTable::SudokuTable(size_t size) {
    this->size = size;
    this->table = new int *[this->size];
    for (size_t i = 0; i < this->size; i++) {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++) {
            this->table[i][j] = 0;
        }
    }

    this->rows = new SudokuArea[this->size];
    this->columns = new SudokuArea[this->size];
    this->squares = new SudokuArea[this->size];

    for (size_t i = 0; i < this->size; i++) {
        this->rows[i].resize(this->size);
        this->columns[i].resize(this->size);
        this->squares[i].resize(this->size);
    }

    this->init_numbers();

    this->iteratorType = SudokuTable::IteratorType::Row;
}

/**
 * Copy constructor
 */
SudokuTable::SudokuTable(const SudokuTable &other) {
    this->size = other.size;
    this->numberInRect_w = other.getNumberInRectInWidth();
    this->numberInRect_h = other.getNumberInRectInHeight();
    this->table = new int *[this->size];
    for (size_t i = 0; i < this->size; i++) {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++) {
            this->table[i][j] = other(i, j);
        }
    }

    this->rows = new SudokuArea[this->size];
    this->columns = new SudokuArea[this->size];
    this->squares = new SudokuArea[this->size];

    int h = static_cast<int>(this->numberInRect_h);
    int w = static_cast<int>(this->numberInRect_w);

    for (size_t i = 0; i < this->size; i++) {
        this->rows[i].resize(this->size);
        this->columns[i].resize(this->size);
        this->squares[i].resize(this->size);
        for (size_t j = 0; j < this->size; j++) {
            this->rows[i](j) = this->table[i][j];
            this->columns[i](j) = this->table[j][i];
            this->squares[i](j) = this->table[(i / h) * h + j / w][(i % h) * w + j % w];
        }
    }

    this->iteratorType = other.getIteratorType();
}

/**
 * Destructor
 */
SudokuTable::~SudokuTable() {
    for (int i = 0; i < this->size; i++) {
        delete[] this->table[i];
    }
    delete[] table;
    delete rows;
    delete columns;
    delete squares;
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
void SudokuTable::resize(size_t _size) {
    this->size = _size;
    this->table = new int *[this->size];
    for (size_t i = 0; i < this->size; i++) {
        this->table[i] = new int[this->size];

        for (size_t j = 0; j < this->size; j++) {
            this->table[i][j] = 0;
        }
    }

    this->rows = new SudokuArea[this->size];
    this->columns = new SudokuArea[this->size];
    this->squares = new SudokuArea[this->size];

    for (size_t i = 0; i < this->size; i++) {
        this->rows[i].resize(this->size);
        this->columns[i].resize(this->size);
        this->squares[i].resize(this->size);
    }

    this->init_numbers();
}

/**
 * Set the value for the selected element in sudoku
 * @param x
 *  - row for selected element
 * @param y
 *  - column for selected element
 * @param value
 *  - new value
 */
void SudokuTable::setValueAt(size_t x, size_t y, int value) {
    int h = static_cast<int>(this->numberInRect_h);
    int w = static_cast<int>(this->numberInRect_w);

    this->table[x][y] = value;
    this->rows[x](y) = value;
    this->columns[y](x) = value;
    this->squares[(x / h) * h + y / w]((x % h) * w + y % w) = value;
}

void SudokuTable::enterSudoku(std::istream &in) {
    for (size_t i = 0; i < this->size; i++) {
        for (size_t j = 0; j < this->size; j++) {
            std::cin >> this->table[i][j];
            this->setValueAt(i, j, this->table[i][j]);
        }
    }
}

void SudokuTable::enterSudoku(std::istream &in, SudokuTable &_table) {
    _table.enterSudoku(in);
}

//-------------
// Getters
//-------------

// Getter for table size
size_t SudokuTable::getSize() const {
    return this->size;
}

// Getter for table
int **SudokuTable::getTable() const {
    return this->table;
}

// Getter for rows
SudokuArea *SudokuTable::getRows() const {
    return this->rows;
}

// Getter for columns
SudokuArea *SudokuTable::getColumns() const {
    return this->columns;
}

// Getter for squares (rectangle)
SudokuArea *SudokuTable::getSquares() const {
    return this->squares;
}

/**
 * Getter for selected row
 * @param idx
 *  - index for selected row
 * @return
 *  - selected row
 */
SudokuArea SudokuTable::getRow(size_t idx) const {
    return this->rows[idx];
}

/**
 * Getter for selected column
 * @param idx
 *  - index for selected column
 * @return
 *  - selected column
 */
SudokuArea SudokuTable::getColumn(size_t idx) const {
    return this->columns[idx];
}

/**
 * Getter for selected square
 * @param idx
 *  - index for selected square
 * @return
 *  - selected square
 */
SudokuArea SudokuTable::getSquare(size_t idx) const {
    return this->squares[idx];
}

/**
 * Getter for selected row
 * @param idx
 *  - index for selected row
 * @return
 *  - link for selected row
 */
SudokuArea &SudokuTable::getRow(size_t idx) {
    return this->rows[idx];
}

/**
 * Getter for selected column
 * @param idx
 *  - index for selected column
 * @return
 *  - link for selected column
 */
SudokuArea &SudokuTable::getColumn(size_t idx) {
    return this->columns[idx];
}

/**
 * Getter for selected row
 * @param idx
 *  - index for selected row
 * @return
 *  - link for selected row
 */
SudokuArea &SudokuTable::getSquare(size_t idx) {
    return this->squares[idx];
}

// Getter for number of numbers in one rect in width
size_t SudokuTable::getNumberInRectInWidth() const {
    return this->numberInRect_w;
}

// Getter for number of numbers in one rect in height
size_t SudokuTable::getNumberInRectInHeight() const {
    return this->numberInRect_h;
}

// Getter for table iterator type
SudokuTable::IteratorType SudokuTable::getIteratorType() const
{
    return this->iteratorType;
}

//-------------
// Setters
//-------------

/**
 * Setter for iterator type
 * @param new_type
 *  - new iterator type
 */
void SudokuTable::setIteratorType(SudokuTable::IteratorType new_type)
{
    this->iteratorType = new_type;
}

//-------------
// Operators
//-------------

// Indexers

int SudokuTable::operator()(size_t x, size_t y) const {
    return this->table[x][y];
}

// Input / output operators

std::ostream &operator<<(std::ostream &out, const SudokuTable &table) {
    for (size_t i = 0; i < table.size; i++) {
        for (size_t j = 0; j < table.size; j++) {
            out << table(i, j) << ' ';
        }
        out << std::endl;
    }
    return out;
}

std::istream &operator>>(std::istream &in, SudokuTable &table)
{
    int val;
    for (size_t i = 0; i < table.getSize(); i++)
    {
        for (size_t j = 0; j < table.getSize(); j++)
        {
            in >> val;
            table.setValueAt(i, j, val);
        }
    }
    return in;
}

//-------------
// Iterators
//-------------

SudokuTable::iterator SudokuTable::begin()
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_begin();
        }
        case Column:
        {
            return this->columns_begin();
        }
        case Square:
        {
            return this->squares_begin();
        }
    }
}

SudokuTable::iterator SudokuTable::end()
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_end();
        }
        case Column:
        {
            return this->columns_end();
        }
        case Square:
        {
            return this->squares_end();
        }
    }
}

SudokuTable::const_iterator SudokuTable::begin() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_begin();
        }
        case Column:
        {
            return this->columns_begin();
        }
        case Square:
        {
            return this->squares_begin();
        }
    }
}

SudokuTable::const_iterator SudokuTable::end() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_end();
        }
        case Column:
        {
            return this->columns_end();
        }
        case Square:
        {
            return this->squares_end();
        }
    }
}

SudokuTable::const_iterator SudokuTable::cbegin() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_cbegin();
        }
        case Column:
        {
            return this->columns_cbegin();
        }
        case Square:
        {
            return this->squares_cbegin();
        }
    }
}

SudokuTable::const_iterator SudokuTable::cend() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_cend();
        }
        case Column:
        {
            return this->columns_cend();
        }
        case Square:
        {
            return this->squares_cend();
        }
    }
}

SudokuTable::reverse_iterator SudokuTable::rbegin()
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_rbegin();
        }
        case Column:
        {
            return this->columns_rbegin();
        }
        case Square:
        {
            return this->squares_rbegin();
        }
    }
}

SudokuTable::reverse_iterator SudokuTable::rend()
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_rend();
        }
        case Column:
        {
            return this->columns_rend();
        }
        case Square:
        {
            return this->squares_rend();
        }
    }
}

SudokuTable::const_reverse_iterator SudokuTable::rbegin() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_rbegin();
        }
        case Column:
        {
            return this->columns_rbegin();
        }
        case Square:
        {
            return this->squares_rbegin();
        }
    }
}

SudokuTable::const_reverse_iterator SudokuTable::rend() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_rend();
        }
        case Column:
        {
            return this->columns_rend();
        }
        case Square:
        {
            return this->squares_rend();
        }
    }
}

SudokuTable::const_reverse_iterator SudokuTable::crbegin() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_crbegin();
        }
        case Column:
        {
            return this->columns_crbegin();
        }
        case Square:
        {
            return this->squares_crbegin();
        }
    }
}

SudokuTable::const_reverse_iterator SudokuTable::crend() const
{
    switch(this->iteratorType)
    {
        case Row:
        {
            return this->rows_crend();
        }
        case Column:
        {
            return this->columns_crend();
        }
        case Square:
        {
            return this->squares_crend();
        }
    }
}

// iterator for rows

SudokuTable::iterator SudokuTable::rows_begin()
{
    return iterator(&this->rows[0]);
}

SudokuTable::iterator SudokuTable::rows_end()
{
    return iterator(&this->rows[this->size]);
}

SudokuTable::const_iterator SudokuTable::rows_begin() const
{
    return const_iterator(&this->rows[0]);
}

SudokuTable::const_iterator SudokuTable::rows_end() const
{
    return const_iterator(&this->rows[this->size]);
}

SudokuTable::const_iterator SudokuTable::rows_cbegin() const
{
    return const_iterator(&this->rows[0]);
}

SudokuTable::const_iterator SudokuTable::rows_cend() const
{
    return const_iterator(&this->rows[this->size]);
}

SudokuTable::reverse_iterator SudokuTable::rows_rbegin()
{
    return reverse_iterator(&this->rows[this->size - 1]);
}

SudokuTable::reverse_iterator SudokuTable::rows_rend()
{
    return reverse_iterator(&this->rows[-1]);
}

SudokuTable::const_reverse_iterator SudokuTable::rows_rbegin() const
{
    return const_reverse_iterator(&this->rows[this->size - 1]);
}

SudokuTable::const_reverse_iterator SudokuTable::rows_rend() const
{
    return const_reverse_iterator(&this->rows[-1]);
}

SudokuTable::const_reverse_iterator SudokuTable::rows_crbegin() const
{
    return const_reverse_iterator(&this->rows[this->size - 1]);
}

SudokuTable::const_reverse_iterator SudokuTable::rows_crend() const
{
    return const_reverse_iterator(&this->rows[-1]);
}

// iterator for columns

SudokuTable::iterator SudokuTable::columns_begin()
{
    return iterator(&this->columns[0]);
}

SudokuTable::iterator SudokuTable::columns_end()
{
    return iterator(&this->columns[this->size]);
}

SudokuTable::const_iterator SudokuTable::columns_begin() const
{
    return const_iterator(&this->columns[0]);
}

SudokuTable::const_iterator SudokuTable::columns_end() const
{
    return const_iterator(&this->columns[this->size]);
}

SudokuTable::const_iterator SudokuTable::columns_cbegin() const
{
    return const_iterator(&this->columns[0]);
}

SudokuTable::const_iterator SudokuTable::columns_cend() const
{
    return const_iterator(&this->columns[this->size]);
}

SudokuTable::reverse_iterator SudokuTable::columns_rbegin()
{
    return reverse_iterator(&this->columns[this->size - 1]);
}

SudokuTable::reverse_iterator SudokuTable::columns_rend()
{
    return reverse_iterator(&this->columns[-1]);
}

SudokuTable::const_reverse_iterator SudokuTable::columns_rbegin() const
{
    return const_reverse_iterator(&this->columns[this->size - 1]);
}

SudokuTable::const_reverse_iterator SudokuTable::columns_rend() const
{
    return const_reverse_iterator(&this->columns[-1]);
}

SudokuTable::const_reverse_iterator SudokuTable::columns_crbegin() const
{
    return const_reverse_iterator(&this->columns[this->size - 1]);
}

SudokuTable::const_reverse_iterator SudokuTable::columns_crend() const
{
    return const_reverse_iterator(&this->columns[-1]);
}

// iterator for squares

SudokuTable::iterator SudokuTable::squares_begin()
{
    return iterator(&this->squares[0]);
}

SudokuTable::iterator SudokuTable::squares_end()
{
    return iterator(&this->squares[this->size]);
}

SudokuTable::const_iterator SudokuTable::squares_begin() const
{
    return const_iterator(&this->squares[0]);
}

SudokuTable::const_iterator SudokuTable::squares_end() const
{
    return const_iterator(&this->squares[this->size]);
}

SudokuTable::const_iterator SudokuTable::squares_cbegin() const
{
    return const_iterator(&this->squares[0]);
}

SudokuTable::const_iterator SudokuTable::squares_cend() const
{
    return const_iterator(&this->squares[this->size]);
}

SudokuTable::reverse_iterator SudokuTable::squares_rbegin()
{
    return reverse_iterator(&this->squares[this->size - 1]);
}

SudokuTable::reverse_iterator SudokuTable::squares_rend()
{
    return reverse_iterator(&this->squares[-1]);
}

SudokuTable::const_reverse_iterator SudokuTable::squares_rbegin() const
{
    return const_reverse_iterator(&this->squares[this->size - 1]);
}

SudokuTable::const_reverse_iterator SudokuTable::squares_rend() const
{
    return const_reverse_iterator(&this->squares[-1]);
}

SudokuTable::const_reverse_iterator SudokuTable::squares_crbegin() const
{
    return const_reverse_iterator(&this->squares[this->size - 1]);
}

SudokuTable::const_reverse_iterator SudokuTable::squares_crend() const
{
    return const_reverse_iterator(&this->squares[-1]);
}
