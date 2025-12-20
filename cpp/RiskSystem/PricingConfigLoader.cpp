#include "PricingConfigLoader.h"
#include <stdexcept>


#include <fstream>
#include <regex>
#include <stdexcept>
#include <string>  


PricingEngineConfig PricingConfigLoader::loadConfig() {

PricingEngineConfig configs; // This is the vector of config that we will return
    std::ifstream xmlfile(configFile_);

    if (!xmlfile.is_open()) {
        throw std::runtime_error("Could not open pricing config file: " + configFile_);
    }

    std::string line;
    // Read regex string
    std::regex engineregex("tradeType=\"([^\"]+)\"\\s+assembly=\"([^\"]+)\"\\s+pricingEngine=\"([^\"]+)\"");
    std::smatch match;

    while (std::getline(xmlfile, line)) {
        if (line.find("<Engine") != std::string::npos) {
            if (std::regex_search(line, match, engineregex)) {
                
                std::string tradeType = match[1].str();
                std::string assembly = match[2].str();
                std::string engine = match[3].str();

                // Fill the vector objects
                PricingEngineConfigItem item; 
                item.setTradeType(tradeType);
                item.setAssembly(assembly);
                item.setTypeName(engine);

                // FIX 2: Push the item into the 'configs' vector
                configs.push_back(item);
            }
        }
    }

    // Check if the vector is empty
    if (configs.empty()) {
        throw std::runtime_error("No valid engine configurations found in: " + configFile_);
    }

    // Return the vector 'configs
    return configs; 
}



std::string PricingConfigLoader::getConfigFile() const {
    return configFile_;
}

void PricingConfigLoader::setConfigFile(const std::string& file) {
    configFile_ = file;
}  
