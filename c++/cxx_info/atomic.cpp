#include <atomic>
#include <iostream>
#include <thread>

std::atomic<int> counter(0); // 原子整型变量

void incrementCounter() {
  for (int i = 0; i < 100000; ++i) {
    counter.fetch_add(1, std::memory_order_relaxed); // 原子递增
  }
}

int main() {
  std::thread t1(incrementCounter);
  std::thread t2(incrementCounter);

  t1.join();
  t2.join();

  std::cout << "Counter value: " << counter << std::endl;

  return 0;
}
