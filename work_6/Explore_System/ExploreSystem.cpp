#include "ExploreSystem.h"

Player::Player(const std::string& toolName_) : toolName(toolName_) {}

std::string Player::getToolName() const {
    return toolName;
}

void Player::sealTool() {
    isSealed = true;
}

bool Player::isToolSealed() const {
    return isSealed;
}

int Player::toolScore() const {
    if (isSealed) {
        return 0;
    }

    if (toolName == "torch") {
        return 10;
    }
    if (toolName == "map") {
        return 15;
    }
    if (toolName == "compass") {
        return 12;
    }

    return 5;
}

SwordPlayer::SwordPlayer(float power_, const std::string& toolName_)
    : Player(toolName_), power(power_) {}

void SwordPlayer::weaponEnhanced() {
    power *= 1.5f;
}

float SwordPlayer::weaponScore(int level) const {
    return power * level;
}

StaffPlayer::StaffPlayer(float magic_, const std::string& toolName_)
    : Player(toolName_), magic(magic_) {}

void StaffPlayer::weaponEnhanced() {
    magic *= 2.0f;
}

float StaffPlayer::weaponScore(int level) const {
    return magic * (level + 2);
}

DaggerPlayer::DaggerPlayer(float sharpness_, const std::string& toolName_)
    : Player(toolName_), sharpness(sharpness_) {}

void DaggerPlayer::weaponEnhanced() {
    sharpness *= 1.2f;
}

float DaggerPlayer::weaponScore(int level) const {
    return sharpness * level * 0.8f;
}

Dungeon::Dungeon(int level_) : level(level_) {}

int Dungeon::getLevel() const {
    return level;
}

NormalDungeon::NormalDungeon(int level_) : Dungeon(level_) {}

float NormalDungeon::startExplore(Player* player) {
    if (player == nullptr) {
        return 0.0f;
    }

    return player->weaponScore(getLevel()) + player->toolScore();
}

ToolSealDungeon::ToolSealDungeon(int level_) : Dungeon(level_) {}

float ToolSealDungeon::startExplore(Player* player) {
    if (player == nullptr) {
        return 0.0f;
    }

    player->sealTool();
    return player->weaponScore(getLevel()) + player->toolScore();
}

WeaponEnhancedDungeon::WeaponEnhancedDungeon(int level_) : Dungeon(level_) {}

float WeaponEnhancedDungeon::startExplore(Player* player) {
    if (player == nullptr) {
        return 0.0f;
    }

    player->weaponEnhanced();
    return player->weaponScore(getLevel()) + player->toolScore();
}

Player* createPlayer(const std::string& weaponName, float weaponValue, const std::string& toolName) {
    if (weaponName == "sword") {
        return new SwordPlayer(weaponValue, toolName);
    }
    if (weaponName == "staff") {
        return new StaffPlayer(weaponValue, toolName);
    }
    if (weaponName == "dagger") {
        return new DaggerPlayer(weaponValue, toolName);
    }

    return nullptr;
}

Dungeon* createDungeon(const std::string& dungeonName, int level) {
    if (dungeonName == "normal") {
        return new NormalDungeon(level);
    }
    if (dungeonName == "toolseal") {
        return new ToolSealDungeon(level);
    }
    if (dungeonName == "weaponenhance") {
        return new WeaponEnhancedDungeon(level);
    }

    return nullptr;
}
