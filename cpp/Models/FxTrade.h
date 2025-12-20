#ifndef FXTRADE_H
#define FXTRADE_H

#include "FXBaseTrade.h"
#include <chrono>
#include <stdexcept>

class FxTrade : public FXBaseTrade {
public:
    static constexpr const char* FxSpotTradeType = "FxSpot";
    static constexpr const char* FxForwardTradeType = "FxFwd";
    
 //   FxTrade(const std::string& tradeId = "", const std::string& tradeType = FxSpotTradeType)
 //       : tradeType_(tradeType) {
    FxTrade(const std::string& tradeId){

        if (!tradeId.empty()) {
            tradeId_ = tradeId;
        }
    }
    
  //  std::string getTradeType() const override {
  //      return tradeType_;
 //   }
    
 //   std::chrono::system_clock::time_point getValueDate() const { return valueDate_; }
 //   void setValueDate(const std::chrono::system_clock::time_point& date) { valueDate_ = date; }




private:
  //  std::string tradeType_;

    std::string tradeId_;

//  std::chrono::system_clock::time_point valueDate_;
   // std::double Amount_;

};

#endif // FXTRADE_H

