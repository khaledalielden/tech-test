#ifndef ITRADERECEIVER_H
#define ITRADERECEIVER_H

#include "ITrade.h"
#include "FXITrade.h"

class ITradeReceiver {
public:
    virtual ~ITradeReceiver() = default;
    virtual void add(ITrade* trade) = 0;
};
/*
class FXITradeReceiver {
public:
    virtual ~FXITradeReceiver() = default;
    virtual void add(FXITrade* trade) = 0;
};*/

#endif // ITRADERECEIVER_H

