//
// Created by aleksey on 13.10.2023.
//

#include <ranges>
#include <iostream>
#include <vector>

#include "Person.h"

template <std::input_iterator Iter>
auto sum(Iter begin, Iter end) {
  auto sum{*begin}; // empty view?)
  for (auto iter{++begin}; iter != end; iter++) {
    sum += *iter;
  }
  return sum;
}

template <std::ranges::sized_range Rng>
//requires (Rng::value_type && std::is_same_v<typename Rng::value_type, std::pair<Person, int>>)
double avg_age(Rng &&val) {
  auto res = val
  | std::views::transform([](auto pers) { return pers.second; })
  | std::views::filter([](const auto age){ return age < 12 || age > 65; });
  return sum(res.begin(), res.end()) / std::distance(std::begin(res), std::end(res));;
}

int main() {
  using PersonData = std::pair<Person, int>;
  std::vector<PersonData> data = {
    {{.name = "a", .surname = "b"}, 10},
    {{.name = "c", .surname = "d"}, 22},
    {{.name = "c", .surname = "d"}, 100}
  };
  std::cout << avg_age(data);
}
