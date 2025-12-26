#ifndef FXBASETRADE_H
#define FXBASETRADE_H

#include "FXITrade.h"
#include <chrono>
#include <string>

class FXBaseTrade : public FXITrade {
public:
    FXBaseTrade() = default;
    virtual ~FXBaseTrade() = default;
    
    std::chrono::system_clock::time_point getTradeDate() const override { return tradeDate_; }
    void setTradeDate(const std::chrono::system_clock::time_point& date) override { tradeDate_ = date; }
    

  //  std::chrono::system_clock::time_point getValueDate() const override { return tradeDate_; }
  //  void setValueDate(const std::chrono::system_clock::time_point& date) override { tradeDate_ = date; }

    std::string getInstrument() const override { return instrument_; }
    void setInstrument(const std::string& instrument) override { instrument_ = instrument; }
    
    std::string getCounterparty() const override { return counterparty_; }
    void setCounterparty(const std::string& counterparty) override { counterparty_ = counterparty; }
    
//    double getNotional() const override { return notional_; }
//    void setNotional(double notional) override { notional_ = notional; }
    
    double getRate() const override { return rate_; }
    void setRate(double rate) override { rate_ = rate; }
    
 //   std::string getTradeType() const override = 0;
 //   std::string getTradeType() const override { return tradeType_; }                         // Added
 //   void setTradeType(const std::string& tradetype) override { tradeType_ = tradetype; }

    double getAmount() const override { return amount_; }             // Added the override function
    void setAmount(double amount) override { amount_ = amount; }     // Added the override function


    std::chrono::system_clock::time_point getValueDate() const { return valueDate_; }
    void setValueDate(const std::chrono::system_clock::time_point& date2) { valueDate_ = date2; }



    std::string getTradeId() const override { return tradeId_; }

    
protected:
    std::string tradeId_;
  //  std::string tradeType_;

private:
    std::chrono::system_clock::time_point tradeDate_;
    std::chrono::system_clock::time_point valueDate_;
    std::string instrument_;
    std::string counterparty_;
  //  double notional_ = 0.0;
    double rate_ = 0.0;
  //  std::string tradeType_;
    double amount_;
};

#endif // FXBASETRADE_H
