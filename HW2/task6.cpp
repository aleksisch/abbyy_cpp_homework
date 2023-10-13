//
// Created by aleksey on 13.10.2023.
//

#include <type_traits>
#include <string>
#include <iostream>

template<typename T>
concept NumeStrType = requires(T param) {
  requires std::is_integral_v<T> || std::is_floating_point_v<T>;
  { std::to_string(param) };
};

template <NumeStrType T1, NumeStrType T2>
std::string concat(T1 t1, T2 t2) {
  return std::to_string(t1) + std::to_string(t2);
}


int main() {
  std::cout << concat(float(1.), double(2)) << std::endl;
  std::cout << concat(uint8_t(1.), int(2)) << std::endl;
  std::cout << concat(uint16_t(1.), double(2)) << std::endl;
}
