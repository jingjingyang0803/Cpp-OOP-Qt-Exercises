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



# C++ / OOP / Qt 

## 1. Abstraction and Interface

### 1.1 Abstraction 抽象

Abstraction 的意思是：

> 通过隐藏或省略细节，把复杂概念简化成更容易处理的形式。
> 

核心：

Generalizing a concept by hiding or omitting details

目的：

- 隐藏不重要的实现细节
- 保留重要概念和结构
- 降低复杂度
- 让程序更容易理解和维护

### 1.2 Principle of Locality 局部性原则

目标：

> Minimize connections between software components.
> 

意思是：

- 软件组件之间的连接越少越好
- 类之间依赖越少越好
- 修改一个地方时，影响范围越小越好

这有助于：

- 降低耦合
- 提高可维护性
- 提高可测试性

## 2. Design by Contract 契约式设计

Design by Contract，简称 DbC。

核心思想像签合同：

> 调用者按规定调用，函数就保证按规定工作。
> 

### 2.1 三个核心问题

| 问题 | 对应概念 | 谁负责 |
| --- | --- | --- |
| What does the contract expect? | Precondition 前置条件 | Caller |
| What does the contract guarantee? | Postcondition 后置条件 | Implementer |
| What does the contract maintain? | Invariant 不变式 | Class |

### 2.2 Precondition 前置条件

前置条件是：

> 调用函数之前必须满足的条件。
> 

例如：

```cpp
// Precondition: day >= 1 && day <= days in month
void setDay(int day);
```

如果调用者传入非法参数，责任在调用者。

### 2.3 Postcondition 后置条件

后置条件是：

> 函数执行完成后必须保证的结果。
> 

例如：

```cpp
// Postcondition: if day is legal, date is changed
// Postcondition: if day is illegal, exception is thrown
```

这是实现者负责保证的。

### 2.4 Invariant 不变式

不变式是：

> 对象在公开操作前后都必须保持成立的条件。
> 

例如：

```cpp
// Invariant: Date object must always represent a legal date.
```

也就是：

调用前：对象合法
调用后：对象仍然合法

### 2.5 子类中的 DbC 规则

子类不能：

- 强化前置条件
- 削弱后置条件

意思是：

- 子类不能要求调用者满足更多条件
- 子类不能比父类承诺得更少

否则会破坏多态。

## 3. Exception Handling 异常处理

### 3.1 catch(...)

```cpp
catch(...)
{
// catch all exceptions
}
```

含义：

> 捕获所有类型的异常。
> 

注意：

- 它不知道异常具体类型
- 通常用于最后兜底
- 不适合滥用

## 4. Object Lifetime and Memory Management

对象生命周期主要分为两类：

- Automatic / Static Storage Duration
- Dynamic Storage Duration

### 4.1 Automatic / Static Storage Duration

特点：

- 生命周期由作用域或编译器管理
- 自动创建
- 自动销毁
- 程序员不用 delete
- 更安全

例如：

```cpp
void f()
{
	Card c;
} // c 自动析构
```

优先使用这种方式。

### 4.2 Dynamic Storage Duration

动态对象通常在 heap 上创建：

```cpp
Card* c = new Card();
```

特点：

- 运行时创建
- 生命周期更灵活
- 需要管理释放

传统 C++：new + delete

现代 C++ 推荐：dynamic object + smart pointer

例如：

```cpp
auto c = std::make_unique<Card>();
```

## 5. RAII-Resource Acquisition Is Initialization

> 构造函数获取资源，析构函数释放资源。
> 

资源不只是内存，也包括：

- heap memory
- file
- socket
- mutex
- network connection

RAII 的好处：

- 自动释放资源
- 减少内存泄漏
- 异常情况下也更安全

## 6. Constructor, Initializer List, Destructor

### 6.1 Initializer List 初始化列表

初始化列表用于：

> 直接构造成员变量。
> 

而不是：

先默认构造，再赋值

### 6.2 为什么用 initializer list？

更高效。

尤其下面这些成员必须用 initializer list：

- const 成员
- reference 成员
- 没有默认构造函数的成员对象

例如：

```cpp
class Card
{
public:
	Card(int value)
		**: value_(value)**
	{
	}

private:
	const int value_;
};
```

### 6.3 Copy Constructor 拷贝构造函数

