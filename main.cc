#include "module.hpp"
/* FuckJSON https://github.com/asciphx/FuckJSON Copyright (c) 2021-2022 Asciphx */
int main() {
  Tab t{ 1, true, "静态反射", now(), vector<Type>{ Type{ 1,"模块化" } } };//初始化结构体
  t = json::parse(R"(
{
  "id": 3,
  "ok": false,
  "name": "序列化与反序列化",
  "date": "2021-09-08 01:04:30",
  "types": [{
    "id": 1,
    "language": "c++"
  }, {
    "id": 2,
    "language": "js",
    "tabs": [{
      "id": 1,
      "name": "fuckjson!"
    }, {
      "id": 2,
      "name": "fastest!"
    }]
  }, {
    "id": 3,
    "language": "rust"
  }]
}
)").get<Tab>();//直接将json格式的字符串反序列化成原对象
  t.types[1].language = "go programing";//text字段有最大长度限制，超出的部分将会丢弃
  t.types[1].tabs[0].name = "Megatron";//直接在结构体里面修改即可
  t.types[1].tabs[0].types = vector<Type>{ Type{ 1,"typescript" }, Type{ 2,"wtf!" } };//赋值
  //打印json反序列化结构体，后面结构体序列化成json，再以dump(2)格式化输出打印
  cout << &t << '\n' << json(t).dump(2) << '\n';
  return 0;
}