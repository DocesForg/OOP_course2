// lib/parser.h
#pragma once

#include <filesystem>
#include <istream>
#include <string>
#include <vector>
#include <variant>
#include <memory>
#include <unordered_map>
#include <optional>

namespace omfl {

class OMFLValue {
public:
    const std::vector<OMFLValue>& AsArray() const; // <-- Новый метод
    using Value = std::variant<
        std::monostate,
        int32_t,
        float,
        bool,
        std::string,
        std::vector<OMFLValue>
    >;

    OMFLValue() = default;
    explicit OMFLValue(Value value);

    bool IsInt() const;
    bool IsFloat() const;
    bool IsBool() const;
    bool IsString() const;
    bool IsArray() const;
    bool valid() const;

    int32_t AsInt() const;
    int32_t AsIntOrDefault(int32_t default_value) const;
    float AsFloat() const;
    float AsFloatOrDefault(float default_value) const;
    bool AsBool() const;
    bool AsBoolOrDefault(bool default_value) const;
    const std::string& AsString() const;
    std::string AsStringOrDefault(const std::string& default_value) const;
    const OMFLValue& operator[](size_t index) const;

    const Value& GetValue() const { return value_; }

private:
    Value value_;
};

class OMFLSection {
public:
    OMFLSection() = default;

    bool valid() const { return true; }
    const OMFLValue& Get(const std::string& key) const;

    void AddValue(const std::string& key, OMFLValue::Value value);
    void AddSection(const std::string& key, std::shared_ptr<OMFLSection> section);

    std::unordered_map<std::string, OMFLValue> values;
    std::unordered_map<std::string, std::shared_ptr<OMFLSection>> sections;
    static OMFLValue empty_value_;
    static const OMFLValue empty_section_;
};

class OMFLRoot : public OMFLSection {
public:
    static OMFLRoot parse(const std::string& str);
    static OMFLRoot parse(const std::filesystem::path& path);

private:
    OMFLRoot() = default;
    bool ParseStream(std::istream& input);
};

OMFLRoot parse(const std::string& str);
OMFLRoot parse(const std::filesystem::path& path);

}// namespace omfl