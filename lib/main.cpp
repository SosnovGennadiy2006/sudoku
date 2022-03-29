#include <iostream>
#include <sstream>
#include <Windows.h>
#include "SudokuTable.h"
#include "SudokuPrinter.h"

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
    table.resize(9);

    SudokuPrinter printer(table);

    // Print to console
    printer.print(std::cout, SudokuPrinter::borderTypes::borderDouble);

    std::system("pause");
}