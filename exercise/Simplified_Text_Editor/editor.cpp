#include "editor.h"
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

void TextEditor::move(Position dest)
{
    int row = dest.first;
    int col = dest.second;
    int max_row = data.size();   //最大行数
    int max_col = 0;
    if(row >= max_row) 
    {
        lighter.first = max_row - 1;
        max_col = data [max_row - 1].size();
    }
    else if(row < 0) 
    {
        lighter.first = 0;
        max_col = data [0].size();
    }
    else 
    {
        lighter.first = row;
        max_col = data [row].size();
    }

    if(col >= max_col)
    {
        lighter.second = max_col;
    }
    else if(col < 0)
    {
        lighter.second = 0;
    }
    else 
    {
        lighter.second = col;
    }
}

void TextEditor::write(const std::string &str)
{
    data_record.push_back(data);
    lighter_record.push_back(lighter);

    int add_size = str.size(); //加入长度
    for(int i = 0 ; i < add_size; i ++)
    {
        data [lighter.first].insert(data [lighter.first].begin() + lighter.second, str [i]);
        lighter.second ++;
    }
}

void TextEditor::newline()
{
    data_record.push_back(data);
    lighter_record.push_back(lighter);

    std::string next_line = data [lighter.first].substr(lighter.second);
    data [lighter.first].erase(data [lighter.first].begin() + lighter.second, data[lighter.first].end());
    data.insert(data.begin() + (lighter.first + 1), next_line);

    lighter.first ++;
    lighter.second = 0;
}

void TextEditor::del()
{
    if(lighter.first == 0 && lighter.second == 0)
    {
        return;
    }

    data_record.push_back(data);
    lighter_record.push_back(lighter);

    if(lighter.second == 0)   //若光标在一行的开头
    {
        lighter.second = data  [lighter.first - 1].size();
        data [lighter.first - 1] += data [lighter.first];
        data.erase(data.begin() + lighter.first);
        lighter.first --;
        return ;
    }
    //普通情况下删除前一个字符
    data [lighter.first].erase(data [lighter.first].begin() + (lighter.second - 1));
    lighter.second --;
}

void TextEditor::undo()
{
    if(data_record.empty()) return;

    data = data_record.back();
    lighter = lighter_record.back();

    data_record.pop_back();
    lighter_record.pop_back();
}

void TextEditor::screenShot()
{
    std::cout << "### SCREENSHOT BEGIN ###" << std::endl;

    for(int i = 0 ; i < data.size(); i ++)
    {
        if(i == lighter.first)
        {
            for(int j = 0 ; j < data [i].size(); j ++)
            {
                if(j == lighter.second)
                {
                    std::cout << "*" ;
                }
                std::cout << data[i][j];
            }
            if(lighter.second >= data[i].size()) std::cout << "*";
            std::cout << std::endl;
        }
        else
        {
            std::cout << data [i] << std::endl;
        }
    }

    std::cout << "### SCREENSHOT END ###" << std::endl;
}

void TextEditor::apply(const std::string& opt)
{
    std::stringstream ss;
    ss << opt;
    std::string cmd;
    ss >> cmd;
    if(cmd == "MOVE")
    {
        int row, col;
        ss >> row >> col;
        Position dest = {row, col};
        move(dest);
    }
    else if(cmd == "WRITE")
    {
        std::string text;
        std::getline(ss, text);
        if(!text.empty()) text.erase(text.begin());
        write(text);
    }
    else if(cmd == "NEWLINE")
    {
        newline();
    }
    else if(cmd == "DELETE")
    {
        del();
    }
    else if(cmd == "UNDO")
    {
        undo();
    }
    else   //SCREEN
    {
        screenShot();
    }
}