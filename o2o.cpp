#include "src/macros.hpp"
/* FuckJSON https://github.com/asciphx/FuckJSON Copyright (c) 2021-2022 Asciphx */
//One to one
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
struct Tab;
struct Tab;
struct Type {
  uint8_t id;
  text<10> language;
  double bigBlob;
  Tab* tab = nullptr;
  ~Type() { tab = nullptr; }
  SCHEMA(Type, id, language, bigBlob, tab)
};
FUCKJSON(Type, id, language, bigBlob, tab)
struct Tab {
  uint32_t id;
  bool ok;
  text<15> name;
  tm date = now();
  Type* type = nullptr;
  ~Tab() { type = nullptr; }
  SCHEMA(Tab, id, ok, name, date, type)
};
FUCKJSON(Tab, id, ok, name, date, type)
int main() {
  Type ty{ 1,"model1" }, ty2{ 2,"model2",3.141593 };
  Tab t{ 1, true, "ref1", now(), &ty };
  Tab a{ 1, true, "ref2", now() };
  t.type->tab = &a; a.type = &ty2;
  t.type->language = "Meta universe";
  cout << t << '\n';
  t = json::parse(R"(
{
  "id": 3,
  "ok": false,
  "name": "FuckJSON",
  "date": "2021-09-08 01:04:30",
  "type":  {
    "bigBlob": 0.0,
    "id": 1,
    "language": "Meta unive"
  }
}
)").get<Tab>();// cout << t << '\n';
  t.name = "Megatron";
  cout << json(t).dump(2) << '\n';
  return 0;
}