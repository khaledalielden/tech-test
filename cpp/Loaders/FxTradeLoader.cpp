#include "FxTradeLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <iostream>

using namespace std;

// 1. Constructor & Destructor - Mandatory to fix "undefined reference to vtable"
//FxTradeLoader::FxTradeLoader() : dataFile_("") {}
//FxTradeLoader::~FxTradeLoader() = default;

FxTrade* FxTradeLoader::createFxTradeFromLine(std::string line) {
    // Skip completely empty lines
    if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
        return nullptr;
    }

    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, fxseparator)) {
        // Remove non-printable characters (like the ¬ in the FX file)
        item.erase(std::remove_if(item.begin(), item.end(), [](unsigned char c) {
            return !std::isprint(c); 
        }), item.end());

        // Trim whitespace
        item.erase(0, item.find_first_not_of(" \t\r\n"));
        auto last_pos = item.find_last_not_of(" \t\r\n");
        if (last_pos != std::string::npos) item.erase(last_pos + 1);
        
        items.push_back(item);
    }

    // 2. Validate row content
    // Skip headers, footers, or malformed rows
    if (items.empty() || items[0] == "Type" || items[0] == "END" || items[0] == "TradeId") {
        return nullptr;
    }

    // Based on your code, FX trades require 9 columns
    if (items.size() < 9) {
        return nullptr;
    }

    // 3. Extract and clean TradeId (items[8])
    std::string trade_id = items[8];
    if (trade_id.empty()) return nullptr;

    FxTrade* trade = new FxTrade(trade_id);

    // 4. Safe numeric conversion
    try {
        trade->setAmount(std::stod(items[4]));
        trade->setRate(std::stod(items[5]));
    } catch (...) {
        delete trade; 
        return nullptr; // Return nullptr instead of throwing to keep the loader running
    }

    // 5. Set text fields
    trade->setTradeType(items[0]);
    
    // Combine currency pair (e.g., "EUR" + "USD")
    std::string instrument = items[2] + items[3];
    trade->setInstrument(instrument); 
    trade->setCounterparty(items[7]);

    // 6. Parse Dates (Trade Date and Value Date)
    auto parseDate = [](const std::string& dateStr) {
        std::tm tm = {};
        std::istringstream ds(dateStr);
        ds >> std::get_time(&tm, "%Y-%m-%d");
        time_t tt = std::mktime(&tm);
        if (tt == -1) return std::chrono::system_clock::now();
        return std::chrono::system_clock::from_time_t(tt);
    };

    trade->setTradeDate(parseDate(items[1]));
    trade->setValueDate(parseDate(items[6]));

    return trade;
}

void FxTradeLoader::loadFxTradesFromFile(std::string filename, FXTradeList& tradeList) {
    if (filename.empty()) {
        throw std::invalid_argument("Filename cannot be null");
    }

    std::ifstream stream(filename);
    if (!stream.is_open()) {
        throw std::runtime_error("Cannot open file: " + filename);
    }
    
    std::string line;
    while (std::getline(stream, line)) {
        FxTrade* trade = createFxTradeFromLine(line);
        
        // IMPORTANT: Only add to the list if the pointer is not null
        if (trade != nullptr) {
            tradeList.add(trade);
        }
    }    
}

std::vector<FXITrade*> FxTradeLoader::loadTrades() {
    FXTradeList tradeList;
    loadFxTradesFromFile(dataFile_, tradeList);
    
    std::vector<FXITrade*> result;
    for (size_t i = 0; i < tradeList.size(); ++i) {
        result.push_back(tradeList[i]);
    }
    return result;
}

std::string FxTradeLoader::getDataFile() const {
    return dataFile_;
}

void FxTradeLoader::setDataFile(const std::string& file) {
    dataFile_ = file;
}
