// #include "ScreenResultPrinter.h"
// #include <iostream>
/*
void ScreenResultPrinter::printResults(ScalarResults& results) {
    for (const auto& result : results) {
        // Write code here to print out the results such that we have:
        // TradeID : Result : Error
        // If there is no result then the output should be:
        // TradeID : Error
        // If there is no error the output should be:
        // TradeID : Result
    }
}*/


#include "ScreenResultPrinter.h"
#include <iostream>
#include <iomanip>

void ScreenResultPrinter::printResults(ScalarResults& results) {
    bool foundAny = false;
    
    // The range-based for loop uses begin() and end()
    for (const auto& result : results) {
        if (result.getTradeId().empty()) continue;

        foundAny = true;
        std::cout << std::left << std::setw(15) << result.getTradeId() << " : ";

        const auto& price = result.getResult();
        const auto& error = result.getError();

        if (price.has_value() && error.has_value()) {
            std::cout << std::fixed << std::setprecision(2) << price.value() 
                      << " [Error: " << error.value() << "]";
        } 
        else if (price.has_value()) {
            std::cout << std::fixed << std::setprecision(2) << price.value();
        } 
        else if (error.has_value()) {
            std::cout << "ERROR: " << error.value();
        }

        std::cout << std::endl;
    }

    if (!foundAny) {
        std::cout << "No valid results or errors found to display." << std::endl;
    }
}




