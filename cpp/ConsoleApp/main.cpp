#include "../RiskSystem/SerialTradeLoader.h"
#include "../RiskSystem/FxSerialTradeLoader.h"
#include "../RiskSystem/StreamingTradeLoader.h"
#include "../Models/ScalarResults.h"
#include "../RiskSystem/SerialPricer.h"
#include "../RiskSystem/ParallelPricer.h"
#include "../RiskSystem/ScreenResultPrinter.h"
#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#include <fcntl.h>
#include <iostream>
int _getch() {
    struct termios oldt, newt;
    int ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
}
#endif

int main(int argc, char* argv[]) {
    ScalarResults results;

    // 1. Load and price BONDS
    SerialTradeLoader bondLoader;
    auto bondTrades = bondLoader.loadTrades(); 
//    std::cout << "DEBUG: bond Loader found " << bondTrades.size() << " groups." << std::endl; 

    SerialPricer bondPricer;
    bondPricer.price(bondTrades, &results);

    // 2. Load and price FX
    FxSerialTradeLoader fxLoader;
    auto fxTrades = fxLoader.loadTrades();    
//    std::cout << "DEBUG: FX Loader found " << fxTrades.size() << " groups." << std::endl; 


    FxSerialPricer fxPricer;
    fxPricer.Fxprice(fxTrades, &results);

    // --- ADDED THIS SECTION ---
    // 3. Print the results to the screen
    std::cout << "\n--- Calculation Results ---" << std::endl;
    ScreenResultPrinter screenPrinter;
    screenPrinter.printResults(results);
    // ---------------------------



    std::cout << "\nPress any key to exit.." << std::endl;
    _getch();

    // Clean up memory
    for (auto& container : bondTrades) {
        for (ITrade* trade : container) delete trade;
    }
    for (auto& container : fxTrades) {
        for (FXITrade* trade : container) delete trade;
    }

    return 0;
}


