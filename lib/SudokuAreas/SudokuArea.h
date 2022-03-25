//
// Created by genas on 24.03.2022.
//

#ifndef LIB_SUDOKUAREA_H
#define LIB_SUDOKUAREA_H

#include <iostream>

class SudokuArea {
private:
    size_t size;
    int* area;
public:
    //-------------
    // Constructors and destructor
    //-------------
    SudokuArea(size_t size = 0);
    SudokuArea(const SudokuArea& other);
    ~SudokuArea();
};


#endif //LIB_SUDOKUAREA_H
