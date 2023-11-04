#include <vector>
#include <string>
#include <set>

class Solution {
public:
  std::vector<std::string> generateParenthesis(int n) {
    std::set<std::string> last; // Here we store all parenthesis with size i on i-th step
    last.insert("()");
    for (size_t i = 1; i < n; i++) {
      last = addParenthesis(last);
    }
    return {last.begin(), last.end()}; // so, on last step `last` will contain all parnthesis with size n
  }
private:
  /**
   * add 1 level of parenthesis and keep their correctness.
   * @param prev previous parenthesis
   * @return `prev` with additional parenthesis
   */
  std::set<std::string> addParenthesis(const std::set<std::string> &prev) {
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
          // if counter == 0 it means we have 2 correct parts:
          // xy => with new depth level it may be (x)y and x(y)
          const auto &x = par.substr(0, i + 1);
          const auto &y = par.substr(i + 1);
          result.insert("(" + x + ")" + y);
          result.insert(x + "(" + y + ")");
        }
      }
      result.insert(par + "()");
    }
    return result;
  }
};