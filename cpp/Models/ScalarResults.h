#ifndef SCALARRESULTS_H
#define SCALARRESULTS_H

#include "IScalarResultReceiver.h"
#include "ScalarResult.h"
#include <map>
#include <vector>
#include <optional>
#include <string>
#include <iterator>
#include <iostream>

// Forward declaration of the operator for global scope
std::ostream& operator<<(std::ostream& os, const ScalarResult& res);

class ScalarResults : public IScalarResultReceiver {
public:
    virtual ~ScalarResults();
    std::optional<ScalarResult> operator[](const std::string& tradeId) const;

    bool containsTrade(const std::string& tradeId) const;

    virtual void addResult(const std::string& tradeId, double result) override;
    virtual void addError(const std::string& tradeId, const std::string& error) override;

    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = ScalarResult;
        using difference_type = std::ptrdiff_t;
        
        // Default constructor
        Iterator() : index_(-1), parent_(nullptr) {}

        Iterator& operator++();
        ScalarResult operator*() const;
        
        // Modified comparison: Only check index and parent identity
        bool operator!=(const Iterator& other) const {
            return index_ != other.index_;
        }

        bool operator==(const Iterator& other) const {
            return index_ == other.index_;
        }

    private:
        std::vector<std::string> allKeys_;
        int index_; 
        const ScalarResults* parent_;

        // Constructor used by begin()
        Iterator(std::vector<std::string> keys, int idx, const ScalarResults* parent)
            : allKeys_(std::move(keys)), index_(idx), parent_(parent) {}

        friend class ScalarResults;
    };

    Iterator begin() const;
    Iterator end() const;

private:
    std::map<std::string, double> results_;
    std::map<std::string, std::string> errors_;
};

#endif // SCALARRESULTS_H
