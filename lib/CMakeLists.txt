cmake_minimum_required(VERSION 3.20)
project(lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(lib main.cpp
        SudokuTable.cpp
        SudokuTable.h
        SudokuArea/SudokuArea.cpp
        SudokuArea/SudokuArea.h
        Iterator/SudokuIterator.h SudokuPrinter.cpp SudokuPrinter.h)
