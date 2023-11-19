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

    auto yield_value(int val){
      m_value.emplace(val);
      return awaiter{this};
    }

    std::optional<int> m_value;
  };

  struct awaiter : std::suspend_always {
    constexpr int await_resume() const { return m_p->m_value.value(); }

    constexpr awaiter(promise_type* p) : m_p(p) {}
    promise_type* m_p;
  };


  ~Coro() {
    if (coro_)
      coro_.destroy();
  }

  std::coroutine_handle<promise_type> coro_;
};

Coro myCoro() {
  std::cout << "Hello, World!" << std::endl;
  co_yield 1;
  std::cout << "I am coroutine!" << std::endl;
  co_yield 2;
  std::cout << "Nice to meet you!" << std::endl;
  co_yield 3;
  std::cout << "Goodbye!" << std::endl;
  co_return;
}

int main() {
  Coro coro = myCoro();
  coro.coro_.resume();
  coro.coro_.resume();
  coro.coro_.resume();
}