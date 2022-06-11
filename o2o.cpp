#include <src/fuckJson.hpp>
/* FuckJSON https://github.com/asciphx/FuckJSON Copyright (c) 2021-2022 Asciphx */
//One to one
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
class Tab;
class Type;

Class(Type)
uint8_t id; text<10> language; double bigBlob;
box<Tab> tab;
FUCKJSON(Type, id, language, bigBlob, tab)

Class(Tab)
uint32_t id; bool ok; text<15> name; tm date = now();
box<Type> type;
FUCKJSON(Tab, id, ok, name, date, type)

int main() {
  Tab t{ 1, true, "ref1", now(), Type{1,"model1",3.141593} };//Up to 2 layers
  Tab a{ 1, true, "ref2", now() };
  t.type().tab = a;
  t.type().language = "🎨🧵🎱🕶👓👑✈🛸🛰🚀";
  cout << t << '\n';//std::vector simply cannot nest box, but box can nest box and std::vector
  json::parse(t, R"(
{
  "id": 3,
  "ok": false,
  "name": "🍻🍺!",
  "date": "2021-09-08 01:04:30",
  "type":  {
    "bigBlob": 0.1,
    "id": 4,
    "language": "元宇宙🌀🌌🪐!",
    "tab":  {
      "id": 5,
      "name": "!!!!!",
      "type":  {
        "bigBlob": 0.2,
        "id": 6,
        "language": "元宇宙2🌀🌌🪐!",
        "tab":  {
          "id": 7,
          "name": "!!!!!!!!",
          "type":  {
            "bigBlob": 0.3,
            "id": 8,
            "language": "元宇宙4🌀🌌🪐!",
            "tab":  {
              "id": 9,
              "name": "!!!!!!!!!!"
            }
          }
        }
      }
    }
  }
}
)");//deserialization a layer one-to-one
  cout << json(t).dump(2) << '\n';
  return 0;
}