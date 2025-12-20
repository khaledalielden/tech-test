#include "FxSerialTradeLoader.h"
#include "../Loaders/FxTradeLoader.h"

// new
std::vector<FXITradeLoader*> FxSerialTradeLoader::FxgetTradeLoaders() {
    std::vector<FXITradeLoader*> loaders;
    
    FxTradeLoader* fxLoader = new FxTradeLoader();
    fxLoader->setDataFile("TradeData/FxTrades.dat");
    loaders.push_back(fxLoader);
    return loaders;
} 

std::vector<std::vector<FXITrade*>> FxSerialTradeLoader::loadTrades() {
    auto loaders = FxgetTradeLoaders();
    std::vector<std::vector<FXITrade*>> result;
    
    for (auto loader : loaders) {
        result.push_back(loader->loadTrades());
    }
    
    return result;
}
