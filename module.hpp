#include "src/macros.hpp"
static int RES_INIT = orm::InitializationOrm();
//模块化，以及循环依赖，是难点(Modularity and circular dependency are the difficulties)
using namespace std; using namespace orm;
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
};
FUCKJSON(Tab, id, ok, name, date, types)
struct Type {
  uint8_t id;
  text<10> language;
  double bigBlob;
  vector<Tab> tabs;
  Type(uint8_t a = 0, const char* b = "", double c = 0, vector<Tab> d = {}) :
	id(a), language(b), bigBlob(c), tabs(d) {}
  const static char* $[];
};
FUCKJSON(Type, id, language, bigBlob, tabs)