#include "src/utils/text.hpp"
int main() {
#if _WIN32
  system("chcp 65001 >nul");
#else
  std::locale::global(std::locale("en_US.UTF8"));
#endif
  text<> t(" 🎁🧥👔"); std::vector<int> v{ 1,2,3 };
  //std::cout << t[1] << t[2] << t[3] << (t[4](0) == 0);
  std::cout << t[1] << t[2] << t[3] << ' ' << (t >> v);
  return 0;
}