形式：

```cpp
Class(const Class& other);
```

作用：

> 创建新对象时，用已有对象初始化它。
> 

Class&：用起来更像普通变量，不能是空，更安全（常用于参数）。
Class*：可以是 nullptr，需要 -> 访问成员，适合“可空/可选”的情况。

例子：

```cpp
Card c1(5);
Card c2 = c1;
```

函数传值也会调用 copy constructor：

```cpp
void f(Card c);
```

### 6.4 Assignment Operator 赋值运算符

```cpp
Card c1(5);
Card c2(10);

c2 = c1;
```

| 情况 | 调用 |
| --- | --- |
| 创建新对象 | Copy constructor |
| 已有对象重新赋值 | Assignment operator |

### 6.5 Destructor 析构函数

析构函数会在对象生命周期结束时自动调用。

常见情况：

1. 局部变量离开作用域
2. delete 动态对象
3. 容器销毁元素
4. 成员对象随所属对象销毁

例子：

```cpp
void f()
{
	Card c;
} // 自动调用 c 的 destructor
```

### 6.6 Virtual Destructor

如果类可能被继承，析构函数应该是 virtual：

```cpp
class Base
{
public:
	virtual ~Base() = default;
};
```

原因：

```cpp
Base* p = new Derived();
delete p;
```

如果 Base 的析构函数不是 virtual，可能不会正确调用 Derived 的析构函数。

正确析构顺序：

Derived destructor
Base destructor

## 7. Ownership 所有权

Ownership 表示：

> 谁负责释放资源。
> 

接口文档必须说明 ownership 是否转移。

### 7.1 不转移 ownership

```cpp
void print(Card* c);
```

意思：

- 函数只是使用 Card
- 不负责 delete
- 调用者仍然拥有对象

### 7.2 转移 ownership

```cpp
void store(Card* c);
```

如果 store 会保存指针，并最终 delete：

- ownership 转移给 store
- 调用者之后不能 delete

否则会 double delete。

### 7.3 Move ownership vs Copy

Move ownership：

转移资源所有权

Copy：

复制对象内容

Move 通常更快，因为不需要复制全部数据。

## 8. Smart Pointers 智能指针

现代 C++ 推荐用智能指针管理动态对象。

### 8.1 unique_ptr

特点：

- 独占 ownership
- 不能复制
- 只能 move

例子：

```cpp
std::unique_ptr<Card> p = std::make_unique<Card>();
```

不能这样：

```cpp
std::unique_ptr<Card> p2 = p; // wrong
```

可以 move：

```cpp
std::unique_ptr<Card> p2 = std::move(p);
```

move 后：

p 不再拥有对象
p2 拥有对象

### 8.2 unique_ptr::release()

```cpp
Card* raw = p.release();
```

作用：

- 放弃 ownership
- 不 delete 对象
- 返回 raw pointer 裸指针

之后：

`p == nullptr`

注意：

`release()` 不会 delete 对象

所以 raw pointer 必须之后被正确管理（比如后面交给另一个智能指针，或者明确 delete raw）。

### 8.3 unique_ptr::reset()

```cpp
p.reset();
```

作用：

- delete 当前对象
- p 变成 nullptr

也可以换成新对象：

```cpp
p.reset(new Card());
```

### 8.4 shared_ptr

特点：

- 共享 ownership
- 使用 reference counting

例子：

```cpp
std::shared_ptr<Card> p1 = std::make_shared<Card>();
std::shared_ptr<Card> p2 = p1;
```

这不是深拷贝。

意思是：

p1 和 p2 指向同一个对象

对象会在最后一个 shared_ptr 消失后销毁。

### 8.5 shared_ptr 缺点

shared_ptr 不是越多越好。

缺点：

- 有引用计数开销
- 比 unique_ptr 慢
- 可能产生循环引用

只有真的需要共享 ownership 时才用 shared_ptr。

### 8.6 get()

unique_ptr 和 shared_ptr 都有：

```cpp
ptr.get();
```

作用：

得到普通 raw pointer

但是：

不转移 ownership

### 8.7 weak_ptr

weak_ptr 用来观察 shared_ptr 管理的对象。

特点：

- 不增加引用计数
- 不拥有对象
- 不影响对象生命周期

例子：

