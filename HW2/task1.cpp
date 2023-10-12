//
// Created by aleksey on 13.10.2023.
//

#include <ranges>
#include <iostream>

int main() {
  auto nums = std::views::iota(10, 100)
    | std::views::transform([](auto x){ return x * x; })
    | std::views::filter([](auto x) { return x % 5 != 0; })
    | std::ranges::views::transform([](int x) { return std::to_string(x); });
  for (const auto &x : nums) {
    std::cout << x << std::endl;
  }
}
