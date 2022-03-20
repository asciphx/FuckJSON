# FuckJSON[v1.4]
> 元宇宙的c++的序列化与反序列化JSON工具

## 优势
- [x] 基于最现代化的JSON库，nlohman JSON。
- [x] 只需要原生的结构体，简单的两句宏即可搞定。
- [x] 强大静态反射，最高性能(相对于其他语言)，最低开销，最迅速的反应，最容易维护，以及最少代码。
- [x] 解决模块化与互相依赖，循环依赖的问题。
- [x] 纯头文件无需cmake即可直接编译。
- [x] 支持序列化对象或者vector对象到字符串，序列化对象得到JSON，反序列化Json格式字符串到对象。
- [x] 宽松的布尔类型反序列化，包含但不仅限于true、false，还有0，1;

## 模型层
```c++
struct Type;
struct Tab {
  uint32_t id;
  bool ok;
  text<15> name;
  tm date;
  vector<Type> types;
  Type* type;
  Tab(uint32_t a = 0, bool b = false, const char* c = "", tm d = now(), vector<Type> e = {}, Type* f = nullptr) :
	id(a), ok(b), name(c), date(d), types(e), type(f) {}
  ~Tab() { type = nullptr; }
  SCHEMA(Tab, id, ok, name, date, types, type)
};
FUCKJSON(Tab, id, ok, name, date, types, type)
struct Type {
  uint8_t id;
  text<10> language;
  double bigBlob;
  vector<Tab> tabs;
  Tab* tab;
  Type(uint8_t a = 0, const char* b = "", double c = 0, vector<Tab> d = {}, Tab* e = nullptr) :
	id(a), language(b), bigBlob(c), tabs(d), tab(e) {}
  ~Type() { tab = nullptr; }
  SCHEMA(Type, id, language, bigBlob, tabs, tab)
};
FUCKJSON(Type, id, language, bigBlob, tabs, tab)
```

## 特征
 - 模块化
 - 仅头文件
 - 低代码
 - 高性能

## 前提
```shell
g++ -std=c++17 *.cc -o main -I./src -O3
g++ -std=c++17 *.cpp -o o2o -I./src -O3
```
# 支持的编译器（最低版本）:
    - Linux: G++ 9.2, Clang++ 9.0
    - MacOS: Apple clang version 12.0.0 
    - Windows: MSVC C++ compiler version 1930.

### Attributions
    uses the following libraries.

	json 

    https://github.com/nlohmann/json

    Copyright (c) 2013-2021 Niels Lohmann
    Permission is hereby granted, free of charge, to any person obtaining a copy
    of this software and associated documentation files (the "Software"), to deal
    in the Software without restriction, including without limitation the rights
    to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the Software is
    furnished to do so, subject to the following conditions:

    The above copyright notice and this permission notice shall be included in all
    copies or substantial portions of the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
    IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
    FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
    LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
    OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
