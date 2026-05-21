# STL 容器与迭代器学习笔记

> 基于 `STL_utilization` 项目代码总结

---

## 一、程序架构概览

```
BasicContainer.h   —— 抽象基类，定义接口（使用 std::pair 作为坐标）
Container.h        —— 两个模板特化实现（vector 版本 / map 版本）
main.cpp           —— 运行时多态调度，根据用户输入选择底层容器
```

程序实现了一个**二维坐标到值的映射容器**，支持 `insert` 和 `find` 操作。核心设计亮点是：同样的接口（`BasicContainer<A>`），底层可以用 `vector` 或 `map` 两种 STL 容器实现，通过模板特化在编译期选择策略。

---

## 二、使用的 STL 容器

### 2.1 `std::pair` —— 坐标抽象

```cpp
// BasicContainer.h
#include <utility>
typedef std::pair<int, int> Pos;
```

- `std::pair` 将两个 int 捆绑为一个二维坐标 `Pos`。
- 自带默认的 `operator<`（先比 first，再比 second），这使得 `Pos` 可直接作为 `std::map` 的 key。
- 在 `main.cpp` 中使用 `make_pair(x, y)` 构造坐标。

**关键知识点：** `std::pair` 是 STL 中最基础的工具类模板，常用于：
- 关联容器的键类型（如此处的 `map<Pos, A>`）
- 函数返回多个值
- 算法中的中间数据结构

### 2.2 `std::vector` —— 序列容器（动态数组）

```cpp
// Container.h — vector 特化版本
template <class A>
class Container<A, vector<A> > : public BasicContainer<A> {
    vector< Point<A> > base;   // 存储 Point 对象的动态数组
    // ...
};
```

**在这个程序中的使用方式：**

| 操作 | 代码 | 说明 |
|------|------|------|
| 尾部插入 | `base.push_back(Point<A>(p, v))` | O(1) 均摊，不关心顺序 |
| 获取首迭代器 | `base.begin()` | 指向第一个元素 |
| 获取尾后迭代器 | `base.end()` | 指向最后一个元素之后 |

**设计决策——延迟排序（Lazy Sort）：**
- `insert` 时直接 `push_back`，不管顺序 —— O(1)
- 第一次 `find` 时才调用 `std::sort` 排序，之后用 `std::lower_bound` 二分查找
- 用 `bool sorted` 标记避免重复排序

### 2.3 `std::map` —— 关联容器（红黑树）

```cpp
// Container.h — map 特化版本
template<class A, class C>
class Container : public BasicContainer<A> {
    map<Pos, A> base;   // 以 Pos 为键、A 为值的红黑树
public:
    void insert(const Pos &p, const A &v) {
        base[p] = v;   // map::operator[]
    }
    A* find(Pos p) {
        auto it = base.find(p);   // map::find
        if(it != base.end()) return &(it->second);
        else return nullptr;
    }
};
```

**在这个程序中的使用方式：**

| 操作 | 代码 | 时间复杂度 |
|------|------|-----------|
| 插入/更新 | `base[p] = v` | O(log n) |
| 查找 | `base.find(p)` | O(log n) |

**关键知识点：**
- `operator[]` 在 key 不存在时会**默认构造**一个 value 并插入；若 key 已存在则**覆盖**。语义偏"有则改之，无则加之"。
- `find()` 返回迭代器，key 不存在时返回 `end()`，不会插入新元素。
- 迭代器指向 `std::pair<const Pos, A>`，所以通过 `it->second` 获取值。

### 2.4 `std::string` 

```cpp
// main.cpp
string base, type;   // 用户输入的容器类型和数据类型
string act;          // 用户输入的操作类型（"insert" / "find"）
```

使用 `std::string` 存储用户输入，配合 `cin >>` 读取。

---

## 三、使用的 STL 迭代器

STL 迭代器的设计哲学：**提供统一的访问接口，使算法与容器解耦**。

### 3.1 map 的迭代器

```cpp
auto it = base.find(p);
if(it != base.end()) return &(it->second);
```

- `map::find()` 返回一个**双向迭代器**（Bidirectional Iterator）
- `it != base.end()` — 与尾后迭代器比较，判断是否找到
- `it->second` — 通过迭代器访问 `pair` 的 value。等价于 `(*it).second`

