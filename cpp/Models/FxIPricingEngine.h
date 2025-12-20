#ifndef FXIPRICINGENGINE_H
#define FXIPRICINGENGINE_H

#include "IScalarResultReceiver.h"

#include "FXITrade.h"

class FxIPricingEngine {
public:
    virtual ~FxIPricingEngine() = default;
    virtual void price(FXITrade* trade, IScalarResultReceiver* resultReceiver) = 0;

};

#endif // FXIPRICINGENGINE_H

