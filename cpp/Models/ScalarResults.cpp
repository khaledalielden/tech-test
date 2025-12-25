#include "ScalarResults.h"
#include <stdexcept>
#include <iostream>
#include <set>
#include <vector>

ScalarResults::~ScalarResults() = default;

// --- Access Data ---
std::optional<ScalarResult> ScalarResults::operator[](const std::string& tradeId) const {
    if (!containsTrade(tradeId)) {
        return std::nullopt;
    }

    std::optional<double> priceResult = std::nullopt;
    std::optional<std::string> error = std::nullopt;

    auto resultIt = results_.find(tradeId);
    if (resultIt != results_.end()) {
        priceResult = resultIt->second;
    }

    auto errorIt = errors_.find(tradeId);
    if (errorIt != errors_.end()) {
        error = errorIt->second;
    }

    return ScalarResult(tradeId, priceResult, error);
}

bool ScalarResults::containsTrade(const std::string& tradeId) const {
    return results_.find(tradeId) != results_.end() || errors_.find(tradeId) != errors_.end();
}

void ScalarResults::addResult(const std::string& tradeId, double result) {
    results_[tradeId] = result;
}

void ScalarResults::addError(const std::string& tradeId, const std::string& error) {
    errors_[tradeId] = error;
}

// --- Iterator Implementation on the data list ---
ScalarResults::Iterator ScalarResults::begin() const {
    // Create a set of all unique keys from both maps
    std::set<std::string> uniqueKeys;
    for (auto const& [key, val] : results_) uniqueKeys.insert(key);
    for (auto const& [key, val] : errors_) uniqueKeys.insert(key);

    // Convert set to a vector for indexed access within the iterator
    std::vector<std::string> keys(uniqueKeys.begin(), uniqueKeys.end());
    
    // Start at index 0, passing 'this' parent to allow map lookups
    return Iterator(keys, 0, this);
}

ScalarResults::Iterator ScalarResults::end() const {
    // Return an iterator representing the past-the-end position
    return Iterator({}, -1, this); 
}

ScalarResults::Iterator& ScalarResults::Iterator::operator++() {
    if (index_ != -1) {
        index_++;
        if (index_ >= (int)allKeys_.size()) {
            index_ = -1; // Mark as finished
        }
    }
    return *this;
}

ScalarResult ScalarResults::Iterator::operator*() const {
    if (index_ == -1 || index_ >= (int)allKeys_.size()) {
        throw std::out_of_range("Iterator out of bounds");
    }

    const std::string& tradeId = allKeys_[index_];
    
    // Fetch data from both maps for this specific ID
    std::optional<double> price = std::nullopt;
    std::optional<std::string> errMsg = std::nullopt;

    auto resIt = parent_->results_.find(tradeId);
    if (resIt != parent_->results_.end()) price = resIt->second;

    auto errIt = parent_->errors_.find(tradeId);
    if (errIt != parent_->errors_.end()) errMsg = errIt->second;

    return ScalarResult(tradeId, price, errMsg);
}

bool ScalarResults::Iterator::operator!=(const Iterator& other) const {
    // Simpler comparison based on the current index
    return index_ != other.index_;
}

// --- Helper Functions ---

std::ostream& operator<<(std::ostream& os, const ScalarResult& res) {
    os << "Trade: " << res.getTradeId();
    if (res.getResult().has_value()) os << " | Price: " << res.getResult().value();
    if (res.getError().has_value()) os << " | Error: " << res.getError().value();
    return os;
}
