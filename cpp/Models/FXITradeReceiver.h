#ifndef FXITRADERECEIVER_H
#define FXITRADERECEIVER_H

#include "FXITrade.h"

class FXITradeReceiver {
public:
    virtual ~FXITradeReceiver() = default;
    virtual void add(FXITrade* trade) = 0;
};

#endif // FXITRADERECEIVER_H

