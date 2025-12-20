#include "SerialPricer.h"
#include "FxPricingEngine.h"
#include "GovBondPricingEngine.h"
#include "CorpBondPricingEngine.h"
#include <iostream>
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
        if (item.getTypeName().find("GovBondPricingEngine") != std::string::npos) engine = new GovBondPricingEngine();
        else if (item.getTypeName().find("CorpBondPricingEngine") != std::string::npos) engine = new CorpBondPricingEngine();

        if (engine) pricers_[item.getTradeType()] = engine;
        // SILENT: No 'else' block means no errors added for FX engines found in XML
    }
}

void SerialPricer::price(const std::vector<std::vector<ITrade*>>& tradeContainers, IScalarResultReceiver* resultReceiver) {
    loadPricers();
    for (const auto& container : tradeContainers) {
        for (ITrade* trade : container) {
            if (!trade) continue;
            auto it = pricers_.find(trade->getTradeType());
            if (it != pricers_.end()) it->second->price(trade, resultReceiver);
            // SILENT: If it's an FX trade in a Bond container, we just skip it.
        }
    }
}

// --- FX Pricer Implementation ---
FxSerialPricer::~FxSerialPricer() {
    for (auto const& [type, engine] : Fxpricers_) delete engine;
}

void FxSerialPricer::FxloadPricers() {
    if (!Fxpricers_.empty()) return;

    PricingConfigLoader pricingConfigLoader;
    pricingConfigLoader.setConfigFile("./PricingConfig/PricingEngines.xml");
    PricingEngineConfig pricerConfig = pricingConfigLoader.loadConfig();

    for (const auto& configItem : pricerConfig) {
        std::string typeName = configItem.getTypeName();
        std::string tradeType = configItem.getTradeType(); // e.g. "FxSpot" or "FxFwd"

        if (typeName.find("FxPricingEngine") != std::string::npos) {
            // We MUST use the tradeType from the XML as the key
            Fxpricers_[tradeType] = new FxPricingEngine();
        } 
    }
}
/*
void FxSerialPricer::FxloadPricers() {
    if (!Fxpricers_.empty()) return;
    PricingConfigLoader loader;
    loader.setConfigFile("./PricingConfig/PricingEngines.xml");
    auto config = loader.loadConfig();

    for (const auto& item : config) {
        FxIPricingEngine* engine = nullptr;
        if (item.getTypeName().find("FxPricingEngine") != std::string::npos) engine = new FxPricingEngine();

        if (engine) Fxpricers_[item.getTradeType()] = engine;
        // SILENT: No errors added for Bond engines found in XML
    }
}


void FxSerialPricer::Fxprice(const std::vector<std::vector<FXITrade*>>& tradeContainers, 
                             IScalarResultReceiver* resultReceiver) {
    FxloadPricers();
    for (const auto& container : tradeContainers) {
        for (FXITrade* trade : container) {
            if (!trade) continue;

            std::string type = trade->getTradeType();
            auto it = Fxpricers_.find(type);

            if (it != Fxpricers_.end()) {
                it->second->price(trade, resultReceiver);
            } else {
                // If you see this in the console, your tradeType string is wrong!
                std::printf("DEBUG: FX Trade %s skipped. Type '%s' not found in map.\n", 
                            trade->getTradeId().c_str(), type.c_str());
            }
        }
    }
}
*/



void FxSerialPricer::Fxprice(const std::vector<std::vector<FXITrade*>>& tradeContainers, 
                             IScalarResultReceiver* resultReceiver) {
    FxloadPricers();
    

    for (const auto& tradeContainer : tradeContainers) {
        for (FXITrade* trade : tradeContainer) {
            if (trade == nullptr) continue;

            std::string type = trade->getTradeType();
            auto it = Fxpricers_.find(type);
            
if (it != Fxpricers_.end()) {
    it->second->price(trade, resultReceiver);
} else {
    // THIS IS THE SMOKING GUN: If this prints, your trade names don't match the XML
    std::cout << "MISSING ENGINE FOR: [" << type << "]" << std::endl;
}
    //        if (it != Fxpricers_.end()) {
     //           it->second->price(trade, resultReceiver);
     //       } else {
                // If this prints, your Trade Type string in the data 
                // doesn't match "FxSpot" or "FxFwd" in the XML.
                resultReceiver->addError(trade->getTradeId(), "No engine for type: " + type);
      //      }
        }
    }
}



// --- Engine Logic ---
void FxPricingEngine::price(FXITrade* trade, IScalarResultReceiver* receiver) {
    if (trade) receiver->addResult(trade->getTradeId(), trade->getAmount());
}

void GovBondPricingEngine::price(ITrade* trade, IScalarResultReceiver* receiver) {
    if (trade) receiver->addResult(trade->getTradeId(), 100.0);
}
void CorpBondPricingEngine::price(ITrade* trade, IScalarResultReceiver* receiver) {
    if (trade) receiver->addResult(trade->getTradeId(), 100.0);
}
