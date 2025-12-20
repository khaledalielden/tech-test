#ifndef BONDTRADE_H
#define BONDTRADE_H

#include "BaseTrade.h"
#include <stdexcept>

class BondTrade : public BaseTrade {
public:
    static constexpr const char* GovBondTradeType = "GovBond";
    static constexpr const char* CorpBondTradeType = "CorpBond";
    
    BondTrade(const std::string& tradeId) {

     //   std::string tradeType_ = tradeType;

        if (tradeId.empty()) {
            throw std::invalid_argument("A valid non null, non empty trade ID must be provided");
        }

        /*
        // if we want to identify Bond name from the tradeId. 
        else{
        size_t pos = tradeId.find_first_of("0123456789");      // determine the first index of number
        std::string tradeprefix = tradeId.substr(0, pos);


        if (tradeprefix == "GOV") { std::string tradeType_ = GovBondTradeType; }
        else if (tradeprefix == "CORP") { std::string tradeType_ = CorpBondTradeType ;} 
        }*/

        tradeId_ = tradeId;
    }


 //   std::string getTradeType() const override { return tradeType_; }

private:
    std::string tradeType_;
  //  std::string tradeId_;
};

#endif // BONDTRADE_H

