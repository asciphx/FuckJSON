#include <src/fuckJson.hpp>
static int RES_INIT = orm::InitializationOrm();
using namespace std; using namespace orm;
class Tab;
class Type;

Class(Tab)
uint32_t id; bool ok; text<15> name; tm date = now();
vector<Type> types;
box<Type> type;
//Tab(uint32_t a = 0, bool b = false, const char* c = "", tm d = now(), vector<Type> e = {}, box<Type> f = nullptr) :
//  id(a), ok(b), name(c), date(d), types(e), type(f) {}
FUCKJSON(Tab, id, ok, name, date, types, type)

Class(Type)
uint8_t id; text<10> language; double bigBlob;
vector<Tab> tabs;
box<Tab> tab;
//Type(uint8_t a = 0, const char* b = "", double c = 0, vector<Tab> d = {}, box<Tab> e = nullptr) :
//  id(a), language(b), bigBlob(c), tabs(d), tab(e) {}
FUCKJSON(Type, id, language, bigBlob, tabs, tab)