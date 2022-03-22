#include "src/macros.hpp"
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
class Tab;
class Type;

class(Tab)
uint32_t id;
bool ok;
text<15> name;
tm date;
vector<Type> types;
Type* type;
Tab(uint32_t a = 0, bool b = false, const char* c = "", tm d = now(), vector<Type> e = {}, Type* f = nullptr) :
  id(a), ok(b), name(c), date(d), types(e), type(f) {}
~Tab() { type = nullptr; }
FUCKJSON(Tab, id, ok, name, date, types, type)

class(Type)
uint8_t id;
text<10> language;
double bigBlob;
vector<Tab> tabs;
Tab* tab;
Type(uint8_t a = 0, const char* b = "", double c = 0, vector<Tab> d = {}, Tab* e = nullptr) :
  id(a), language(b), bigBlob(c), tabs(d), tab(e) {}
~Type() { tab = nullptr; }
FUCKJSON(Type, id, language, bigBlob, tabs, tab)