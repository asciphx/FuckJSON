#include "module.hpp"
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
      "name": "🎨🧵🎱🕶👓👑"
    }, {
      "id": 2,
      "name": "你好，杰森！"
    }]
  }, {
    "id": 3,
    "language": "hello干杯🍻🍺!"
  }]
}
)").get<Tab>()).dump().c_str());
  }

  printf("\nuse %.6f seconds", (float)(clock() - start) / CLOCKS_PER_SEC);
  return 0;
}