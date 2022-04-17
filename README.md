# FuckJSON[v1.8]
> Meta universe's C++ serialization and deserialization JSON tool

## Advantage
- [x] Based on the most modern JSON library, nlohman JSON.
- [x] You only need the original structure and two macro.
- [x] Powerful static reflection, maximum performance(relative to other languages), minimum overhead, the fastest response, the easiest to maintain, and the low code.
- [x] Now, the problems of modularity, interdependence and circular dependency have been solved.
- [x] Pure header files can be compiled directly without cmake
- [x] Supports serializing objects or vector objects to strings, serializing objects to get JSON, and deserializing JSON format strings to objects.
- [x] Loose boolean type deserialization, including but not limited to true, false, and 0, 1
- [x] Support direct conversion of class or struct to JSON string
- [x] Allow the varchar type of the database, adopt the text < > scheme and be accurate to each character to ensure the maximum length and data security

## Model layer
```c++
class Tab;
class Type;

Class(Tab)
uint32_t id;
bool ok;
text<15> name;
tm date;
vector<Type> types;
Type* type;
Tab(uint32_t a = 0, bool b = false, const char* c = "", tm d = now(), vector<Type> e = {}, Type* f = nullptr) :
  id(a), ok(b), name(c), date(d), types(e), type(f) {}
~Tab() { type = nullptr; }
FUCKJSON(Tab, id, ok, name, date, types, type)

Class(Type)
uint8_t id;
text<10> language;
double bigBlob;
vector<Tab> tabs;
Tab* tab;
Type(uint8_t a = 0, const char* b = "", double c = 0, vector<Tab> d = {}, Tab* e = nullptr) :
  id(a), language(b), bigBlob(c), tabs(d), tab(e) {}
~Type() { tab = nullptr; }
FUCKJSON(Type, id, language, bigBlob, tabs, tab)
```

## Examples
> Suppose there is an object Tab above
```c++
Tab t{ 1, true, "reflect", now() };
```
### Serialize the object into a JSON string
```c++
std::string s; s << &t;
```
### Serialize objects into JSON
```c++
json(t);
```
### Deserialize JSON strings into objects [keep a layer of pointers that can be deserialized]
```c++
json::parse(t, R"(
{
  "id": 3,
  "ok": false,
  "name": "🍻🍺!",
  "date": "2021-09-08 01:04:30",
  "type":  {
    "bigBlob": 0.1,
    "id": 1,
    "language": "Meta🌀🌌🪐!"
  }
}
)");//type is {"bigBlob": 0.1,"id": 1,"language":"Meta🌀🌌🪐!"}
```
### Deserialize JSON string to object [get specifies type and property does not contain pointer]
```c++
t = json::parse(R"(
{
  "id": 3,
  "ok": false,
  "name": "🍻🍺!",
  "date": "2021-09-08 01:04:30",
  "type":  {
    "bigBlob": 0.1,
    "id": 1,
    "language": "Meta🌀🌌🪐!"
  }
}
)").get<Tab>();//type is null
```

## Features
- Modularization
- Header files only
- Low code
- High performance

## Premise
```shell
g++ -std=c++17 main.cc -o main -I./ -O3
g++ -std=c++17 *.cpp -o o2o -I./ -O3
g++ -std=c++17 benchmark.cc -o benchmark -I./ -O3
g++ -std=c++17 text.cc -o text -I./ -O3
```
# Supported compilers(minimum version):
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