```cpp
std::shared_ptr<Person> sp = std::make_shared<Person>();
std::weak_ptr<Person> wp = sp;
```

### 8.8 weak_ptr::expired()

```cpp
wp.expired()
```

返回 bool：

| 返回值 | 含义 |
| --- | --- |
| true | 对象已经销毁 |
| false | 对象还活着 |

注意：

expired() 只是当前时刻的快照

多线程下结果可能马上变化。

### 8.9 weak_ptr::lock()

weak_ptr 不能直接解引用。

它没有：

```cpp
operator->
operator*
get()
```

必须先 lock：

```cpp
if (auto sp = wp.lock())
{
	sp->doSomething();
}
else
{
// object already destroyed
}
```

lock 的作用：

| 情况 | 结果 |
| --- | --- |
| 对象还活着 | 返回有效 shared_ptr |
| 对象已销毁 | 返回空 shared_ptr |

## 9. Circular Reference 循环引用

如果两个对象互相用 shared_ptr 指向对方：

A -> shared_ptr<B>
B -> shared_ptr<A>

会导致：

引用计数永远不为 0
对象无法释放

解决方法：

其中一边使用 weak_ptr

## 10. Linked List Ownership Example

双向链表可以这样设计：

```cpp
struct ListItem
{
	int value;
	std::shared_ptr<ListItem> next;
	ListItem* prev;
};

std::shared_ptr<ListItem> first_;
ListItem* last_;
```

含义：

| 成员 | 作用 |
| --- | --- |
| first_ | 拥有第一个节点 |
| next | 拥有下一个节点 |
| prev | 只指路，不拥有 |
| last_ | 只指路，不拥有 |

这样：

从 first_ 开始拥有整条链表

当 first_ 被销毁时：

整个链表自动释放

如果 prev 也用 shared_ptr，就可能形成循环引用。

## 11. Association, Aggregation, Composition

### 11.1 Bidirectional Association 双向关联

例子：

```cpp
Book 知道 Loan
Loan 知道 Book
```

两个类互相知道对方。

### 11.2 Forward Declaration 前向声明

如果类之间互相引用，可以用 forward declaration：

```cpp
// A.h
// 不需要知道类型大小/内部成员
#pragma once
class B;              // forward declaration

class A {
public:
    void setB(B* b);  // 这里只需要知道 B 是一个类型
private:
    B* b_;            // 指针成员：可以只 forward declare
};
```

意思：

```cpp
先告诉编译器 Loan 是一个类
```

好处：

- 减少头文件依赖
- 避免循环 include
- 提高编译效率

```cpp
class Loan;        // 声明 class
struct Node;       // 声明 struct（class/struct 都可以 forward declare）
enum class E;      // enum class 可以前向声明（C++11 起）
```

### 11.3 Composition 组合

Composition 是最强的拥有关系。

意思：部件生命周期依赖整体

例如：House owns Room

House 消失，Room 也消失。

### 11.4 Shared Aggregation 共享聚合

Shared aggregation 表示：

**一个对象可以属于多个对象
生命周期独立**

例如：Publisher 和 Book

Book 不一定随着 Publisher 的消失而消失。

## 12. Copying and Shallow Copy

### 12.1 Shallow Copy 浅拷贝

Shallow copy 只复制指针地址。

例子：

```cpp
p2 =p1;
```

如果只是复制 raw pointer，两个对象可能指向同一块内存。

危险：

- double delete
- dangling pointer
- 修改一个影响另一个

## 13. OOP Core Concepts

### 13.1 Class 类

Class 是对象的模板。

定义：

- attributes
- behavior
- internal structure
- initial state

### 13.2 Object 对象

Object 是 class 的实例。

对象有三个核心特征：

- **State**（状态）
- **Identity**（身份）
- **Behavior**（行为）

### 13.3 State 状态

State 是对象当前的数据。

特点：

- 由 attributes 组成
- 每个对象自己的状态独立
- 程序运行中可以变化

### 13.4 Identity 身份

即使两个对象状态完全一样，它们也可以是不同对象。

例如：

```cpp
Card a(5);
Card b(5);
```

a 和 b 状态相同，但身份不同。

### 13.5 Behavior 行为

Behavior 是对象能执行的操作。

例如：

```cpp
card.print();
card.setValue(5);
```

## 14. Encapsulation 封装

Encapsulation 的核心：

