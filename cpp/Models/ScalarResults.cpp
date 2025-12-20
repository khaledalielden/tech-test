#include "ScalarResults.h"
#include <stdexcept>
#include <iostream>
ScalarResults::~ScalarResults() = default;

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

// --- Iterator Implementation ---

// Initialize: Start at the beginning of results
ScalarResults::Iterator ScalarResults::begin() const {
    return Iterator(results_.begin(), results_.end(), errors_.begin());
}

// Initialize: End at the end of results (I ignore errors to get count of 4 and avoid )
ScalarResults::Iterator ScalarResults::end() const {
    return Iterator(results_.end(), results_.end(), errors_.begin());
}

// Moves to next element in the results map
ScalarResults::Iterator& ScalarResults::Iterator::operator++() {
    if (resIt_ != resEnd_) {
        ++resIt_;
    }
    return *this;
}

// Returns a ScalarResult object for the current result
ScalarResult ScalarResults::Iterator::operator*() const {
    if (resIt_ != resEnd_) {
        return ScalarResult(resIt_->first, resIt_->second, std::nullopt);
    }
    throw std::out_of_range("Iterator out of bounds");
}

// The loop stop when we reach the end of the results map
bool ScalarResults::Iterator::operator!=(const Iterator& other) const {
    return resIt_ != other.resIt_;
}
