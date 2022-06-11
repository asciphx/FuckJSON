#include "module.hpp"
/* FuckJSON https://github.com/asciphx/FuckJSON Copyright (c) 2021-2022 Asciphx */
//Many to many
int main() {
  Tab t{ 1, true, "reflect🪂", now(), vector<Type>{ Type{ 1,"model🦼" } }, nullptr };
  std::string s; s << &t;//Support direct conversion of class or struct to JSON string
  std::cout << s << '\n';//or cout << t << '\n';
  json::parse(t, R"(
{
  "id": 3,
  "ok": false,
  "name": "FuckJSON🛬",
  "date": "2021-09-08 01:04:30",
  "types": [{
    "id": 1,
    "language": "c++🏎"
  }, {
    "id": 2,
    "language": "js🛺",
    "tabs": [{
      "id": 1,
      "name": "faker🛴"
    }, {
      "id": 2,
      "name": "bonkers🚒"
    }]
  }, {
    "id": 3,
    "language": "rust🚟"
  }]
}
)");
  t.types[1].language = "go programing";
  t.types[1].tabs[0].name = "Megatron🛹";
  t.types[1].tabs[0].types = vector<Type>{ Type{ 1,"typescript🚁" }, Type{ 2,"best in the universe" } };
  std::cout << json(t).dump(2) << '\n';
  return 0;
}