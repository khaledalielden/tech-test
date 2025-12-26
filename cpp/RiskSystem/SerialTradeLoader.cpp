#include "SerialTradeLoader.h"
#include "../Loaders/BondTradeLoader.h"
//#include "../Loaders/FxTradeLoader.h"
/*
std::vector<ITradeLoader*> SerialTradeLoader::getTradeLoaders() {
    std::vector<ITradeLoader*> loaders;
    
    BondTradeLoader* bondLoader = new BondTradeLoader();
    bondLoader->setDataFile("TradeData/BondTrades.dat");
    loaders.push_back(bondLoader);
    
    return loaders;
}

std::vector<std::vector<ITrade*>> SerialTradeLoader::loadTrades() {
    auto loaders = getTradeLoaders();
    std::vector<std::vector<ITrade*>> result;
    
    for (auto loader : loaders) {
        result.push_back(loader->loadTrades());
    }
    
    return result;
}*/
//  new



/**
 * Creates the collection of specific loaders.
 * Note: In a production environment, we'd use smart pointers (std::unique_ptr)
 * to avoid manual deletion.
 */
std::vector<ITradeLoader*> SerialTradeLoader::getTradeLoaders() {
    std::vector<ITradeLoader*> loaders;
    
    // Initialize the Bond Loader
    BondTradeLoader* bondLoader = new BondTradeLoader();
    
    // Ensure the path is correct relative to your executable
    bondLoader->setDataFile("TradeData/BondTrades.dat");
    
    loaders.push_back(bondLoader);
    
    return loaders;
}

/**
 * Executes all registered loaders and returns a nested vector of trades.
 */
std::vector<std::vector<ITrade*>> SerialTradeLoader::loadTrades() {
    std::vector<ITradeLoader*> loaders = getTradeLoaders();
    std::vector<std::vector<ITrade*>> result;
    
    for (ITradeLoader* loader : loaders) {
        // Load the trades from the specific loader (e.g., BondTradeLoader)
        std::vector<ITrade*> trades = loader->loadTrades();
        
        // Only add the group if it's not empty
        if (!trades.empty()) {
            result.push_back(trades);
        }

        // Clean up the loader object to prevent memory leaks
        delete loader;
    }
    
    return result;
}

