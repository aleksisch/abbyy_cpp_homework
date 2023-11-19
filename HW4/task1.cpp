#include <mutex>
#include <shared_mutex>
#include <vector>
#include <thread>
#include <iostream>

class Foo1 {
  int value;
  mutable std::mutex mutex;
public:
  int Get() const {
    std::unique_lock guard(mutex);
    return value;
  }

  void Set(int newValue) {
    std::unique_lock guard(mutex);
    value = newValue;
  }
};

class Foo2 {
  int value;
  mutable std::shared_mutex shared_m;
public:
  int Get() const {
    std::shared_lock guard(shared_m);
    return value ;
  }
  void Set(int newValue) {
    std::unique_lock guard(shared_m);
    value = newValue;
  }
};

template <typename T>
void measure(const int rw_ratio = 1) {
  std::vector<std::thread> threads;
  T foo1;
  threads.reserve(8);
  for (int i = 0; i < 8; i++) {
    threads.emplace_back([&]() mutable {
      for (int i = 0; i < 10000000; i++) {
        auto val = foo1.Get();
        val += 1;
        if (val % rw_ratio == 0) {
          foo1.Set(val);
        }
      }
    });
  }
  for (auto &thread: threads) {
    thread.join();
  }
}

int main() {
  const auto now11 = std::chrono::high_resolution_clock::now();
  measure<Foo1>(1);
  const auto end11 = std::chrono::high_resolution_clock::now();

  const auto now125 = std::chrono::high_resolution_clock::now();
  measure<Foo2>(25);
  const auto end125 = std::chrono::high_resolution_clock::now();

  const auto now21 = std::chrono::high_resolution_clock::now();
  measure<Foo1>(1);
  const auto end21 = std::chrono::high_resolution_clock::now();

  const auto now225 = std::chrono::high_resolution_clock::now();
  measure<Foo2>(25);
  const auto end225 = std::chrono::high_resolution_clock::now();

  using std::chrono::duration_cast;
  using std::chrono::milliseconds;
  std::cout << duration_cast<milliseconds>(end11 - now11).count() << std::endl
            << duration_cast<milliseconds>(end125 - now125).count() << std::endl
            << duration_cast<milliseconds>(end21 - now21).count() << std::endl
            << duration_cast<milliseconds>(end225 - now225).count() << std::endl;
  /**
   * It prints smth like:
   *
   * 20229 --- Foo1 rw_ratio 1
   * 5226 --- Foo2 rw_ratio 1
   * 22022 --- Foo1 rw_ratio 25
   * 4617 --- Foo2 rw_ratio 25
   *
   * First two launches is same number of read-write operations.
   * Other 2 launches with read-write ratio 25 (on 25 read 1 write)
   * Probably, different time with different rw-ratio might be explained by branch-predictor.
   *
   * Time with shared mutex 4 times lower then with regular one. This can be explained by
   * lack of synchronization for read operation with shared mutex.
   */
  return 0;
}