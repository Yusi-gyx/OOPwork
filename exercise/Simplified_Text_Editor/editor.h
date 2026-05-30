#ifndef Editor_H
#define Editor_H

#include <vector>
#include <string>

// 你可以根据需要修改此文件

class TextEditor
{
private:
    using Position = std::pair<int, int>;
    std::vector<std::string> data;
    std::pair<int, int> lighter;     //光标的位置
    std::vector<std::vector<std::string>> data_record;   //记录历史文本
    std::vector<std::pair<int, int>> lighter_record;
public:
    TextEditor()
    {
        lighter = {0, 0};
        data.push_back("");
        data_record.push_back(data);
        lighter_record.push_back(lighter);
    }
    void move(Position dest);
    void write(const std::string &str);
    void newline();
    void del();
    void screenShot();
    void undo();
    void apply(const std::string &opt);
};

#endif // Editor_H