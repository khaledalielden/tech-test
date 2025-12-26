#include "StreamingTradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"
#include "PricingConfigLoader.h"
#include "../RiskSystem/GovBondPricingEngine.h"
#include "../RiskSystem/CorpBondPricingEngine.h"
#include "../RiskSystem/FxPricingEngine.h"
#include <iostream>
#include <vector>

// --- StreamingTradeLoader (Bonds) ---

std::vector<ITradeLoader*> StreamingTradeLoader::getTradeLoaders() {
    std::vector<ITradeLoader*> loaders;
    BondTradeLoader* bondLoader = new BondTradeLoader();
    bondLoader->setDataFile("TradeData/BondTrades.dat");
    loaders.push_back(bondLoader);
    return loaders;
}

void StreamingTradeLoader::loadPricers() {
    if (!pricers_.empty()) return;
    PricingConfigLoader configLoader;
    configLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    auto config = configLoader.loadConfig();

    for (const auto& item : config) {
        IPricingEngine* engine = nullptr;
        if (item.getTypeName().find("GovBondPricingEngine") != std::string::npos)
            engine = new GovBondPricingEngine();
        else if (item.getTypeName().find("CorpBondPricingEngine") != std::string::npos)
            engine = new CorpBondPricingEngine();

        if (engine) pricers_[item.getTradeType()] = engine;
    }
}

StreamingTradeLoader::~StreamingTradeLoader() {
    for (auto const& [type, engine] : pricers_) delete engine;
}

void StreamingTradeLoader::loadAndPrice(IScalarResultReceiver* resultReceiver) {
    loadPricers();
    std::vector<ITradeLoader*> loaders = getTradeLoaders();

    for (ITradeLoader* loader : loaders) {
        std::vector<ITrade*> trades = loader->loadTrades();
        for (ITrade* trade : trades) {
            if (trade && !trade->getTradeId().empty()) {
                auto it = pricers_.find(trade->getTradeType());
                if (it != pricers_.end()) {
                    it->second->price(trade, resultReceiver);
                } else {
                    resultReceiver->addError(trade->getTradeId(), "No engine for: " + trade->getTradeType());
                }
            }
            delete trade; 
        }
        delete loader; 
    }
}

// --- FxStreamingTradeLoader (FX) ---

std::vector<FXITradeLoader*> FxStreamingTradeLoader::getTradeLoaders() {
    std::vector<FXITradeLoader*> loaders;
    FxTradeLoader* fxLoader = new FxTradeLoader();
    fxLoader->setDataFile("TradeData/FxTrades.dat");
    loaders.push_back(fxLoader);
    return loaders;
}

void FxStreamingTradeLoader::loadPricers() {
    if (!pricers_.empty()) return;
    PricingConfigLoader configLoader;
    configLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    auto config = configLoader.loadConfig();

    for (const auto& item : config) {
        if (item.getTypeName().find("FxPricingEngine") != std::string::npos) {
            // Use reinterpret_cast to store the FxPricingEngine in the IPricingEngine* map
            pricers_[item.getTradeType()] = reinterpret_cast<IPricingEngine*>(new FxPricingEngine());
        }
    }
}

FxStreamingTradeLoader::~FxStreamingTradeLoader() {
    // We must cast back to FxPricingEngine* or use a void* to delete properly 
    // to avoid undefined behavior if the destructors aren't virtual
    for (auto const& [type, engine] : pricers_) {
        delete reinterpret_cast<FxPricingEngine*>(engine);
    }
}

void FxStreamingTradeLoader::loadAndPrice(IScalarResultReceiver* resultReceiver) {
    loadPricers();
    std::vector<FXITradeLoader*> loaders = getTradeLoaders();

    for (FXITradeLoader* loader : loaders) {
        std::vector<FXITrade*> trades = loader->loadTrades();
        
        for (FXITrade* trade : trades) {
            if (trade && !trade->getTradeId().empty()) {
                auto it = pricers_.find(trade->getTradeType());
                if (it != pricers_.end()) {
                    // Use reinterpret_cast here to match the type stored in loadPricers
                    FxPricingEngine* fxEngine = reinterpret_cast<FxPricingEngine*>(it->second);
                    fxEngine->price(trade, resultReceiver);
                }
            }
            delete trade;
        }
        delete loader;
    }
}
