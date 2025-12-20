#ifndef SERIALPRICER_H
#define SERIALPRICER_H

#include "../Models/IPricingEngine.h"
#include "../Models/ITrade.h"
#include "../Models/IScalarResultReceiver.h"
#include "PricingConfigLoader.h"
#include <map>
#include <vector>
#include <string>

#include "../Models/FXITrade.h"
#include "../Models/FxIPricingEngine.h"

/**
 * SerialPricer handles the pricing of standard trades (Bonds).
 * It expects trade containers of type ITrade*.
 */
class SerialPricer {
private:
    std::map<std::string, IPricingEngine*> pricers_;
    void loadPricers();
    
public:
    virtual ~SerialPricer();
    
    // Processes the Bond-dimension trades
    void price(const std::vector<std::vector<ITrade*>>& tradeContainers, 
               IScalarResultReceiver* resultReceiver);
};


/**
 * FxSerialPricer handles the pricing of FX trades.
 * It expects trade containers of type FXITrade*.
 */
class FxSerialPricer {
private:
    std::map<std::string, FxIPricingEngine*> Fxpricers_;
    void FxloadPricers();
    
public:
    virtual ~FxSerialPricer();
    
    // Processes the FX-dimension trades
    void Fxprice(const std::vector<std::vector<FXITrade*>>& tradeContainers, 
                 IScalarResultReceiver* resultReceiver);
};

#endif // SERIALPRICER_H
