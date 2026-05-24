#pragma once
#include "iargument.h"
#include <iostream>
#include <string>
#include <optional>

template<typename T>
class ValueArgument : public IArgument {
public:
    std::optional<T> value;
    T default_value;
    ValueArgument(char s, const std::string& l, const std::string& d, T def_val): IArgument(s, l, d), default_value(def_val) {

    }
    bool parse(const std::vector<std::string>& args, size_t& index) override {
        if(index + 1 >= args.size()) return false;
        if(args [index + 1][0] == '-') return false;

        std::string str_val = args [++index];
        if constexpr (std::is_same_v<T, std::string>)
        {
            value = str_val;
        }
        else
        {
            value = std::stoi(str_val);
        }
        index ++ ;
        return true;
    }
    std::string get_info() const override {
        std::string info;
        info += "  -";
        info += short_name_;
        info += ", --";
        info += long_name_;
        info += "=<value>\t";
        info += description_;
        info += " (default: ";
        if constexpr (std::is_same_v<T, std::string>)
        {
            // 如果 T 本身就是 string，直接拼接
            info += default_value;
        }
        else
        {
            info += std::to_string(default_value);
        }
        info += ")";
        return info;
    }
};