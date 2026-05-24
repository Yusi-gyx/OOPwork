#pragma once
#include "iargument.h"
#include <iostream>

class FlagArgument : public IArgument {
public:
    bool value = false;
    FlagArgument(char s, const std::string& l, const std::string& d): IArgument(s, l, d) {
        
    }
    bool parse(const std::vector<std::string>& args, size_t& index) override {
        value = true;
        index ++;
        return true;
    }
    std::string get_info() const override {
        std::string info;
        info += "  -";
        info += short_name_;
        info += ", --";
        info += long_name_;
        info += "\t\t";
        info += description_;
        return info;
    }

    bool is_flag() const override {
        return true;
    }
};