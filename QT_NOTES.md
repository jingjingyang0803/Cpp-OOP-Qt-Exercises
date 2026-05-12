## Qt Widgets 常见代码总结

## 1. 窗口与构造函数

### 构造函数

```cpp
explicit MainWindow(QWidget* parent = nullptr);
```

含义：

- `explicit`
    
    防止隐式转换
    
- `QWidget* parent`
    
    父对象
    
- `= nullptr`
    
    默认无父对象
    

### 析构函数

```cpp
MainWindow::~MainWindow()
{
    delete ui;
}
```

释放 UI。

Qt 父子机制会自动释放子控件。

## 2. 常见控件（Widgets）

### QLabel

显示文本/图片

```cpp
QLabel* label = new QLabel("Hello", this);
```

#### 设置对齐

```cpp
label->setAlignment(Qt::AlignCenter);
```

#### 自动换行

```cpp
label->setWordWrap(true);
```

#### 设置固定大小

```cpp
label->setFixedSize(60, 60);
```

#### 设置最小高度

```cpp
label->setMinimumHeight(200);
```

#### 显示一个填充颜色的 pixmap

```cpp
QPixmap pix(64, 64);
pix.fill(Qt::red);

label->setPixmap(pix);
```

### QPushButton

```cpp
QPushButton* btn = new QPushButton("OK", this);
```

### QLineEdit

单行输入框

#### 获取文本

```cpp
lineEdit->text();
```

#### 设置文本

```cpp
lineEdit->setText("hello");
```

### QTextBrowser

富文本显示

```cpp
textBrowser->setText("hello");
```

### QComboBox

下拉框

#### 添加选项

```cpp
comboBox->addItem("apple");
```

#### 获取当前文本

```cpp
comboBox->currentText();
```

#### 设置当前索引

```cpp
comboBox->setCurrentIndex(1);
```

### QSpinBox

数字输入框

#### 获取值

```cpp
spinBox->value();
```

#### 设置值

```cpp
spinBox->setValue(50);
```

### QSlider

滑动条

#### 设置方向（构造函数）

```cpp
QSlider* slider = new QSlider(Qt::Horizontal, this);
```

也可以：

```cpp
QSlider* slider = new QSlider(Qt::Vertical, this);
```

#### 运行时修改方向

```cpp
slider->setOrientation(Qt::Horizontal);
// slider->setOrientation(Qt::Vertical);
```

#### 设置范围

```cpp
slider->setRange(0, 255);
```

#### 单独设置

```cpp
slider->setMinimum(0);
slider->setMaximum(255);
```

也可设置刻度、步长、信号、范围

### QLCDNumber

LCD 数字显示

```cpp
lcdNumber->display(0);
```

## 3. 布局（Layouts）

### 水平布局

```cpp
QHBoxLayout* layout = new QHBoxLayout;
```

### 垂直布局

```cpp
QVBoxLayout* layout = new QVBoxLayout;
```

### 网格布局

```cpp
QGridLayout* grid = new QGridLayout;
```

#### 添加控件

```cpp
grid->addWidget(red_label, 0, 0);
```

参数：

```
控件, 行, 列
```

### 布局嵌套

```cpp
horizontal_layout->addLayout(grid_layout);
```

### 设置整体对齐

```cpp
main_layout->setAlignment(Qt::AlignTop);
```

## 4. 获取控件值

### 获取文本

```cpp
lineEdit->text();
```

### 获取数字

```cpp
spinBox->value();
slider->value();
```

### 获取下拉框内容

```cpp
comboBox->currentText();
```

## 5. 设置属性

#### 设置对象名

```cpp
widget->setObjectName("myButton");
```

常用于：

- stylesheet
- 查找对象
- Qt Designer

#### 设置大小

```cpp
widget->setFixedSize(100, 50);
```

#### 设置样式

```cpp
label->setStyleSheet("background-color:red;");
```

