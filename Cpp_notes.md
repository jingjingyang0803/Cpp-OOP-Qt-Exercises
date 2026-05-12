# 1. `.` / `>` /  / `&`

## `.`

对象调用成员：

```cpp
obj.func()
obj.value
```

---

## `>`

指针调用成员：

```cpp
ptr->func()
```

等价：

```cpp
(*ptr).func()
```

例：

```cpp
dates.at(i)->toString()
```

说明：

```cpp
dates.at(i) 返回指针
```

---

##

### 声明指针

```cpp
int*p;
```

### 解引用

```cpp
*p
```

取指针指向对象。

---

## `&`

### 类型后：引用

```cpp
string&
Account*&
```

表示“别名”。

---

### 变量前：取地址

```cpp
&obj
```

得到地址。

---

例：

```cpp
transfer_to(&normal_account,20)
```

传地址。

---

# 2. 引用 `&`（最重要）

## 普通引用

```cpp
string&s
```

修改会影响原变量。

---

## const 引用（最常用）

```cpp
const string& s
```

特点：

**不复制
不能修改
效率高**

大型对象参数都推荐：

```cpp
const vector<int>&
const map<int,string>&
```

---

## 指针引用

```cpp
string*& p
```

含义：p 是 “指针的引用”

可以修改指针本身。

---

例：

```cpp
map<int,Service>*&
```

表示：map指针 的引用

---

# 3. const 放哪里

---

## const 在前

```cpp
const string& s
```

不能修改 s。

---

## const 在后（成员函数）

```cpp
void print() const
```

表示：该函数不修改成员变量

---

## const 指针

```cpp
const int* p
```

不能改 `*p`

---

```cpp
int* const p
```

不能改 p。

---

# 4. auto

自动推导类型：

```cpp
auto x =5;
```

---

常见：

```cpp
auto it =m.find(key);
```

避免写超长类型。

---

推荐：

```cpp
const auto&
```

---

# 5. for loop

---

## 普通 for

```cpp
for(int i=0;i<n;i++)
```

---

## range-for（现代 C++）

---

### 不修改元素

```cpp
for(const string& s :arr)
```

避免复制。

---

### 修改元素

```cpp
for(string& s :arr)
```

---

### 指针容器

```cpp
for(Role*role :roles_)
```

---

### auto

```cpp
for(const auto&x :vec)
```

最推荐。

---

# 6. string 常用

---

## find

```cpp
str.find(",")
```

返回位置。

找不到：

```cpp
string::npos
```

---

## 判断包含

```cpp
if(str.find(",")!= string::npos)
```

---

## substr

```cpp
str.substr(start,len)
```

例：

```cpp
"hello".substr(1,3)
```

结果：

```cpp
ell
```

---

## empty

```cpp
str.empty()
```

为空。

---

```cpp
notstr.empty()
```

非空。

---

# 7. vector / map

---

## vector

```cpp
v.push_back(x)
v.at(i)
v[i]
v.size()
v.empty()
```

---

## at vs []

### `[]`

不检查越界。

---

### at()

检查越界。

更安全。

---

## map

```cpp
map<string,int> m;
```

---

### 插入

```cpp
m["Tom"] =90;
```

---

### 查找

```cpp
m.find(key)
```

返回 iterator。

---

### 判断存在

```cpp
if(m.find(key)!=m.end())
```

---

### 不存在

```cpp
if(m.find(key)==m.end())
```

---

# 8. iterator

iterator 类似指针。

---

## `it->first`

map key。

---

## `it->second`

map value。

---

例：

```cpp
auto it =definitions_.find(field);

return _definitions.push_back(it->second);
```

---

# 9. sort

---

## 默认升序

```cpp
sort(v.begin(),v.end());
```

---

## 自定义排序

```cpp
sort(v.begin(),v.end(),
     [](int a,int b)
     {
				return a>b;
     });
```

降序。

---

# 10. Lambda（超重要）

匿名函数。

---

结构：

```cpp
[](){}
```

---

完整：

```cpp
[](int a,int b)
{
	return a+b;
}
```

---

## 三部分

- [] 捕获列表
- () 参数
- {} 函数体

---

## 空捕获

```cpp
[]
```

不使用外部变量。

---

## 捕获外部变量

```cpp
[x]
[&x]
[=]
[&]
```

---

# 11. transform

```cpp
transform(begin,end,out_begin,func)
```

---

例：

```cpp
transform(str.begin(),
					str.end(),
					str.begin(),
          [](unsignedcharc)
          {
						returntolower(c);
          });
```

全部转小写。

---

# 12. throw / catch / exception

---

## throw

抛异常：

```cpp
throw invalid_argument("bad");
```

---

## catch

```cpp
catch(const invalid_argument& e)
```

推荐 const 引用。

---

## what()

错误信息：

```cpp
e.what()
```

---

## 常见异常

`invalid_argument
domain_error
out_of_range
runtime_error`

---

例：

```cpp
throw domain_error("No numbers");
```

---

# 13. stod

```cpp
doubl ex =stod(str);
```

string → double。

失败抛：

