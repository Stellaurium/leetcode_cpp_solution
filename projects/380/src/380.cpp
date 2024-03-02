#include "Set.h"

class RandomizedSet {
  private:
    Set<int> s;

  public:
    RandomizedSet() {}

    bool insert(int val) { return s.insert(val); }

    bool remove(int val) { return s.remove(val); }

    int getRandom() { return s.getRandom(); }
};

int main(){
    RandomizedSet obj{};
    // 这个测试样例实在是太难写了
    return 0;
}