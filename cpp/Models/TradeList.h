#ifndef TRADELIST_H
#define TRADELIST_H

#include "ITrade.h"
#include "ITradeReceiver.h"
#include <vector>

#include "FXITrade.h"   // Add this
#include "FXITradeReceiver.h"  // creat this


class TradeList : public ITradeReceiver {
public:
    TradeList() = default;
    
    void add(ITrade* trade) override {
        trades_.push_back(trade);
    }
    
    size_t size() const { return trades_.size(); }
    ITrade* operator[](size_t index) const { return trades_[index]; }
    
    using iterator = std::vector<ITrade*>::iterator;
    using const_iterator = std::vector<ITrade*>::const_iterator;
    
    iterator begin() { return trades_.begin(); }
    iterator end() { return trades_.end(); }
    const_iterator begin() const { return trades_.begin(); }
    const_iterator end() const { return trades_.end(); }
    
private:
    std::vector<ITrade*> trades_;
};


// add a new class for  Fx

class TradeListX : public FXITradeReceiver {
public:
    TradeListX() = default;
    
    void add(FXITrade* trade) override {
        Fxtrades_.push_back(trade);
    }
    
    size_t size() const { return Fxtrades_.size(); }
    FXITrade* operator[](size_t index) const { return Fxtrades_[index]; }
    
    using iterator = std::vector<FXITrade*>::iterator;
    using const_iterator = std::vector<FXITrade*>::const_iterator;
    
    iterator begin() { return Fxtrades_.begin(); }
    iterator end() { return Fxtrades_.end(); }
    const_iterator begin() const { return Fxtrades_.begin(); }
    const_iterator end() const { return Fxtrades_.end(); }
    
private:
    std::vector<FXITrade*> Fxtrades_;
};



#endif // TRADELIST_H
