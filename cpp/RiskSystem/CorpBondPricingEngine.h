#ifndef CORPBONDPRICINGENGINE_H
#define CORPBONDPRICINGENGINE_H

#include "../Models/IPricingEngine.h"
#include "../Models/ITrade.h"
#include "../Models/IScalarResultReceiver.h"

/**
 * CorpBondPricingEngine handles the pricing logic for Corporate Bond trades.
 * It implements the IPricingEngine interface.
 */
class CorpBondPricingEngine : public IPricingEngine {
public:
    // Constructor
    CorpBondPricingEngine() = default;

    // Virtual destructor ensuring cleanup
    virtual ~CorpBondPricingEngine() = default;

    void price(ITrade* trade, IScalarResultReceiver* resultReceiver) override;
};

#endif // CORPBONDPRICINGENGINE_H
