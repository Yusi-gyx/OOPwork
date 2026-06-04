#pragma once

#include <string>

class Player {
    std::string toolName;
    bool isSealed = false;

public:
    explicit Player(const std::string& toolName_);
    virtual ~Player() {}

    std::string getToolName() const;
    void sealTool();             //设置是否工具被隐藏
    bool isToolSealed() const;   //返回isSealed
    int toolScore() const;       //工具得分

    virtual void weaponEnhanced() = 0;            //武器强化
    virtual float weaponScore(int level) const = 0;        //武器得分
};

class SwordPlayer : public Player {
    float power;

public:
    SwordPlayer(float power_, const std::string& toolName_);
    void weaponEnhanced() override;
    float weaponScore(int level) const override;
};

class StaffPlayer : public Player {
    float magic;

public:
    StaffPlayer(float magic_, const std::string& toolName_);
    void weaponEnhanced() override;
    float weaponScore(int level) const override;
};

class DaggerPlayer : public Player {
    float sharpness;

public:
    DaggerPlayer(float sharpness_, const std::string& toolName_);
    void weaponEnhanced() override;
    float weaponScore(int level) const override;
};

class Dungeon {
    int level;

public:
    explicit Dungeon(int level_);
    virtual ~Dungeon() {}

    int getLevel() const;
    virtual float startExplore(Player* player) = 0;
};

class NormalDungeon : public Dungeon {
public:
    explicit NormalDungeon(int level_);
    float startExplore(Player* player) override;
};

class ToolSealDungeon : public Dungeon {
public:
    explicit ToolSealDungeon(int level_);
    float startExplore(Player* player) override;
};

class WeaponEnhancedDungeon : public Dungeon {
public:
    explicit WeaponEnhancedDungeon(int level_);
    float startExplore(Player* player) override;
};

Player* createPlayer(const std::string& weaponName, float weaponValue, const std::string& toolName);
Dungeon* createDungeon(const std::string& dungeonName, int level);
