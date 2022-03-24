#include "src/macros.hpp"
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
class Tab;
class Type;

Class(Tab)
uint32_t id;
bool ok;
text<15> name;
vector<Type> types;
Tab(uint32_t a = 0, bool b = false, const char* c = "", vector<Type> e = {}) :
  id(a), ok(b), name(c), types(e) {}
FUCKJSON(Tab, id, ok, name, types)

Class(Type)
uint8_t id;
text<10> language;
vector<Tab> tabs;
Type(uint8_t a = 0, const char* b = "", vector<Tab> d = {}) :
  id(a), language(b), tabs(d) {}
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
)").get<Tab>()).dump().c_str());
  }

  printf("\nuse %.6f seconds", (float)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}