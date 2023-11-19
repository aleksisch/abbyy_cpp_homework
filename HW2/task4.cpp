//
// Created by aleksey on 13.10.2023.
//

#include <ranges>
#include <iostream>
#include <algorithm>
#include <vector>

void with_for() {
  std::vector<int> in;
  for (const auto& s: std::ranges::istream_view<int>(std::cin)) {
    if (s == -1) {
      std::copy(in.begin(), in.end(), std::ostream_iterator<int>(std::cout, " "));
      return;
    }
    in.emplace_back(s);
  }
}

void in_line() {
  auto ins = std::ranges::istream_view<int>(std::cin)
    | std::views::take_while([] (int x) { return x != -1; });
  std::ranges::copy(ins, std::ostream_iterator<int>(std::cout, " "));
}

int main() {
  with_for();
}