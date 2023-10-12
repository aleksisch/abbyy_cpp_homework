//
// Created by aleksey on 13.10.2023.
//

#include <vector>
#include <ranges>

#include "Person.h"

template <typename InputIter , typename OutputIter>
void myCopy (InputIter begin, InputIter end, OutputIter target) {
  for ( auto iter { begin }; iter != end ; ++ iter , ++ target ) { * target = * iter ; }
}

template <std::ranges::sized_range Rng>
void print(Rng &&val) {

  auto top_people = val
                    | std::views::transform([](const auto &pers) { return pers.first; })
                    | std::ranges::views::take(4);

  auto surname_top = top_people
                     | std::views::transform([](const auto &pers) { return pers.surname; });

  myCopy(top_people.begin(), top_people.end(), std::ostream_iterator<Person>(std::cout, "\n"));
  myCopy(surname_top.begin(), surname_top.end(), std::ostream_iterator<std::string>(std::cout, "\n"));
}


int main() {
  std::vector<PersonAge> data = {
    {{.name = "1", .surname = "11"}, 10},
    {{.name = "2", .surname = "12"}, 22},
    {{.name = "3", .surname = "13"}, 100},
    {{.name = "4", .surname = "14"}, 100},
    {{.name = "5", .surname = "15"}, 100},
    {{.name = "6", .surname = "16"}, 100},
    {{.name = "7", .surname = "17"}, 100},
  };
  print(data);
}