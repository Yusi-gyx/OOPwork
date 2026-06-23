#pragma once
#include <algorithm>
#include <iostream>
#include <map>
#include <numeric>
#include <string>
#include <vector>
using namespace std;

template<class T>
struct AgentRecord {
    int id;
    string role;
    T content;
    int tokens;
    AgentRecord() = default;
    AgentRecord(int id_, string role_, T content_, int tokens_):id(id_), role(role_), content(content_), tokens(tokens_) {}
};

template<class T, int W>
class AgentTrace {
    vector<AgentRecord<T>> records;
public:
    AgentTrace() {}
    AgentTrace(const vector<string>& roles,
               const vector<T>& contents = vector<T>(),
               const vector<int>& tokens = vector<int>())
    {
        for(int i = 0 ; i < roles.size() ; i ++)
        {
            AgentRecord<T> temp;
            temp.id = i;
            temp.role = roles [i];
            temp.tokens = 1;
            records.push_back(temp);
        }
        if(contents.size() == 0) for(auto& x: records) x.content = T();
        else
        {
            for(int i = 0; i < contents.size() ; i ++) records [i].content = contents[i];
        }
        if(tokens.size() == 0) for(auto& x: records) x.tokens = 1;
        else
        {
            for(int i = 0; i < tokens.size(); i ++) records [i].tokens = tokens [i];
        }
    }

    int getId(int index) const {return records [index].id;}
    int getSize() const {return records.size();}
    const string& getRole(int id) const {return records [id].role;}
    int getTokens(int id) const {return records [id].tokens;}
    int add(const string& role, const T& content, int tokens = 1)
    {
        AgentRecord<T> new_record;
        new_record.id = records.empty() ? 0 : records.back().id + 1;
        new_record.role = role;
        new_record.content = content;
        new_record.tokens = tokens;
        records.push_back(new_record);
        return new_record.id;
    }
    void set(int id, const T& content)
    {
        records [id].content = content;
    }
    const T& get(int id) const
    {
        return records [id].content;
    }
    T& get(int id)
    {
        return records [id].content;
    }
    vector<int> ids(const string& role) const
    {
        vector<int> id_set;
        for(auto x: records)
        {
            if(x.role == role) id_set.push_back(x.id);
        }
        return id_set;
    }
    int token_sum() const
    {
        int sum = 0;
        for(auto x: records)
            sum += x.tokens;
        return sum;
    }

    bool operator==(const AgentTrace& other) const
    {
        if(records.size() != other.records.size()) return false;
        for(int i = 0 ; i < records.size() ; i ++)
        {
            if(records [i].id != other.records [i].id) return false;
            if(records [i].role != other.records [i].role) return false;
            if(records [i].content != other.records [i].content) return false;
            if(records [i].tokens != other.records [i].tokens) return false;
        }
        return true;
    }
    bool operator!=(const AgentTrace& other) const
    {
        return !(*this == other);
    }
    AgentTrace& operator=(const AgentTrace& other)
    {
        if(*this == other) return *this;
        records = other.records;
        return *this;
    }

    class Iterator {
        //嵌套类中储存有外部vector的一个迭代器，实现对vector迭代器的封装
        typename vector<AgentRecord<T>>::iterator it;
    public:
        Iterator() = default;
        Iterator(typename vector<AgentRecord<T>>::iterator _it):it(_it) {} 
        T& operator*() const
        {
            return it -> content;
        }
        Iterator& operator++()
        {
            it ++;
            return *this;
        }
        Iterator operator++(int)
        {
            Iterator new_iter = *this;
            it ++;
            return new_iter;
        }
        bool operator==(const Iterator& other) const
        {
            return it == other.it;
        }
        bool operator!=(const Iterator& other) const
        {
            return it != other.it;
        }
        Iterator& operator=(const Iterator& other)
        {
            it = other.it;
            return *this;
        }
    };

    Iterator begin()
    {
        return Iterator(records.begin());
    }
    Iterator end()
    {
        return Iterator(records.end());
    }

    T& operator[](int id)
    {
        return records [id].content;
    }

    class RoleView {
        AgentTrace* obj;
        string target_role;
    public:
        RoleView() = default;
        RoleView(AgentTrace* obj_, const string& role): obj(obj_), target_role(role) {}
        T& operator[](int index)
        {
            vector<int> idset = obj->ids(target_role);
            return obj->get(idset [index]);
        }
    };

    RoleView operator[](const string& role)
    {
        RoleView proxy(this, role);   //构造自己的代理类
        return proxy;
    }

    void compact()
    {
        int current_tokens = 0;
        // 从后往前遍历
        for (int i = records.size() - 1; i >= 0; i--)
        {
            current_tokens += records[i].tokens;
            if (current_tokens > W)
            {
                // 一旦超标，把从开头到当前位置 i 的所有记录全部删掉
                records.erase(records.begin(), records.begin() + i + 1);
                return;
            }
        }
    }

    //retrieve操作补充结构体和比较函数
    struct Content
    {
        int id;
        T content;
        int score;
        Content(int id_, T content_, int score_): id(id_), content(content_), score(score_) {}
        bool operator<(const Content& other) const 
        {
            if(score == other.score)
            {
                return id < other.id;
            }
            else return score > other.score;
        }
    };

    template<class ScoreFunc>
    vector<T> retrieve(int k, ScoreFunc Score) const
    {
        vector<T> retrieve_record;
        vector<Content> temp;
        
        // 构建临时打分数组
        for (const auto& x : records)
        {
            temp.emplace_back(x.id, x.content, Score(x.content));
        }
        
        // 统一排序
        sort(temp.begin(), temp.end());
        
        // 取 k 和实际数量的较小值，避免越界
        int limit = std::min(k, (int)temp.size());
        for(int i = 0 ; i < limit ; i ++)
        {
            retrieve_record.push_back(temp[i].content);
        }
        
        return retrieve_record;
    }

    map<string, int> tool_stats() const
    {
        map<string, int> stats;
        for(const auto& x: records) 
        {
            // 确保长度大于5，并且前5个字符是 "tool:"
            if(x.role.size() > 5 && x.role.substr(0, 5) == "tool:")
            {
                // 提取从索引 5 开始的工具名称
                string tool_name = x.role.substr(5);
                stats[tool_name]++;
            }
        }
        return stats;
    }
};

template<class T, int W>
ostream& operator<<(ostream& os, const AgentTrace<T, W>& trace)
{
    for(int i = 0 ; i < trace.getSize(); i ++)
    {
        os << "#" << trace.getId(i) << " [" << trace.getRole(i) << "] (" << trace.getTokens(i) << ") " << trace.get(i);
        if(i != trace.getSize() - 1) os << endl;
    }
    return os;
}
