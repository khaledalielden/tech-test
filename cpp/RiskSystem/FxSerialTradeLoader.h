#ifndef FXSERIALTRADELOADER_H
#define FXSERIALTRADELOADER_H

#include <vector>

#include "../Loaders/FXITradeLoader.h"
#include "../Models/FXITrade.h"

/*
class FxSerialTradeLoader {
private:
    std::vector<FXITradeLoader*> FxgetTradeLoaders();
public:
    std::vector<std::vector<FXITrade*>> loadTrades();
};
*/



class FxSerialTradeLoader {
public:
    std::vector<FXITradeLoader*> FxgetTradeLoaders();
    std::vector<std::vector<FXITrade*>> loadTrades();
//private:

};

#endif // FXSERIALTRADELOADER_H