```cpp
invalid_argument
```

---

# 14. 文件读取

---

## 打开文件

```cpp
ifstream file(filename);
```

---

## 检查成功

```cpp
if(!file)
```

---

## 读取一行

```cpp
getline(file,line);
```

---

## 读取单词

```cpp
file>>word;
```

---

# 15. cin / getline

---

## cin >>

```cpp
cin>>x;
```

遇空格停止。

---

## getline

```cpp
getline(cin,line);
```

读整行。

---

# 16. cout

---

## 输出

```cpp
cout<<x;
```

---

## endl

```cpp
cout<<endl;
```

换行 + flush。

---

## 推荐

```cpp
"\n"
```

更快。

---

## 连续输出

```cpp
cout<<a<<" "<<b<<endl;
```

---

# 17. static_cast / dynamic_cast

---

## static_cast

普通转换：

```cpp
static_cast<int>(x)
```

---

## dynamic_cast（继承）

```cpp
dynamic_cast<Child*>(baseptr)
```

失败返回：

```cpp
nullptr
```

---

# 18. nullptr

现代空指针：

```cpp
nullptr
```

不要用：

```cpp
NULL
0
```

---

# 19. 前置++ / 后置++

---

## 前置

```cpp
++i
```

先加后用。

效率更高。

---

## 后置

```cpp
i++
```

先用后加。

---

例：

```cpp
ID_(NEXT_ID++)
```

先赋值，再自增。

---

# 20. make_shared

推荐：

```cpp
auto p =make_shared<Node>();
```

代替：

```cpp
shared_ptr<Node> p(newNode);
```

---

优点：

```cpp
更安全
更快
少一次分配
```

---

# 21. shared_ptr

自动释放内存。

不用 delete。

---

## 创建

```cpp
make_shared<T>()
```

---

## get()

```cpp
ptr.get()
```

得到裸指针。

---

# 22. 初始化列表（重要）

推荐：

```cpp
Circle(intr)
    : radius_(r)
{
}
```

不要：

```cpp
{
	radius_ =r;
}
```

---

## 父类构造

```cpp
Student(...)
    : Person(name,age)
{
}
```

---

# 23. return *this

```cpp
return *this;
```

返回当前对象。

用于：

```cpp
operator=
链式调用
```

---

# 24. ostream

---

## cout

标准输出。

---

## ostream&

任意输出流：

```cpp
void print(ostream& out)
```

既能输出：

```cpp
cout
文件
stringstream
```

---

# 25. ostringstream

字符串输出流。

---

## 写入

```cpp
ostringstream oss;

oss << "line1\n";
oss << "line2\n";
oss << "x = " << x << "\n";

// 一次性写很多段
oss << "The program uses:\n"
    << "  A: " << a << "\n"
    << "  B: " << b << "\n";
```

---

## 获取字符串

```cpp
oss.str()
```

---

# 26. noexcept

```cpp
void func()noexcept
```

表示：

```cpp
不会抛异常
```

---

# 27. setw / setfill

格式化：

```cpp
setw(2)
setfill('0')
```

结果：

```cpp
03
09
```

---

# 28. erase-remove（超重要）

删除 vector 元素标准写法：

```cpp
v.erase(remove(v.begin(),
v.end(),
x),
v.end());
```

---

## remove

不真正删除。

只是：

```cpp
把保留元素前移
```

---

## erase

真正删尾部垃圾。

---

# 29. Circular List 思路

核心：

```cpp
last_->next 永远指向 first_
```

---

## 插入头

```cpp
new->next =first_;
first_ =new;
last_->next =first_;
```

---

## 插入尾

```cpp
new->next =first_;
last_->next =new;
last_ =new;
```

---

## 删除头

```cpp
first_ =first_->next;
last_->next =first_;
```

---

## 删除尾

```cpp
找到last_前一个
current->next =first_
last_ =current
```

---

# 30. 双向链表（Two Way List）

每节点：

```cpp
prev
next
```

---

## 插入中间

```cpp
new->prev =cur->prev;
new->next =cur;

cur->prev->next =new;
cur->prev =new;
```

---

## 删除中间

```cpp
cur->prev->next =cur->next;
cur->next->prev =cur->prev;
```

---

## 提前结束

```cpp
if(current->data>target)
{
returnfalse;
}
```

因为后面更大。

---

## 插入思路

找到：

```cpp
第一个 >= 插入值 的节点
```

插它前面。

---

# 31. OOP 核心

---

## class

```cpp
数据 + 方法
```

---

## private

隐藏实现。

---

## public

外部接口。

---

## inheritance

```cpp
is-a
```

---

## polymorphism

父类指针指向子类。

---

## virtual

运行时动态绑定。

---

# 32. STL 最常用

---

## vector

动态数组。

---

## map

key-value。

---

## set

自动排序 + 不重复。

---

## list

双向链表。

---

# 33. 最推荐现代 C++ 写法

---

## 推荐

```cpp
const auto&
nullptr
make_shared
range-for
initializer list
```

---

## 少用

```cpp
new/delete
NULL
复制大对象
裸指针
```
