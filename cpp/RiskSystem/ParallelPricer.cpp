#include "ParallelPricer.h"
#include "GovBondPricingEngine.h"
#include "CorpBondPricingEngine.h"
#include <iostream>
#include <algorithm>

ParallelPricer::~ParallelPricer() {
    for (auto const& [type, engine] : pricers_) {
        delete engine;
    }
}

void ParallelPricer::loadPricers() {
    if (!pricers_.empty()) return;

    PricingConfigLoader loader;
    loader.setConfigFile("./PricingConfig/PricingEngines.xml");
    auto config = loader.loadConfig();

    for (const auto& item : config) {
        IPricingEngine* engine = nullptr;
        if (item.getTypeName().find("GovBondPricingEngine") != std::string::npos)
            engine = new GovBondPricingEngine();
        else if (item.getTypeName().find("CorpBondPricingEngine") != std::string::npos)
            engine = new CorpBondPricingEngine();

        if (engine) pricers_[item.getTradeType()] = engine;
    }
}

void ParallelPricer::price(const std::vector<std::vector<ITrade*>>& tradeContainers, 
                           IScalarResultReceiver* resultReceiver) {
    loadPricers();
    
    std::vector<std::future<void>> futures;

    for (const auto& container : tradeContainers) {
        for (ITrade* trade : container) {
            if (!trade || trade->getTradeId().empty()) continue;

            // Use std::async to run each trade pricing in a separate thread
            futures.push_back(std::async(std::launch::async, [this, trade, resultReceiver]() {
                auto it = pricers_.find(trade->getTradeType());
                
                if (it != pricers_.end()) {
                    // We must protect the receiver because addResult/addError 
                    // modify shared state (the maps in ScalarResults)
                    std::lock_guard<std::mutex> lock(this->resultMutex_);
                    it->second->price(trade, resultReceiver);
                } else {
                    std::lock_guard<std::mutex> lock(this->resultMutex_);
                    resultReceiver->addError(trade->getTradeId(), "No engine for: " + trade->getTradeType());
                }
            }));
        }
    }

    // This loop ensures the function only returns once all threads are finished
    for (auto& fut : futures) {
        fut.wait(); 
    }
}
