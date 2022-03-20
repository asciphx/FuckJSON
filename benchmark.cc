#include "src/macros.hpp"
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
struct Tab;
struct Type;
struct Tab {
  uint32_t id;
  bool ok;
  text<15> name;
  vector<Type> types;
  Tab(uint32_t a = 0, bool b = false, const char* c = "", vector<Type> e = {}) :
	id(a), ok(b), name(c), types(e) {}
  SCHEMA(Tab, id, ok, name, types)
};
FUCKJSON(Tab, id, ok, name, types)
struct Type {
  uint8_t id;
  text<10> language;
  vector<Tab> tabs;
  Type(uint8_t a = 0, const char* b = "", vector<Tab> d = {}) :
	id(a), language(b), tabs(d) {}
  SCHEMA(Type, id, language, tabs)
};
FUCKJSON(Type, id, language, tabs)
int main() {
  clock_t start = clock();
  for (size_t i = 0; i < 1000; ++i) {
    puts(json(json::parse(R"(
{
  "id": 3,
  "ok": false,
  "name": "FuckJSON",
  "types": [{
    "id": 1,
    "language": "sql"
  }, {
    "id": 2,
    "language": "css",
    "tabs": [{
      "id": 1,
      "name": "wtf!"
    }, {
      "id": 2,
      "name": "stupid!"
    }]
  }, {
    "id": 3,
    "language": "idiot!"
  }]
}
)").get<Tab>()).dump(2).c_str());
  }
  printf("\nuse %.6f seconds", (float)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}