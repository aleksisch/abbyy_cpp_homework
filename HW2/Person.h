//
// Created by aleksey on 13.10.2023.
//

#pragma once

#include <iostream>

struct Person {
  std::string name;
  std::string surname;

  friend std::ostream & operator << (std::ostream &cout, const Person &self) {
    cout << self.name << " " << self.surname;
    return cout;
  }
};

using PersonAge = std::pair<Person, int>;

