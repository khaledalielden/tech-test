#ifndef FXITRADELOADER_H
#define FXITRADELOADER_H

#include "../Models/FXITrade.h"
#include <vector>
#include <string>

class FXITradeLoader {
public:
    virtual ~FXITradeLoader() = default;
    virtual std::vector<FXITrade*> loadTrades() = 0;
    virtual std::string getDataFile() const = 0;
    virtual void setDataFile(const std::string& file) = 0;
};

#endif // FXITRADELOADER_H
