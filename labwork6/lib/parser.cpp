// lib/parser.cpp
#include "parser.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <charconv>

namespace omfl {

OMFLValue OMFLSection::empty_value_;
const OMFLValue OMFLSection::empty_section_;

OMFLValue::OMFLValue(Value value) : value_(std::move(value)) {}

bool OMFLValue::IsInt() const {
    return std::holds_alternative<int32_t>(value_);
}

bool OMFLValue::IsFloat() const {
    return std::holds_alternative<float>(value_);
}

bool OMFLValue::IsBool() const {
    return std::holds_alternative<bool>(value_);
}

bool OMFLValue::IsString() const {
    return std::holds_alternative<std::string>(value_);
}

bool OMFLValue::IsArray() const {
    return std::holds_alternative<std::vector<OMFLValue>>(value_);
}

bool OMFLValue::valid() const {
    return !std::holds_alternative<std::monostate>(value_);
}
const std::vector<omfl::OMFLValue>& omfl::OMFLValue::AsArray() const {
    if (!IsArray()) {
        throw std::runtime_error("Value is not an array");
    }
    return std::get<std::vector<omfl::OMFLValue>>(value_);
}
int32_t OMFLValue::AsInt() const {
    if (IsInt()) return std::get<int32_t>(value_);
    if (IsFloat()) return static_cast<int32_t>(std::get<float>(value_));
    throw std::runtime_error("Not an integer");
}

int32_t OMFLValue::AsIntOrDefault(int32_t default_value) const {
    return IsInt() ? AsInt() : default_value;
}

float OMFLValue::AsFloat() const {
    if (IsFloat()) return std::get<float>(value_);
    if (IsInt()) return static_cast<float>(std::get<int32_t>(value_));
    throw std::runtime_error("Not a float");
}

float OMFLValue::AsFloatOrDefault(float default_value) const {
    return IsFloat() || IsInt() ? AsFloat() : default_value;
}

bool OMFLValue::AsBool() const {
    if (!IsBool()) throw std::runtime_error("Not a boolean");
    return std::get<bool>(value_);
}

bool OMFLValue::AsBoolOrDefault(bool default_value) const {
    return IsBool() ? AsBool() : default_value;
}

const std::string& OMFLValue::AsString() const {
    if (!IsString()) throw std::runtime_error("Not a string");
    return std::get<std::string>(value_);
}

std::string OMFLValue::AsStringOrDefault(const std::string& default_value) const {
    return IsString() ? AsString() : default_value;
}

const OMFLValue& OMFLValue::operator[](size_t index) const {
    if (!IsArray()) return OMFLSection::empty_value_;
    const auto& arr = std::get<std::vector<OMFLValue>>(value_);
    if (index >= arr.size()) return OMFLSection::empty_value_;
    return arr[index];
}

const OMFLValue& OMFLSection::Get(const std::string& key) const {
    auto it = values.find(key);
    if (it != values.end()) {
        return it->second;
    }
    return empty_value_;
}

void OMFLSection::AddValue(const std::string& key, OMFLValue::Value value) {
    values[key] = OMFLValue(std::move(value));
}

void OMFLSection::AddSection(const std::string& key, std::shared_ptr<OMFLSection> section) {
    sections[key] = std::move(section);
}

OMFLRoot OMFLRoot::parse(const std::string& str) {
    std::istringstream iss(str);
    OMFLRoot root;
    root.ParseStream(iss);
    return root;
}

OMFLRoot OMFLRoot::parse(const std::filesystem::path& path) {
    std::ifstream ifs(path);
    OMFLRoot root;
    if (ifs) {
        root.ParseStream(ifs);
    }
    return root;
}

bool OMFLRoot::ParseStream(std::istream& input) {
    std::string line;
    size_t line_number = 0;
    std::vector<std::string> current_section;

    auto trim = [](std::string& s) {
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int ch) { return !std::isspace(ch); }));
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int ch) { return !std::isspace(ch); }).base(), s.end());
    };

    auto remove_comments = [](std::string& s) {
        size_t pos = s.find('#');
        if (pos != std::string::npos) {
            s.erase(pos);
        }
    };

    auto is_valid_key = [](const std::string& key) {
        if (key.empty()) return false;
        for (char c : key) {
            if (!isalnum(c) && c != '-' && c != '_') return false;
        }
        return true;
    };

    while (std::getline(input, line)) {
        line_number++;
        trim(line);
        remove_comments(line);
        if (line.empty()) continue;

        if (line.front() == '[' && line.back() == ']') {
            std::string section_name = line.substr(1, line.size() - 2);
            trim(section_name);

            if (section_name.empty() || section_name.front() == '.' || section_name.back() == '.') {
                return false;
            }

            current_section = {};
            std::istringstream section_stream(section_name);
            std::string part;
            while (std::getline(section_stream, part, '.')) {
                trim(part);
                if (!is_valid_key(part)) {
                    return false;
                }
                current_section.push_back(part);
            }
        } else {
            size_t equal_pos = line.find('=');
            if (equal_pos == std::string::npos) {
                return false;
            }

            std::string key = line.substr(0, equal_pos);
            trim(key);
            if (!is_valid_key(key)) {
                return false;
            }

            std::string value_str = line.substr(equal_pos + 1);
            trim(value_str);
            if (value_str.empty()) {
                return false;
            }

            OMFLValue::Value value;
            if (value_str.front() == '"' && value_str.back() == '"') {
                value = value_str.substr(1, value_str.size() - 2);
            } else if (value_str == "true") {
                value = true;
            } else if (value_str == "false") {
                value = false;
            } else if (value_str.front() == '[' && value_str.back() == ']') {
                std::vector<OMFLValue> array;
                std::string array_content = value_str.substr(1, value_str.size() - 2);
                trim(array_content);

                if (!array_content.empty()) {
                    std::istringstream array_stream(array_content);
                    std::string element;
                    while (std::getline(array_stream, element, ',')) {
                        trim(element);
                        if (element.empty()) continue;

                        if (element.front() == '"' && element.back() == '"') {
                            array.emplace_back(element.substr(1, element.size() - 2));
                        } else if (element == "true") {
                            array.emplace_back(true);
                        } else if (element == "false") {
                            array.emplace_back(false);
                        } else if (element.find('.') != std::string::npos) {
                            float f;
                            auto result = std::from_chars(element.data(), element.data() + element.size(), f);
                            if (result.ec != std::errc() || *result.ptr != '\0') {
                                return false;
                            }
                            array.emplace_back(f);
                        } else {
                            int32_t i;
                            auto result = std::from_chars(element.data(), element.data() + element.size(), i);
                            if (result.ec != std::errc() || *result.ptr != '\0') {
                                return false;
                            }
                            array.emplace_back(i);
                        }
                    }
                }
                value = std::move(array);
            } else if (value_str.find('.') != std::string::npos) {
                float f;
                auto result = std::from_chars(value_str.data(), value_str.data() + value_str.size(), f);
                if (result.ec != std::errc() || *result.ptr != '\0') {
                    return false;
                }
                value = f;
            } else {
                int32_t i;
                auto result = std::from_chars(value_str.data(), value_str.data() + value_str.size(), i);
                if (result.ec != std::errc() || *result.ptr != '\0') {
                    return false;
                }
                value = i;
            }

            OMFLSection* current = this;
            for (const auto& section : current_section) {
                auto it = current->sections.find(section);
                if (it == current->sections.end()) {
                    current->sections[section] = std::make_shared<OMFLSection>();
                }
                current = current->sections[section].get();
            }

            if (current->values.count(key)) {
                return false;
            }

            current->AddValue(key, std::move(value));
        }
    }

    return true;
}

OMFLRoot parse(const std::string& str) {
    return OMFLRoot::parse(str);
}

OMFLRoot parse(const std::filesystem::path& path) {
    return OMFLRoot::parse(path);
}

}// namespace omfl