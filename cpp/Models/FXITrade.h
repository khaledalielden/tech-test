#ifndef FXITRADE_H
#define FXITRADE_H

#include <string>
#include <chrono>
#include <memory>

class FXITrade {
public:
    virtual ~FXITrade() = default;
    
    virtual std::chrono::system_clock::time_point getTradeDate() const = 0;
    virtual void setTradeDate(const std::chrono::system_clock::time_point& date) = 0;

    virtual std::chrono::system_clock::time_point getValueDate() const = 0;
    virtual void setValueDate(const std::chrono::system_clock::time_point& date2) = 0;

    
    virtual std::string getInstrument() const = 0;
    virtual void setInstrument(const std::string& instrument) = 0;
    
    virtual std::string getCounterparty() const = 0;
    virtual void setCounterparty(const std::string& counterparty) = 0;
    
    
    virtual double getRate() const = 0;
    virtual void setRate(double rate) = 0;
    
    virtual std::string getTradeType() const = 0;
    virtual void setTradeType(const std::string& tradetype) = 0; // set the override function for tradetype

    virtual double  getAmount() const = 0;             // Added the override function
    virtual void setAmount(double amount) = 0;     // Added the override function


    virtual std::string getTradeId() const = 0;

};

#endif // FXITRADE_H

