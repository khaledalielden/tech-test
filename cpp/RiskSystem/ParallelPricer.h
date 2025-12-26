#ifndef STREAMINGTRADELOADER_H
#define STREAMINGTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/ITrade.h"
#include "../Models/IScalarResultReceiver.h"
#include "../Models/IPricingEngine.h"
#include <vector>
#include <map>
#include <string>

#include "../Loaders/FXITradeLoader.h"
#include "../Models/FXITrade.h"

class StreamingTradeLoader {
private:
    std::map<std::string, IPricingEngine*> pricers_;
    
    std::vector<ITradeLoader*> getTradeLoaders();
    void loadPricers();
    
public:
    ~StreamingTradeLoader();
    
    void loadAndPrice(IScalarResultReceiver* resultReceiver);
};

// new
class FxStreamingTradeLoader {
private:
    std::map<std::string, IPricingEngine*> pricers_;
    
    std::vector<FXITradeLoader*> getTradeLoaders();
    void loadPricers();
    
public:
    ~FxStreamingTradeLoader();
    
    void loadAndPrice(IScalarResultReceiver* resultReceiver);
};

#endif // STREAMINGTRADELOADER_H
