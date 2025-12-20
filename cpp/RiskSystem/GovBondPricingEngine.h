#ifndef GOVBONDPRICINGENGINE_H
#define GOVBONDPRICINGENGINE_H

#include "../Models/IPricingEngine.h"
#include "../Models/ITrade.h"
#include "../Models/IScalarResultReceiver.h"

// Inherits from the base interface
class GovBondPricingEngine : public IPricingEngine {
public:
    // Standard constructor and virtual destructor
    GovBondPricingEngine() = default;
    virtual ~GovBondPricingEngine() = default;

    
    // Implementation of the interface method.
    void price(ITrade* trade, IScalarResultReceiver* resultReceiver) override;
};

#endif // GOVBONDPRICINGENGINE_H
