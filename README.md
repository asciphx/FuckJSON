﻿# FuckJSON
> A c++ serialization and deserialization JSON tool

## Advantage
- [x] Based on the most modern JSON library, nlohman JSON.
- [x] You only need the original structure, a simple sentence and a macro.
- [x] Powerful static reflection, maximum performance, minimum overhead, the fastest response, the easiest to maintain, and the low code.
- [x] Now, the problems of modularity, interdependence and circular dependency have been solved.
- [x] Pure header files can be compiled directly without cmake
- [x] Supports serializing objects or vector objects to strings, serializing objects to get JSON, and deserializing JSON format strings to objects.

## Model layer
```c++
struct Type;
struct Tab {
  uint32_t id;
  bool ok;
  text<15> name;
  tm date;
  vector<Type> types;
  Tab(uint32_t a = 0, bool b = false, const char* c = "", tm d = now(), vector<Type> e = {}) :
	id(a), ok(b), name(c), date(d), types(e) {}
  const static char* $[];
};//const static char* $[] -> Store the name of the key and the order tuple corresponding
CONSTRUCT(Tab, id, ok, name, date, types)
struct Type {
  uint8_t id;
  text<10> language;
  double bigBlob;
  vector<Tab> tabs;
  Type(uint8_t a = 0, const char* b = "", double c = 0, vector<Tab> d = {}) :
	id(a), language(b), bigBlob(c), tabs(d) {}
  const static char* $[];
};
CONSTRUCT(Type, id, language, bigBlob, tabs)
```

## Features
- Modularization
- Header files only
- Low code
- High performance

## Premise
```shell
g++ -std=c++17 *.cc -o main -I./src
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