## 6. QString 常见操作

### std::string 转 QString

```cpp
QString qstr = QString::fromStdString(str);
```

### 数字转 QString

```cpp
QString::number(value);
```

### 字符串拼接

```cpp
QString text =
    QString::number(a) + " / " +
    QString::number(b);
```

### 占位符 arg()

```cpp
QString style =
    QString("rgb(%1,%2,%3)")
        .arg(r)
        .arg(g)
        .arg(b);
```

## 7. 信号与槽（Signals & Slots）

Qt 最核心机制。

### connect 基本写法

```cpp
connect(sender,
        &Sender::signal,
        receiver,
        &Receiver::slot);
```

### Slider 联动 SpinBox

```cpp
connect(slider,
        &QSlider::valueChanged,
        spinBox,
        &QSpinBox::setValue);
```

### 反向联动

```cpp
connect(spinBox,
        QOverload<int>::of(&QSpinBox::valueChanged),
        slider,
        &QSlider::setValue);
```

### 定时器 connect

```cpp
connect(timer_,
        &QTimer::timeout,
        this,
        &MainWindow::update_timer);
```

## 8. QTimer 定时器

### 创建

```cpp
timer_ = new QTimer(this);
```

### 启动

```cpp
timer_->start(1000);
```

单位：

```
毫秒
```

1000 = 1秒

### 停止

```cpp
timer_->stop();
```

### timeout 信号

```cpp
connect(timer_,
        &QTimer::timeout,
        this,
        &MainWindow::update_timer);
```

## 9. qDebug 调试输出

### 基本输出

```cpp
qDebug() << "hello";
```

### 输出变量

```cpp
qDebug() << value;
```

### 输出多个值

```cpp
qDebug() << x << y << z;
```

### 调试槽函数

```cpp
qDebug() << "onColorChanged";
```

## 10. QColor 与 QPixmap

### 创建颜色

```cpp
QColor color(r, g, b);
```

### 创建图片

```cpp
QPixmap pix(64, 64);
```

### 填充颜色

```cpp
pix.fill(color);
```

### 显示图片

```cpp
label->setPixmap(pix);
```

## 11. blockSignals

临时阻止信号。

### 用法

```cpp
comboBox->blockSignals(true);
```

恢复：

```cpp
comboBox->blockSignals(false);
```

### 常见用途

初始化默认值时：

避免触发槽函数。

## 12. 常见默认值设置

### 设置默认选项

```cpp
comboBox->setCurrentIndex(1);
```

### 判断后设置

```cpp
if (list.size() > 1)
    comboBox->setCurrentIndex(1);
else
    comboBox->setCurrentIndex(0);
```

## 13. Qt 常见对齐方式

### 水平

```cpp
Qt::AlignLeft
Qt::AlignCenter
Qt::AlignRight
```

### 垂直

```cpp
Qt::AlignTop
Qt::AlignBottom
```

## 14. 常见 UI 初始化套路

```cpp
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setupUi(this);

    init_widgets();

    init_layouts();

    init_connections();
}
```

大型项目非常常见。

## 15. Qt 开发高频套路总结

### ① 控件联动

```cpp
slider <-> spinBox
```

### ② 定时刷新

```cpp
QTimer
```

### ③ 动态样式

```cpp
setStyleSheet()
```

### ④ 文本更新

```cpp
setText()
```

### ⑤ 图片显示

```cpp
QPixmap
```

### ⑥ 数据转换

```cpp
QString::number()
fromStdString()
```

### ⑦ 调试

```cpp
qDebug()
```

## 16. Qt 初学最重要的知识

优先掌握：

1. Widgets
2. Layout
3. Signals & Slots
4. QString
5. QTimer
6. QPainter（后期）
7. Model/View（后期）

## 17. 最经典 Qt 一句话

Qt 本质：

```
控件 + 布局 + 信号槽
```

几乎所有 GUI 都是这个组合。
