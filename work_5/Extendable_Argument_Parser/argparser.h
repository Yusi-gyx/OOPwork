#pragma once
#include "flagargument.h"
#include "valueargument.h"

#include <memory>
#include <map>
#include <iostream>
#include <optional>

class ArgParser {
private:
    std::string program_description_;      //程序描述
    std::vector<std::unique_ptr<IArgument>> arguments_;    //已有参数对应的对象指针
    std::map<std::string, IArgument*> long_name_map_;    //长名称映射
    std::map<char, IArgument*> short_name_map_;   //短名称映射
    bool help_wanted_ = false;    //是否需要帮助，即传入的命令行中是否有-h参数

public:
    ArgParser(const std::string& description) : program_description_(description) {
        addFlag('h', "help", "Show this help message.");
    }

    void addFlag(char s, const std::string& l, const std::string& d) {
        auto up = std::make_unique<FlagArgument>(s, l, d);
        short_name_map_ [s] = up.get();
        long_name_map_ [l] = up.get();
        arguments_.push_back(std::move(up));
    }
    template<typename T>
    void addValue(char s, const std::string& l, const std::string& d, T def_val) {
        auto up = std::make_unique<ValueArgument<T>>(s, l, d, def_val);
        short_name_map_ [s] = up.get();
        long_name_map_ [l] = up.get();
        arguments_.push_back(std::move(up));
    }

    bool parse(int argc, char* argv[]) {
        std::vector<std::string> args(argv, argv + argc);
        for(size_t i = 1 ; i < args.size() ;)
        {
            int type = 0 ;
            for(auto x: args [i])
            {
                if(x == '-') type ++ ;
                else break;
            }

            //消除前面的-
            args [i].erase(0, type);

            if(type == 2)   //长参数
            {
                if(long_name_map_.find(args [i]) == long_name_map_.end())
                {
                    if(args [i].size() > 5)   //level后面直接跟等号的情况
                    {
                        std::string check_level;
                        for(int j = 0 ; j < 5 ; j ++) check_level += args [i][j];
                        if(check_level == "level" && args[i][5] == '=') 
                        {
                            auto *val_ptr = dynamic_cast<ValueArgument<int>*>(long_name_map_.find("level")->second);
                            std::string num;
                            for(int j = 6; j < args [i].size() ; j ++) num += args [i][j];
                            val_ptr->value = stoi(num);
                            i ++ ;
                        }
                        else
                        {
                            std::cout << "Error: Unknown argument: --" << args [i] << std::endl;
                            return false;
                        }
                    }
                    else
                    {
                        std::cout << "Error: Unknown argument: --" << args [i] << std::endl;
                        return false;
                    }
                }
                else
                {
                    if(long_name_map_.find(args [i])->second->is_flag())  //这个参数是标志参数
                    {
                        if(args [i] == "help") help_wanted_ = true;
                        long_name_map_[args [i]]->parse(args, i);
                    }
                    else   //是值参数
                    {
                        if(!long_name_map_[args [i]]->parse(args, i))
                        {
                            std::cout << "Error: Argument " << long_name_map_[args [i]]->long_name_ << " requires a value." << std::endl;
                            return false;
                        }
                    }
                }
            }
            else      //短参数
            {
                if(short_name_map_.find(args [i][0]) == short_name_map_.end())
                {
                    std::cout << "Error: Unknown argument: -" << args [i] << std::endl;
                    return false;
                }
                else
                {
                    if(short_name_map_[args [i][0]]->is_flag())   //标志参数
                    {
                        if(args [i] == "h") help_wanted_ = true;
                        short_name_map_[args [i][0]]->parse(args, i);
                    }
                    else   //值参数
                    {
                        if(!short_name_map_[args [i][0]]->parse(args, i))
                        {
                            std::cout << "Error: Argument " << short_name_map_[args [i][0]]->long_name_ << " requires a value." << std::endl;
                            return false;
                        }
                    }
                }
            }
        }
        return true;
    }

    template<typename T>
    std::optional<T> get(const std::string& name) const {
        auto it = long_name_map_.find(name);
        if(it == long_name_map_.end()) return std::nullopt;

        IArgument* base_arg = long_name_map_.find(name)->second;

        if (auto *val_arg = dynamic_cast<ValueArgument<T> *>(base_arg))
        {
            // 如果有值就返回输入值，否则返回默认值
            return val_arg->value.value_or(val_arg->default_value);
        }
        if constexpr (std::is_same_v<T, bool>)
        {
            if (auto *flag_arg = dynamic_cast<FlagArgument *>(base_arg))
            {
                return flag_arg->value;
            }
        }

        return std::nullopt;
    }

    bool wantsHelp() const { return help_wanted_; }
    void printHelp() const {
        std::cout << program_description_ << "\n\nUsage:\n";
        for (const auto& arg : arguments_) {
            std::cout << arg->get_info() << std::endl;
        }
    }
};