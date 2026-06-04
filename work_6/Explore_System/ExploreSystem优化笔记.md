# ExploreSystem 设计优化笔记

## 1. 明确 `Player` 的公共能力

原来的 `Player` 保存了工具名和封印状态，但外部没有清晰接口操作这些状态。现在将工具相关能力集中到 `Player` 中：

- `getToolName()`：查询工具名；
- `sealTool()`：封印工具；
- `isToolSealed()`：查询工具是否被封印；
- `toolScore()`：根据工具状态计算工具得分。

这样 `ToolSealDungeon` 不需要直接访问玩家内部成员，只需要调用 `player->sealTool()`，封装性更好。

## 2. 统一武器分数接口

三种玩家都通过同一组虚函数表达武器能力：

- `weaponEnhanced()`：强化武器；
- `weaponScore(int level) const`：根据地牢等级计算武器分数。

这样地牢不需要判断玩家具体是剑士、法师还是匕首玩家，只需要通过 `Player*` 调用统一接口，体现多态。

## 3. 让 `DaggerPlayer` 也拥有武器数值

工厂函数 `createPlayer(weaponName, weaponValue, toolName)` 表示每种武器都应该接收一个武器数值。原设计中 `DaggerPlayer` 没有保存这个数值，会导致传入的 `weaponValue` 被忽略。

现在为 `DaggerPlayer` 增加 `sharpness` 成员，使三种玩家都能使用工厂函数传入的武器数值。

## 4. 区分“修改状态”和“查询分数”

`weaponEnhanced()` 会改变玩家的武器属性，例如提高力量、魔力或锋利度；`weaponScore(int level) const` 只负责查询分数，不修改对象。

因此 `weaponScore()` 和 `toolScore()` 被设计为 `const` 函数，表示它们只是计算结果，不改变玩家状态。

## 5. 地牢只负责地牢规则

三种地牢的职责被分开：

- `NormalDungeon`：普通探索，直接计算武器分数和工具分数；
- `ToolSealDungeon`：先封印工具，再计算奖励；
- `WeaponEnhancedDungeon`：先强化武器，再计算奖励。

这样玩家负责自身能力，地牢负责探索规则，职责更加清晰。

## 6. 保持和现有 `main.cpp` 兼容

本次修改仍然保留裸指针工厂函数：

```cpp
Player* createPlayer(const std::string& weaponName, float weaponValue, const std::string& toolName);
Dungeon* createDungeon(const std::string& dungeonName, int level);
```

这样现有 `main.cpp` 中的 `delete player; delete dungeon;` 可以继续工作。如果后续学习到智能指针，可以进一步改为 `std::unique_ptr`，减少手动内存管理。
