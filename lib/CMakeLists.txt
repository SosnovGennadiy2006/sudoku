cmake_minimum_required(VERSION 3.20)
project(lib)

set(CMAKE_CXX_STANDARD 14)

add_executable(lib main.cpp
        SudokuTable.cpp
        SudokuTable.h
        SudokuAreas/SudokuArea.cpp
        SudokuAreas/SudokuArea.h
        Iterator/SudokuIterator.cpp
        Iterator/SudokuIterator.h)
