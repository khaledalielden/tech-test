#include "FxTradeLoader.h"
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <ctime>
#include <iomanip>
#include <chrono>

#include <algorithm>

FxTrade* FxTradeLoader::createFxTradeFromLine(std::string line) {
    std::vector<std::string> items;
    std::stringstream ss(line);
    std::string item;

    while (std::getline(ss, item, fxseparator)) {
        // Remove any character that is not a standard printable ASCII character
        item.erase(std::remove_if(item.begin(), item.end(), [](unsigned char c) {
        return !std::isprint(c); }), item.end());

        items.push_back(item);
    }

    if (items.size() < 9) {
     //   throw std::runtime_error("Invalid line format"); 
       return nullptr;
    }

    // remove any trailing whitespace/newlines for tradeId
    std::string trade_id = items[8];
    size_t last = trade_id.find_last_not_of(" \n\r\t");
    if (last != std::string::npos) trade_id.erase(last + 1);
 
    FxTrade* trade = new FxTrade(trade_id);

    try {
        trade->setAmount(std::stod(items[4]));
        trade->setRate(std::stod(items[5]));
         } catch (...) {
        delete trade; // Clean up memory if conversion to double fails

        throw std::runtime_error("Invalid numeric data in line");
    }


    std::string trade_type = items[0];
    trade_type.erase(trade_type.find_last_not_of(" \n\r\t") + 1);
    trade->setTradeType(trade_type);

    std::string instrument = items[2] + items[3];
    trade->setInstrument(instrument); 

    trade->setCounterparty(items[7]);


    std::tm tm = {};
    std::istringstream dateStream(items[1]);
    dateStream >> std::get_time(&tm, "%Y-%m-%d");
    auto timePoint = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setTradeDate(timePoint);

    tm = {};
    std::istringstream dstream(items[6]);
    dstream >> std::get_time(&tm, "%Y-%m-%d");
    auto valuedate = std::chrono::system_clock::from_time_t(std::mktime(&tm));
    trade->setValueDate(valuedate);
    
  //  cout <<"here " << trade_id << "ll" << endl;  


//    cout << " space " << trade_type <<endl ;
    
  
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
    
    int lineCount = 0;
    std::string line;
    while (std::getline(stream, line)) {
        if (lineCount < 2) {
        } else { //cout << "line " << line << endl;
            tradeList.add(createFxTradeFromLine(line));
//cout << "Fxtest - " << createFxTradeFromLine(line)->getTradeId()<< endl;
        }
        lineCount++;
    }    
}

std::vector<FXITrade*> FxTradeLoader::loadTrades() {
    FXTradeList tradeList;

    loadFxTradesFromFile(dataFile_, tradeList);
    
    std::vector<FXITrade*> result;
  //  cout << "infun " << tradeList.size() << endl;
    for (size_t i = 0; i < tradeList.size(); ++i) {
      //  cout << "infun " << tradeList[i] << endl;
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



