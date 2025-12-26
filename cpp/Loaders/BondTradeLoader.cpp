#include "BondTradeLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <iostream>

using namespace std;

// Constructor and Destructor - Defining these fixes the "vtable" linker error
//BondTradeLoader::createTradeFromLine() : dataFile_("") {}
//BondTradeLoader::~BondTradeLoader() = default;

BondTrade* BondTradeLoader::createTradeFromLine(std::string line) {
    // 1. Skip completely empty lines
    if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
        return nullptr;
    }

    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;
    
    // Split the line by the separator (usually comma or tab)
    while (std::getline(ss, item, separator)) {
        // Trim whitespace and hidden carriage returns (\r)
        item.erase(0, item.find_first_not_of(" \t\r\n"));
        auto last = item.find_last_not_of(" \t\r\n");
        if (last != std::string::npos) item.erase(last + 1);
        
        items.push_back(item);
    }

    // 2. Filter Header/Footer/Malformed rows
    // If the first item is "Type" (header) or "END" (footer), we return nullptr to skip it
    if (items.empty() || items[0] == "Type" || items[0] == "END") {
        return nullptr;
    }

    // Ensure we have the minimum required columns (usually 7)
    if (items.size() < 7) {
        return nullptr; 
    }

    // 3. Extract and validate Trade ID
    std::string trade_id = items[6];
    if (trade_id.empty()) {
        return nullptr;
    }
    
    // 4. Safe Numeric Conversion (Prevents stod crash)
    double notional = 0.0;
    double rate = 0.0;
    try {
        notional = std::stod(items[4]);
        rate = std::stod(items[5]);
    } catch (...) {
        // If conversion fails (e.g. data is text), skip this line safely
        return nullptr; 
    }

    // 5. Construct the Trade object
    BondTrade* trade = new BondTrade(trade_id);
    trade->setTradeType(items[0]);
    trade->setNotional(notional);
    trade->setRate(rate);

    // 6. Parse the Date
    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    
    time_t tt = std::mktime(&tm);
    if (tt == -1) {
        // If date is malformed, use current time as a fallback
        trade->setTradeDate(std::chrono::system_clock::now());
    } else {
        auto timePoint = std::chrono::system_clock::from_time_t(tt);
        trade->setTradeDate(timePoint);
    }
    
    trade->setInstrument(items[2]);
    trade->setCounterparty(items[3]);
    
    return trade;
}

void BondTradeLoader::loadTradesFromFile(std::string filename, BondTradeList& tradeList) {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }
    
    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    while (std::getline(stream, line)) {
        // Create the trade pointer (might be nullptr if it's a header/footer)
        BondTrade* trade = createTradeFromLine(line);
        
        // Safety check: Only add if the pointer is valid
        if (trade != nullptr) {
            tradeList.add(trade);
        }
    }
}

std::vector<ITrade*> BondTradeLoader::loadTrades() {
    BondTradeList tradeList;
    loadTradesFromFile(dataFile_, tradeList);
    
    std::vector<ITrade*> result;
    for (size_t i = 0; i < tradeList.size(); ++i) {
        result.push_back(tradeList[i]);
    }
    return result;
}

std::string BondTradeLoader::getDataFile() const {
    return dataFile_;
}

void BondTradeLoader::setDataFile(const std::string& file) {
    dataFile_ = file;
}
