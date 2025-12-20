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

    // 1. load and price BONDS
    SerialTradeLoader bondLoader;
    auto bondTrades = bondLoader.loadTrades(); // Loads from BondTrades.dat
    
    SerialPricer bondPricer;
    bondPricer.price(bondTrades, &results);
    
    // 2. load and price Fx
    FxSerialTradeLoader fxLoader;
    auto fxTrades = fxLoader.loadTrades();    // Loads from FxTrades.dat
    
    FxSerialPricer fxPricer;
    fxPricer.Fxprice(fxTrades, &results);
    
    std::cout << "Press any key to exit.." << std::endl;
    _getch();
    

    // Clean up the memory 
    for (auto& container : bondTrades) {
        for (ITrade* trade : container) delete trade;
    }
    for (auto& container : fxTrades) {
        for (FXITrade* trade : container) delete trade;
    }

    return 0;
}



/*

int main(int argc, char* argv[]) {
    SerialTradeLoader tradeLoader;
    auto allTrades = tradeLoader.loadTrades();
    
    ScalarResults results;
    SerialPricer pricer;
    pricer.price(allTrades, &results);
    
    ScreenResultPrinter screenPrinter;
    screenPrinter.printResults(results);
    
    std::cout << "Press any key to exit.." << std::endl;
    _getch();
    
    return 0;
}*/
