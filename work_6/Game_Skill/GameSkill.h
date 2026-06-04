#pragma once
#include "LegacySkill.h"

class ISkill {
public:
    virtual int cast() = 0;
    virtual ~ISkill() {}
};

class LegacySkillAdapter: public ISkill {
    LegacySkill *legacyskill;
public:
    LegacySkillAdapter(LegacySkill *lk): legacyskill(lk) {}
    int cast() override;
};

class MpChecker: public ISkill{
    ISkill* system;
    int mpCost;
    int currentMp;
public:
    MpChecker(ISkill *system_, int mpInit, int mpCost_): system(system_), mpCost(mpCost_), currentMp(mpInit) {}
    int cast() override;
};

class CritBuff: public ISkill {
    ISkill *skill;
public:
    CritBuff(ISkill *skill_): skill(skill_) {}
    int cast() override;
};

class PoisonBuff: public ISkill {
    ISkill* skill;
public:
    PoisonBuff(ISkill *skill_):skill(skill_) {}
    int cast() override;
};