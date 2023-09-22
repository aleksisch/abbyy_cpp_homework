#include <vector>
#include <string>
#include <set>

class Solution {
public:
  std::vector<std::string> generateParenthesis(int n) {
    std::set<std::string> last;
    last.insert("()");
    for (size_t i = 1; i < n; i++) {
      last = genPar(last);
    }
    return {last.begin(), last.end()};
  }
private:
  std::set<std::string> genPar(const std::set<std::string> &prev) {
    std::set<std::string> result;
    for (const auto &par: prev) {
      result.insert("()" + par);
      size_t counter = 0;
      for (int i = 0; i < par.size(); i++) {
        const auto c = par[i];
        switch (c) {
          case '(':
            counter++;
          case ')':
            counter--;
        }
        if (counter == 0) {
          result.insert("(" + par.substr(0, i + 1) + ")" + par.substr(i + 1));
        }
      }
      result.insert(par + "()");
    }
    return result;
  }
};