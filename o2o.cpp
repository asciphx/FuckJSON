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
Tab* tab = nullptr;
~Type() { tab = nullptr; }
FUCKJSON(Type, id, language, bigBlob, tab)

Class(Tab)
uint32_t id;
bool ok;
text<15> name;
tm date = now();
Type* type = nullptr;
~Tab() { type = nullptr; }
FUCKJSON(Tab, id, ok, name, date, type)

int main() {
  Type ty{ 1,"model1",3.141593 };
  Tab t{ 1, true, "ref1", now(), &ty };
  Tab a{ 1, true, "ref2", now() };
  t.type->tab = &a;
  t.type->language = "🎨🧵🎱🕶👓👑✈🛸🛰🚀";
  cout << t.type << '\n';
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