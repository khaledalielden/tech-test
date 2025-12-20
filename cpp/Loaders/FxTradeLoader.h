#ifndef FXTRADELOADER_H
#define FXTRADELOADER_H

#include "FXITradeLoader.h"
#include "../Models/FxTrade.h"
#include "../Models/FXTradeList.h"
#include <string>
#include <vector>
#include <memory>


class FxTradeLoader : public FXITradeLoader {
private:
  //  static const std::string fxseparator = "¬";
    static constexpr char fxseparator = char(172);  // Use its char value ASCII/ISO-8859-1 value for '¬'.


    std::string dataFile_;
    
    FxTrade* createFxTradeFromLine(std::string line);
    void loadFxTradesFromFile(std::string filename, FXTradeList& tradeList);
    

public:
    // NOTE: These methods are only here to allow the solution to compile prior to the test being completed.
    std::vector<FXITrade*> loadTrades() override;
    std::string getDataFile() const override;
    void setDataFile(const std::string& file) override;
};



#endif // FXTRADELOADER_H

