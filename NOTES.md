# 一、C++ 内存管理与智能指针

## 1 为什么需要内存管理？

C++ 常见的动态内存使用方式：

- `new` 分配内存
- `delete` 释放

典型风险：

- 忘记释放 → 内存泄漏（memory leak）
- 过早释放/重复释放 → 悬空指针（dangling pointer）

为了解决“资源在何时释放、由谁释放”的问题，C++ 常用 **RAII（Resource Acquisition Is Initialization）** 的思路：

- 资源在对象构造时获取
- 资源在对象析构时自动释放

## 2 三种智能指针

### `std::unique_ptr`

核心想法：同一时刻只有一个所有者（owner）。

```cpp
std::unique_ptr<int> p = std::make_unique<int>(10);
```

实现要点：

- 内部保存裸指针
- 析构时自动 `delete`

使用特性：

- 不能拷贝（copy）
- 可以移动（move），用来转移所有权

示例：

```cpp
auto p2 = p1;                // ❌ 不允许拷贝
auto p2 = std::move(p1);     // ✅ 转移所有权
```

### `std::shared_ptr`

核心想法：多个指针共享同一对象的所有权。

实现要点：

- 维护引用计数（reference count）
- 引用计数归零时释放对象

示例：

```cpp
auto p1 = std::make_shared<int>(10);
auto p2 = p1;   // 引用计数 +1
```

### `std::weak_ptr`

核心想法：不拥有对象，只是“观察”一个由 `shared_ptr` 管理的对象。

动机：避免 `shared_ptr` 的循环引用导致无法释放。

循环引用示例（会泄漏）：

```cpp
shared_ptr<A> a;
shared_ptr<B> b;

a->b = b;
b->a = a;  // ❌ 循环引用，引用计数无法归零
```

常见做法：把其中一端改为 `weak_ptr`，打破所有权环。

| 指针 | 是否拥有对象 | 典型用途 |
| --- | --- | --- |
| unique_ptr | 独占 | 明确唯一所有者 |
| shared_ptr | 共享 | 共享生命周期 |
| weak_ptr | 不拥有 | 避免循环引用、做缓存/观察者 |

# 二、类之间的关系

### 1) Dependency（依赖）

“临时用一下”。通常表现为函数参数、局部变量。

例子：打印机在 `print` 中临时使用文档。

```cpp
class Document {};

class Printer {
public:
	void print(Document& doc) {
		// 使用 doc，用完结束
	}
};
```

### 2) Association（关联）

“彼此知道对方存在”，但生命周期互不绑定。

例子：学生和课程。

```cpp
class Course;

class Student {
	Course* course;
public:
	void enrollCourse(Course* c) { course = c; }
};

class Course {
	Student* student;
};
```

### 3) Aggregation（聚合）

“整体-部分”，但“部分”可以脱离“整体”独立存在。

例子：球队与球员（球员可以转会）。

```cpp
class Player {
public:
	std::string name;
};

class Team {
	std::vector<Player*> players;
public:
	void addPlayer(Player* p) { players.push_back(p); }
};
```

### 4) Composition（组合）

“整体-部分”，并且生命周期绑定：整体销毁，部分也随之销毁。

例子：汽车与引擎。

```cpp
class Engine {
public:
	void start() {}
};

class Car {
	Engine engine;
public:
	void drive() { engine.start(); }
};
```

| 关系 | 关键词 | 常见代码形态 |
| --- | --- | --- |
| Dependency | 用一下 | 参数/局部变量 |
| Association | 互相知道 | 成员指针/引用（不强调拥有） |
| Aggregation | 有，但可独立 | 成员指针，外部管理生命周期 |
| Composition | 生死与共 | 成员对象（按值持有） |

# 三、继承（Inheritance）

## 1 作用

- 代码复用
- 建立层次结构

## 2 语法

```cpp
class Derived : public Base {};
```

## 3 访问控制

| 关键字 | 含义 |
| --- | --- |
| public | 外部可见 |
| protected | 派生类可访问 |
| private | 仅类内部可访问 |

# 四、多态（Polymorphism）

## 1 多态的直观理解

同一接口，不同实现。

## 2 两种多态

- 编译期（compile-time）：函数重载、模板
- 运行期（runtime）：虚函数（virtual function）

## 3 动态绑定（Dynamic Binding）

调用在运行时根据对象实际类型决定。

示例：

```cpp
Base* p = new Derived();
p->foo();
```

- `foo` 是 `virtual`：调用 `Derived::foo()`
- `foo` 不是 `virtual`：调用 `Base::foo()`

## 4 定义

```cpp
virtual void foo();
```

## 5 重写（override）

- 基类函数为 `virtual`
- 派生类函数签名一致（返回类型、参数列表、cv 限定(const, volatile)等）

# 五、虚函数（Virtual Function）

## 机制（概念层面）

常见实现使用 vtable（虚函数表）：

- 对象内部持有一个指向 vtable 的指针
- vtable 存放虚函数入口地址

## 常见注意/容易混淆点

- 如果基类函数不是 `virtual`，就不会触发运行期多态
- 函数名相同但参数不同，属于重载或隐藏，不是重写

## 构造与析构（继承场景）

### 构造顺序

Base → Derived

### 析构顺序

Derived → Base

### 虚析构函数

当用“基类指针指向派生类对象”并通过基类指针 `delete` 时，通常需要基类析构函数为 `virtual`，以确保派生类部分能正确析构：

```cpp
Base* p = new Derived();
delete p;
```

# 六、抽象类（Abstract Class）

## 定义

```cpp
virtual void foo() = 0;
```

## 特点

- 不能直接实例化
- 派生类需要实现纯虚函数，才能实例化
- 常用于表达接口（interface）

## Overriding vs Hiding

- overriding：基类 `virtual` + 派生类同签名重写 → 运行期多态
- hiding：派生类声明了同名函数（但不满足重写条件）→ 基类同名函数可能被隐藏

# 七、Qt GUI

## 1 事件驱动（Event-driven programming）

程序不是按固定步骤线性执行，而是：

- 事件发生
- 触发对应的处理逻辑

## 2 Signals & Slots

- signal：事件
- slot：响应函数

连接示例：

```cpp
connect(button, &QPushButton::clicked, this, &MyClass::handleClick);
```

直观类比：观察者模式（Observer pattern），优点是解耦（loose coupling）。

## 3 常见组件

- QWidget（基础类）
- QPushButton
- QLabel
- QLineEdit

## 4 布局（Layout）

- QVBoxLayout
- QHBoxLayout
- QGridLayout

## 5 Qt 的内存管理：parent-child

```cpp
child = new QWidget(parent);
```

通常：parent 销毁时会自动销毁 child，减少手动 `delete` 的需求。

## 6 QTimer

用于定时触发：

- 定时到 → 发出 signal → slot 执行

## 7 Designer vs Code

| 方式 | 特点 |
| --- | --- |
| Designer | 搭建快 |
| Code | 更灵活 |