**隐藏内部实现**
**只暴露公共接口**

好的 OOP 应该：

**数据和行为放在一起**

### 14.1 Tell, Don’t Ask

意思是：

> 不要把对象的数据拿出来在外面处理，而是告诉对象去完成事情。
> 

坏设计：

```cpp
intvalue =card.getValue();
if (value>10)
{
    ...
}
```

更好的设计：

```cpp
card.handleHighValue();
```

### 14.2 Getter / Setter 过多的问题

如果一个类：

- 有大量 getter/setter
- 逻辑都在外部
- 自己只保存数据

通常说明封装不好。

### 14.3 God Class / Blob

特点：

- 一个类知道太多其他类的细节
- 一个类做太多事情
- 高耦合
- 难测试
- 难维护

这是常见坏设计。

## 15. Static Members

static 成员属于类，而不是单个对象。

意思：

**所有对象共享同一份 static 数据**

例子：

```cpp
class Card
{
	private:
		static int count_;
};
```

## 16. Inheritance 继承

### 16.1 继承是什么？

子类获得父类的功能。

目的：

- 代码复用
- 扩展功能
- 表达层次结构
- 表示特殊化关系

例子：

```cpp
Animal
  ↑
Dog
```

Dog 是 Animal。

### 16.2 继承语法

```cpp
class Dog :public Animal
{
};
```

### 16.3 is-a 关系

判断是否应该使用继承，最重要的是：

**is-a relationship**

例子：

**Dog is an Animal**

适合继承。

### 16.4 has-a 关系

如果是 has-a：

**Car has an Engine**

应该用 composition，而不是 inheritance。

### 16.5 Ancestor and Descendant

| 概念 | 含义 |
| --- | --- |
| Ancestor | 往上的父类、祖先类 |
| Descendant | 往下的子类、后代类 |

### 16.6 子类可以做什么？

子类可以：

1. 继承父类功能
2. 增加新功能
3. 修改父类功能

### 16.7 private members are inherited

父类 private 成员也存在于子类对象中。

但是：

**子类不能直接访问父类 private 成员**

### 16.8 protected

protected 表示：

- 子类可以访问
- 外部不能访问

但是最好：

**Only member functions should be protected**

成员变量最好仍然 private。

推荐：

| 内容 | 访问权限 |
| --- | --- |
| 成员变量 | private |
| 公共接口 | public |
| 给子类用的辅助函数 | protected |

### 16.9 构造顺序

子类对象创建时：

1. Base class constructor
2. Derived class constructor

原因：

子类可能使用父类部分，所以父类必须先初始化

### 16.10 析构顺序

对象销毁时：

1. Derived destructor
2. Base destructor

如果通过父类指针 delete 子类对象，父类析构函数必须是 virtual。

### 16.11 Object Slicing 对象切片

如果子类对象以值传递给父类参数：

```cpp
void processBook(Bookbook);

LibraryBook lb;
processBook(lb);
```

会发生 object slicing：**子类额外部分丢失**

解决：

```cpp
void processBook(const Book& book);
```

或：

```cpp
void processBook(Book* book);
```

### 16.12 Late Binding 动态绑定

Late binding 指：

运行时才决定调用哪个函数

通常依赖 virtual function。

### 16.13 Interface Class 接口类

Interface class：

**只定义规则
不提供实现**

通常包含 pure virtual functions。

=0 是“接口占位符/强制子类实现”的语法糖

```cpp
class Drawable
{
public:
	virtual void draw() =0;
	virtual ~Drawable() =default;
};
```

### 16.14 Abstract Base Class 抽象基类

Abstract base class：

- 不能实例化
- 可以有部分实现
- 至少有一个 pure virtual function

### 16.15 继承的风险

继承层次太深会导致：

- 难理解
- 难维护
- 代码分散
- 改父类影响很多子类

所以：

不要滥用继承

## 17. Testing 测试

### 17.1 测试的目标

测试不是为了证明程序没 bug。

测试真正目标是：

找 bug

经典说法：

> A successful test case is one that causes a failure.
> 

### 17.2 正确测试 mindset

> 假设代码有问题，我要找到它。
> 

### 17.3 测试不会直接提升质量

测试只能发现问题。

真正提升质量的是：

> 修复问题
> 

### 17.4 Technical Debt 技术债

