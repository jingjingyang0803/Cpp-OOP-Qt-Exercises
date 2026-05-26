# 1. Late Dynamic Binding / Virtual Function

* virtual function 使用 runtime polymorphism
* 调用哪个函数，在 runtime 决定
* 条件：

  * virtual function
  * base pointer/reference
  * 指向 derived object

## 规律

* base object → 调用 Base function
* derived object → 调用 Derived function
* base pointer/reference 指向 derived → 调用 Derived function
* object assignment (`Base b = Sub()`) 会发生 object slicing

  * Sub 部分被切掉
  * 最终调用 Base function

# 2. Inheritance（public / protected / private）

## 子类继承什么

* public 成员：继承，可访问
* protected 成员：继承，可访问
* private 成员：会被继承到对象里，但子类不能直接访问

## Public inheritance

* public → public
* protected → protected
* 表示：

  * “Derived is-a Base”
* 最常用

## Protected inheritance

* public → protected
* protected → protected

## Private inheritance

* public → private
* protected → private

# 3. Doubly Linked List（Two-way Linked List）

## 结构

每个节点包含：

* data
* prev pointer
* next pointer

可以：

* forward traversal（next）
* backward traversal（prev）

## 普通指针实现

* prev 和 next 都是 raw pointers
* 需要手动管理内存
* 容易 memory leak

## Smart pointer 实现

### shared_ptr + weak_ptr（推荐）

* next 用 shared_ptr
* prev 用 weak_ptr

原因：

* shared_ptr 双向引用会产生 circular reference
* weak_ptr 不增加 reference count

### unique_ptr + raw pointer

* next 用 unique_ptr
* prev 用 raw pointer
* ownership 更清晰
* 很常见的设计方式
