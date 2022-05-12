#include <my_unordered_set.h>
#include <algorithm>
#include <vector>
int main() {
  std::vector<int> abc = {1, 2, 3, 4, 5};
  unordered_set<int> x{5, 6, 7, 4,88,8,10,9,23}, y, z(x), d;
  for (auto i : x) std::cout << i << " ";
  std::cout << '\n';
  std::cout << *std::find_if(x.begin(), x.end(), [](int val){return val % 2 == 0;});
  std::for_each(x.begin(), x.end(), [](int val){if(val % 2 == 0) std::cout << val << '\n';});

}
