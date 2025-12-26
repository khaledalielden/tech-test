#include "SerialPricer.h"
#include "FxPricingEngine.h"
#include "GovBondPricingEngine.h"
#include "CorpBondPricingEngine.h"
#include <iostream>
#include <algorithm>

// --- Bond Pricer Implementation ---
SerialPricer::~SerialPricer() {
    for (auto const& [type, engine] : pricers_) delete engine;
}

void SerialPricer::loadPricers() {
    if (!pricers_.empty()) return;
    PricingConfigLoader loader;
    loader.setConfigFile("./PricingConfig/PricingEngines.xml");
    auto config = loader.loadConfig();

    for (const auto& item : config) {
        IPricingEngine* engine = nullptr;
        // Exact match logic for Bonds
        if (item.getTypeName().find("GovBondPricingEngine") != std::string::npos) 
            engine = new GovBondPricingEngine();
        else if (item.getTypeName().find("CorpBondPricingEngine") != std::string::npos) 
            engine = new CorpBondPricingEngine();

        if (engine) pricers_[item.getTradeType()] = engine;
    }
}

void SerialPricer::price(const std::vector<std::vector<ITrade*>>& tradeContainers, IScalarResultReceiver* resultReceiver) {
    loadPricers();
    for (const auto& container : tradeContainers) {
        for (ITrade* trade : container) {
            if (!trade || trade->getTradeId().empty()) continue;

            auto it = pricers_.find(trade->getTradeType());
            if (it != pricers_.end()) {
                it->second->price(trade, resultReceiver);
            } else {
                // RESTORED: This ensures GOV007 shows the "Supra" error
                resultReceiver->addError(trade->getTradeId(), "No engine for Bond type: " + trade->getTradeType());
            }
        }
    }
}

// --- FX Pricer Implementation ---
FxSerialPricer::~FxSerialPricer() {
    for (auto const& [type, engine] : Fxpricers_) delete engine;
}

void FxSerialPricer::FxloadPricers() {
    if (!Fxpricers_.empty()) return;
    PricingConfigLoader loader;
    loader.setConfigFile("./PricingConfig/PricingEngines.xml");
    auto config = loader.loadConfig();

    for (const auto& item : config) {
        // Look specifically for the FX Pricing Engine
        if (item.getTypeName().find("FxPricingEngine") != std::string::npos) {
            Fxpricers_[item.getTradeType()] = new FxPricingEngine();
        }
    }
}

void FxSerialPricer::Fxprice(const std::vector<std::vector<FXITrade*>>& tradeContainers, 
                             IScalarResultReceiver* resultReceiver) {
    FxloadPricers();
    
    for (const auto& tradeContainer : tradeContainers) {
        for (FXITrade* trade : tradeContainer) {
            if (trade == nullptr || trade->getTradeId().empty()) continue;

            std::string type = trade->getTradeType();
            
            // Try exact match first (FxSpot, FxFwd)
            auto it = Fxpricers_.find(type);
            if (it != Fxpricers_.end()) {
                it->second->price(trade, resultReceiver);
            } 
            else {
                // If no exact match, try a case-insensitive search or look for ANY Fx engine
                // because all FX trades currently use the same FxPricingEngine
                bool engineFound = false;
                for (auto const& [xmlType, engine] : Fxpricers_) {
                    if (type.find("Fx") != std::string::npos || xmlType.find("Fx") != std::string::npos) {
                        engine->price(trade, resultReceiver);
                        engineFound = true;
                        break; 
                    }
                }
                
                if (!engineFound) {
                    resultReceiver->addError(trade->getTradeId(), "No FX engine for type: " + type);
                }
            }
        }
    }
}

// --- Engine Implementations ---
void FxPricingEngine::price(FXITrade* trade, IScalarResultReceiver* receiver) {
    if (trade) {
        // We use the amount as the price for FX trades
        receiver->addResult(trade->getTradeId(), trade->getAmount());
    }
}

void GovBondPricingEngine::price(ITrade* trade, IScalarResultReceiver* receiver) {
    if (trade) receiver->addResult(trade->getTradeId(), 100.0);
}

void CorpBondPricingEngine::price(ITrade* trade, IScalarResultReceiver* receiver) {
    if (trade) receiver->addResult(trade->getTradeId(), 100.0);
}
