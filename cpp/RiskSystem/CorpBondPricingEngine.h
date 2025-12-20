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

    // Virtual destructor ensuring proper cleanup
    virtual ~CorpBondPricingEngine() = default;

    /**
     * Prices a Corporate Bond trade.
     * @param trade The trade to price (expected to be a Corporate Bond)
     * @param resultReceiver The receiver to notify of the result or any errors
     */
    void price(ITrade* trade, IScalarResultReceiver* resultReceiver) override;
};

#endif // CORPBONDPRICINGENGINE_H
