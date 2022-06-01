#include <iostream>
#include <sstream>
#include <Windows.h>
#include "SudokuTable.h"
#include "SudokuPrinter.h"

//example sudoku:
//5 0 0 0 15 0 0 0 0 13 0 6 0 0 0 0
//16 0 0 4 0 0 1 0 8 0 3 12 2 6 9 7
//3 0 0 0 6 0 0 16 0 0 14 0 0 12 15 0
//14 0 6 0 9 0 0 0 0 5 0 15 0 11 0 3
//0 0 1 0 0 0 5 0 0 15 0 0 0 10 16 0
//7 0 0 3 0 0 0 0 14 10 0 0 0 0 0 0
//0 5 4 16 14 0 0 0 7 8 0 2 3 15 0 0
//9 10 15 0 3 8 0 0 6 0 5 0 14 0 1 2
//0 0 0 8 4 15 9 0 0 16 13 0 12 0 0 0
//13 14 0 0 0 0 2 0 3 9 0 5 11 0 0 16
//0 0 10 0 0 0 0 5 15 0 0 0 0 3 6 0
//4 3 0 0 7 16 0 6 0 0 0 0 13 5 10 15
//0 0 3 6 0 7 15 2 0 14 16 0 9 1 11 0
//12 9 11 5 8 0 16 0 1 3 0 10 0 0 13 0
//0 0 16 2 1 13 0 4 0 0 11 0 8 14 3 0
//0 4 14 13 0 0 3 9 12 0 0 8 0 0 0 10

class MBuf: public std::stringbuf {
public:
    int sync() override {
        fputs( str().c_str(), stdout );
        str( "" );
        return 0;
    }
};

int main() {
    SetConsoleOutputCP( CP_UTF8 );
    setvbuf( stdout, nullptr, _IONBF, 0 );
    MBuf buf;
    std::cout.rdbuf( &buf );

    // Main part

    SudokuTable table;
    table.resize(16);
    table.setIteratorType(SudokuTable::IteratorType::Square);
    std::cin >> table;

    SudokuPrinter printer(table);

    printer.setNumberFormat(SudokuPrinter::numberFormat::hex);
    printer.setZerosVisible(false);
    printer.setBorderType(SudokuPrinter::borderTypes::borderLined);

    printer.print(std::cout);

    std::cout << "Squares:" << std::endl;

    for (const auto& square : table)
    {
        for (const auto& elem : square)
        {
            std::cout << elem << ' ';
        }
        std::cout << std::endl;
    }

    std::system("pause");
}