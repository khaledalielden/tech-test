#ifndef SERIALTRADELOADER_H
#define SERIALTRADELOADER_H

#include "../Loaders/ITradeLoader.h"
#include "../Models/ITrade.h"
#include <vector>

#include "../Loaders/FXITradeLoader.h"
#include "../Models/FXITrade.h"

class SerialTradeLoader {
private:
    std::vector<ITradeLoader*> getTradeLoaders();
    
public:
    std::vector<std::vector<ITrade*>> loadTrades();
};
/*
class FxSerialTradeLoader {
private:
    std::vector<FXITradeLoader*> FxgetTradeLoaders();
public:
    std::vector<std::vector<FXITrade*>> loadTrades();
};
*/
#endif // SERIALTRADELOADER_H