Technical debt 指：

> 为了赶时间写的烂代码
> 

短期快，长期会导致：

- 难维护
- 难测试
- 难扩展
- bug 增多

### 17.5 测试困难说明什么？

如果代码很难测试，通常说明设计有问题。

可能原因：

- 类之间耦合太强
- God class
- 难 isolate
- 难 mock
- 依赖全局变量

## 18. Error, Fault, Failure

### 18.1 Error

Error 是最广义的错误。
意思：**程序行为和 specification 不一致**

注意：

error 可能来自错误需求，而不一定来自代码。

### 18.2 Fault / Defect

Fault 或 defect 指：**代码内部存在缺陷**

但不一定已经表现出来。

一个 fault：

- 可能导致多个 failure
- 也可能永远不触发

### 18.3 Failure

Failure 指：**用户实际看到的错误行为**

### 18.4 三者关系

```cpp
Fault / Defect
	↓
执行到错误代码
	↓
Failure
	↓
违反 specification
	↓
Error
```

## 19. Unit Testing

### 19.1 Unit testing 的目标

Unit testing 用来：

- 快速发现错误
- 防止 regression
- 支持 refactoring

### 19.2 Unit testing 的视角

Unit testing 通常采用：**interface / black-box view**

也就是说：测试关注接口承诺的行为，而不是内部如何实现

### 19.3 好测试的特点

好测试应该：

- 小
- 精准
- 可重复
- 相互独立

### 19.4 最重要的测试输入

通常不是正常输入，而是：

- 边界情况
- 异常输入
- 错误情况

### 19.5 Test Isolation

Test isolation 指：**测试之间不能互相依赖**

每个测试应该能单独运行。

### 19.6 Global Variable 的问题

全局变量会造成：

- 函数之间隐藏依赖
- 测试顺序影响结果
- 难 isolate
- 难 debug

### 19.7 测试代码本身也要干净

测试代码也需要：

- 清晰结构
- 必要注释
- 可维护
- 可重构

## 20. Qt Test

### 20.1 Qt Test 生命周期

| 函数 | 运行时间 |
| --- | --- |
| initTestCase() | 所有测试开始前运行一次 |
| cleanupTestCase() | 所有测试结束后运行一次 |
| init() | 每个测试前运行 |
| cleanup() | 每个测试后运行 |

### 20.2 常用宏

```cpp
QVERIFY(condition);
```

检查 condition 是否为 true。

```cpp
QVERIFY2(condition,"message");
```

带错误信息的 QVERIFY。

```cpp
QCOMPARE(actual,expected);
```

比较实际值和期望值。

### 20.3 Data-driven Testing

Data-driven testing 指：**同一个测试逻辑，使用多组输入数据运行**

优点：

- 减少重复代码
- 覆盖更多情况
- 结构更清楚

## 21. Static Analysis

Static analysis 指静态代码分析。

工具例子：SonarQube

作用：

- 检查潜在 bug
- 检查坏味道
- 检查代码质量
- 辅助发现 technical debt

## 22. Qt GUI Basics

### 22.1 Qt GUI 程序本质

Qt GUI 是 event-driven programming。

流程：

```cpp
用户操作
  ↓
产生 event
  ↓
Qt 处理 event
  ↓
发出 signal
  ↓
执行 slot
  ↓
界面更新
```

### 22.2 Event 三个属性

| 属性 | 含义 | 例子 |
| --- | --- | --- |
| Target | 事件发生在哪个组件上 | Button A |
| Source | 事件来源 | Mouse, Keyboard |
| Type | 事件类型 | Click, Key Press |

## 23. Signal and Slot

### 23.1 Signal-Slot 机制

Qt 把复杂的事件系统封装成 signal-slot。

例如：

```cpp
用户点击按钮
  ↓
button 发出 clicked() signal
  ↓
slot 函数执行
```

### 23.2 connect

```cpp
connect(button,
        &QPushButton::clicked,
        this,
        &MainWindow::changeColor);
```

含义：当 button 被点击时，调用 MainWindow::changeColor

### 23.3 一个 signal 可以连接多个 slot

例如：

```cpp
slider valueChanged
  ↓
spinbox.setValue()
updateColor()
```

一个信号可以触发多个操作。

### 23.4 Qt 事件流程

