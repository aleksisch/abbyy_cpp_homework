//
// Created by aleksey on 17.11.2023.
//

#include <coroutine>
#include <exception>
#include <iostream>
#include <optional>

struct Coro {
  struct promise_type {

    auto initial_suspend() const noexcept {
      return std::suspend_never{};
    }

    auto final_suspend() const noexcept {
      return std::suspend_always{};
    }

    Coro get_return_object() noexcept {
      return Coro{std::coroutine_handle<promise_type>::from_promise(*this)};
    }

    void unhandled_exception() noexcept {
      std::terminate();
    }

    void return_void(){}

    std::optional<int> m_value;
  };


  ~Coro() {
    if (coro_)
      coro_.destroy();
  }

  std::coroutine_handle<promise_type> coro_;
};

Coro myCoro() {
  std::cout << "Hello, World!" << std::endl;
  co_await std::suspend_always();
  std::cout << "I am coroutine!" << std::endl;
  co_await std::suspend_always();
  std::cout << "Nice to meet you!" << std::endl;
  co_await std::suspend_always();
  std::cout << "Goodbye!" << std::endl;
  co_return;
}

int main() {
  Coro coro = myCoro();
  coro.coro_.resume();
  coro.coro_.resume();
  coro.coro_.resume();
}