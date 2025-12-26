#ifndef FXTRADE_H
#define FXTRADE_H

#include "FXBaseTrade.h"
#include <chrono>
#include <string>

class FxTrade : public FXBaseTrade {
public:
    static constexpr const char* FxSpotTradeType = "FxSpot";
    static constexpr const char* FxForwardTradeType = "FxFwd";
    
    // Constructor: Initialize the ID and set a default type

   FxTrade(const std::string& tradeId = "", const std::string& tradeType = FxSpotTradeType)
    : tradeId_(tradeId), tradeType_(tradeType) {    }     // The body can remain empty because the initializer list above 
                                                          // does all the work!


    // MANDATORY: The Pricer uses this to find the engine in the map
    std::string getTradeType() const override {
        return tradeType_;
    }

    // MANDATORY: The Engine uses this to get the price/amount
 //   double getAmount() const override {
 //       return amount_;
 //   }

    // Setters used by the FxTradeLoader
    void setTradeType(const std::string& type) { tradeType_ = type; }
  //  void setAmount(double amount) { amount_ = amount; }
    void setTradeId(const std::string& id) { tradeId_ = id; }
    
    // Explicitly override getTradeId from base if needed
    std::string getTradeId() const override { return tradeId_; }

private:
    std::string tradeId_;
    std::string tradeType_;
 //   double amount_;
};

#endif // FXTRADE_H