### 3.2 vector 的迭代器（配合算法使用）

```cpp
// sort 算法接收迭代器范围
std::sort(base.begin(), base.end());

// lower_bound 返回迭代器
auto low = std::lower_bound(
    base.begin(), base.end(), p,
    [](const Point<A> target, const Pos obj) {
        return target.pos < obj;
    }
);

// 迭代器比较与解引用
if(low != base.end() && low->pos == p) return &(low->value);
```

- `base.begin()` / `base.end()` 返回**随机访问迭代器**（Random Access Iterator）—— 这是 vector 独有的优势
- `auto low` — 用 `auto` 自动推导迭代器类型，简化代码
- `low->pos` — 迭代器直接访问成员，等价于 `(*low).pos`
- `low != base.end()` — 判断 `lower_bound` 是否找到有效位置

### 3.3 被注释掉的遍历代码（值得一看）

```cpp
// for(auto t = base.begin(); t != base.end(); ++t) {
//     if(p == t->pos) return &(t->value);
// }
// return NULL;
```

这段展示了最经典的迭代器遍历范式：
- 从 `begin()` 开始，到 `end()` 结束
- 使用 `!=` 而非 `<` 比较（所有迭代器都支持 `!=`，只有随机访问迭代器支持 `<`）
- `++t` 前置递增（比后置 `t++` 少一次临时拷贝）
- 这个 O(n) 的线性查找被 O(log n) 的 `lower_bound` 二分查找替代

---

## 四、使用的 STL 算法

### 4.1 `std::sort` —— 排序

```cpp
std::sort(base.begin(), base.end());
```

- 默认使用 `operator<` 比较。此处 `Point<A>` 已重载了 `operator<`，比较的是 `pos` 成员。
- 时间复杂度 O(n log n)，要求迭代器为随机访问迭代器。
- **只有 vector 能用 `std::sort`**，因为 map 本身就是有序的。

### 4.2 `std::lower_bound` —— 二分查找

```cpp
auto low = std::lower_bound(
    base.begin(), base.end(), p,
    [](const Point<A> target, const Pos obj) {
        return target.pos < obj;
    }
);
```

- 在**有序**序列中二分查找第一个 `>= p` 的位置
- 使用自定义 lambda 比较函数，只比较 `Point.pos` 和 `Pos`
- 查找后需要额外判断：`low != base.end() && low->pos == p`
- 时间复杂度 O(log n)，要求迭代器为随机访问迭代器

> **为什么 map 不需要这些算法？** 因为 map 底层是红黑树，自带 O(log n) 的 `find()` 方法。

---

## 五、两种实现策略对比

| 特性 | vector 版本 | map 版本 |
|------|------------|----------|
| 底层数据结构 | 动态数组 | 红黑树 |
| insert 复杂度 | O(1) push_back（懒排序） | O(log n) |
| find 复杂度 | O(n log n) 首次（含排序）<br>O(log n) 后续 | O(log n) 每次 |
| 是否有序 | 延迟排序（lazy sort） | 始终保持有序 |
| 适用场景 | 插入多、查找少 | 插入和查找频繁交叉 |
| 空间开销 | 紧凑，无额外指针 | 每个节点有额外指针开销 |
| 迭代器类型 | **随机访问** | 双向 |

---

## 六、核心学习要点

1. **容器选型取决于操作模式**：vector 适合"先批量插入，后批量查询"；map 适合"插入和查询交替进行"。这个程序用模板特化优雅地展示了两种策略。

2. **迭代器是算法与容器之间的桥梁**：`std::sort` 和 `std::lower_bound` 不关心容器是 vector 还是数组，只要提供随机访问迭代器即可。

3. **`auto` + 迭代器是绝配**：`auto it = base.find(p)` 省去了写 `map<Pos, A>::iterator` 的繁琐。

4. **延迟策略是常见的性能优化**：vector 版本不在每次 insert 时维护有序性，而是推迟到首次 find 时一次性排序。类似的思想在数据库索引、游戏引擎中都很常见。

5. **模板特化 + 多态**：通过 `BasicContainer<A>` 抽象基类实现运行时多态，通过 `Container<A, vector<A>>` 部分特化实现编译期策略选择，两者结合非常灵活。
