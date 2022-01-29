#include "src/macros.hpp"
/* FuckJSON https://github.com/asciphx/FuckJSON Copyright (c) 2021-2022 Asciphx */
//One to one
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
struct Tab;
struct Type {
  uint8_t id;
  text<10> language;
  double bigBlob;
  Tab* tab;
  Type(uint8_t a = 0, const char* b = "", double c = 0, Tab* d = {}) :
	id(a), language(b), bigBlob(c), tab(d) {}
  const static char* $[];
};
FUCKJSON(Type, id, language, bigBlob, tab)
struct Tab {
  uint32_t id;
  bool ok;
  text<15> name;
  tm date;
  Type* type;
  Tab(uint32_t a = 0, bool b = false, const char* c = "", tm d = now(), Type* e = {}) :
	id(a), ok(b), name(c), date(d), type(e) {}
  const static char* $[];
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
)").get<Tab>(); cout << t << '\n';
  t.name = "Megatron";
  t.type = &ty;
  cout << json(t).dump(2) << '\n';
  return 0;
}