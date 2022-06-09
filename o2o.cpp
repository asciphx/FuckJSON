#include <src/fuckJson.hpp>
/* FuckJSON https://github.com/asciphx/FuckJSON Copyright (c) 2021-2022 Asciphx */
//One to one
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
class Tab;
class Type;

Class(Type)
uint8_t id;
text<10> language;
double bigBlob;
box<Tab> tab;
FUCKJSON(Type, id, language, bigBlob, tab)

Class(Tab)
uint32_t id;
bool ok;
text<15> name;
tm date = now();
box<Type> type;
FUCKJSON(Tab, id, ok, name, date, type)

int main() {
  Tab t{ 1, true, "ref1", now(), Type{1,"model1",3.141593} };
  Tab a{ 1, true, "ref2", now() };
  t.type().tab = a;
  t.type().language = "🎨🧵🎱🕶👓👑✈🛸🛰🚀";
  cout << t << '\n';
  json::parse(t, R"(
{
  "id": 3,
  "ok": false,
  "name": "干杯🍻🍺!",
  "date": "2021-09-08 01:04:30",
  "type":  {
    "bigBlob": 0.1,
    "id": 1,
    "language": "元宇宙🌀🌌🪐!"
  }
}
)");//deserialization a layer one-to-one, because multiple level pointer passes are lost
  cout << json(t).dump(2) << '\n';
  return 0;
}