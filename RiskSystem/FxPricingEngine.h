#ifndef FXPRICINGENGINE_H
#define FXPRICINGENGINE_H


#include "../Models/FxIPricingEngine.h"
#include "../Models/FXITrade.h"
#include "../Models/IScalarResultReceiver.h"

/**
 * FxPricingEngine implements the pricing logic for FxSpot and FxFwd trades.
 * It inherits from FxIPricingEngine to handle the FXITrade dimension.
 */
class FxPricingEngine : public FxIPricingEngine {
public:
    // Default constructor
    FxPricingEngine() = default;

    // Virtual destructor 
    virtual ~FxPricingEngine() = default;

    /**
     * Implementation of the pricing function for FX trades.
     * Note: This uses FXITrade* as the first parameter.
     */
    void price(FXITrade* trade, IScalarResultReceiver* resultReceiver) override;
};



#endif // FXPRICINGENGINE_H