```cpp
用户点击按钮
  ↓
mousePressEvent
mouseReleaseEvent
  ↓
Qt 内部处理
  ↓
emit clicked()
  ↓
connect 找到 slot
  ↓
slot 执行
  ↓
界面更新
```

## 24. Qt Documentation

查 Qt 文档时重点看：

| 部分 | 看什么 |
| --- | --- |
| Signals | 组件会发出什么信号 |
| Public Functions | 可以调用哪些普通函数 |
| Public Slots | 哪些函数可以作为 slot |
| Inherited Members | 从父类继承了什么 |

### 24.1 const member function

例子：

```cpp
QString text() const;
```

含义：

| 部分 | 含义 |
| --- | --- |
| `QString` | 返回值类型 |
| `text()` | 函数名 |
| `const` | 不修改对象状态 |

## 25. Qt GUI Project Structure

Qt Creator 自动生成的常见文件：

`main.cpp
mainwindow.cpp
mainwindow.hh
mainwindow.ui
project.pro`

### 25.1 main.cpp

`main.cpp` 负责：

- 创建 QApplication
- 创建 MainWindow
- 显示窗口
- 启动 event loop

### 25.2 mainwindow.ui

`mainwindow.ui` 是图形界面描述文件。

本质：XML 文件

但通常不需要手写。

作用：描述界面上有哪些 

### 25.3 .ui 和 .cpp/.hh 的分工

`widget.ui`     负责界面
`.cpp/.hh`       负责逻辑

## 26. Qt Class Hierarchy

常见继承结构：

```cpp
QObject
   ↓
QWidget
   ↓
QMainWindow
   ↓
MainWindow
```

所有 GUI 组件最终都和 QObject 相关。

## 27. Qt Memory Management

### 27.1 Parent-Child Mechanism

Qt 有自己的自动内存管理机制：Parent-Child Mechanism

也叫：QObject Tree

### 27.2 QObject Tree

QObject 内部维护：children list

当 parent 被销毁时：所有 children 自动 delete

### 27.3 Qt 为什么大量使用 raw pointer？

Qt 中常见：

```cpp
QPushButton* button =new QPushButton(this);
```

虽然是 raw pointer，但如果传入 parent：

```cpp
new QPushButton(this);
```

Qt 会自动管理生命周期。

### 27.4 Qt 黄金规则

**创建 widget 时永远给 parent**

例如：

```cpp
newQPushButton(this);
newQLabel(this);
newQSlider(this);
```

只要 widget 有 parent，一般不用手动 delete。

## 28. QTimer

### 28.1 QTimer 本质

QTimer 不是 GUI 组件。

它依赖：Qt Event Loop

### 28.2 QTimer 工作流程

```cpp
timer->start(1000)
  ↓
等待 1 秒
  ↓
emit timeout()
  ↓
slot 执行
  ↓
继续等待
  ↓
重复
```

### 28.3 timeout()

QTimer 最重要的 signal：

```cpp
timeout()
```

意思是：时间到了

### 28.4 repeating timer

Qt 默认是 repeating timer。

也就是：每隔一段时间重复触发

### 28.5 single-shot timer

single-shot timer 只触发一次。

```cpp
timer_->setSingleShot(true);
```

恢复重复模式：

```cpp
timer_->setSingleShot(false);
```

### 28.6 QTimer 示例结构

```cpp
#include<QTimer>

class MainWindow :public QMainWindow
{
    Q_OBJECT

		private slots:
			void myTimerSlot();
		
		private:
			QTimer* timer_;
};
```

## 29. Qt Layout

### 29.1 Layout 的作用

Layout 用来管理 widget 的位置和大小。

最大优点：自动缩放

窗口变大或变小时：layout 自动调整组件

### 29.2 为什么推荐 layout？

因为现代 GUI 不能固定死位置。

Layout 更适合：

- 自动调整大小
- 动态界面
- 复杂 GUI
- 更容易维护

### 29.3 纯代码 GUI

如果完全用代码写 GUI，可以创建项目时取消：

- [ ]  Generate Form

这样不会生成 .ui 文件。

### 29.4 推荐方式

现代 Qt GUI 推荐：代码创建控件 + Layout 管理布局

优点：

- 更灵活
- 更适合循环创建组件
- 更容易动态修改界面
- 更适合复杂程序
