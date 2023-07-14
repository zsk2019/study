#include <mutex>

class Singleton {
public:
  Singleton(const Singleton &) = delete;

  static Singleton &getInstance() {
    // 局部的静态变量是非线程安全的，非局部静态变量是线程安全的
    static Singleton instance;
    return instance;
  }
  /*
  其他函数和数据
  */
private:
  Singleton() {}  // 声明为私有，防止外部创建
  ~Singleton() {} // 声明为私有，防止外部delete
};
/*
栈上创建
非线程安全
懒汉模式
*/
/*=================================================================================*/

class Singleton2 {
public:
  Singleton2(const Singleton2 &) = delete;
  static Singleton2 *getInstance() {
    if (instance == nullptr) {
      instance = new Singleton2();
    }
    return instance;
  }
  /*
  其他函数和数据
  */

private:
  Singleton2() {}
  ~Singleton2() {
    if (instance != nullptr) {
      delete instance;
      instance = nullptr;
    }
  }
  static Singleton2 *instance;
};
Singleton2 *Singleton2::instance = nullptr;

/*
堆上创建
非线程安全
懒汉模式
*/
/*=================================================================================*/
class Singleton3 {
private:
  static Singleton3 instance;
  Singleton3(){};
  Singleton3(const Singleton3 &) = delete;
  ~Singleton3(){};

public:
  static Singleton3 *getInstance() { return &instance; }
  /*
 其他函数和数据
 */
};
Singleton3 Singleton3::instance;
/*
线程安全
栈上创建
自动销毁
初始化注意使用其他静态变量的情况，其他静态变量可能未初始化
*/

class Singleton4 {
private:
  Singleton4(){};
  Singleton4(const Singleton4 &other) = delete;
  ~Singleton4() { destoryInstance(); };
  static Singleton4 *instance;
  static std::mutex mutx;

public:
  static Singleton4 *getInstance();
  static void destoryInstance();
};

Singleton4 *Singleton4::instance = nullptr;

Singleton4 *Singleton4::getInstance() {
  std::lock_guard<std::mutex> lock(mutx);
  if (instance == nullptr) {
    instance = new Singleton4();
  }
  return instance;
}

void Singleton4::destoryInstance() {
  std::lock_guard<std::mutex> lock(mutx);
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

/*
线程安全
堆上创建
可手动销毁
锁的代价过高
*/

class Singleton5 {
private:
  Singleton5(){};
  Singleton5(const Singleton5 &other) = delete;
  ~Singleton5() { destoryInstance(); };
  static Singleton5 *instance;
  static std::mutex mutx;

public:
  static Singleton5 *getInstance();
  static void destoryInstance();
};

Singleton5 *Singleton5::instance = nullptr;

Singleton5 *Singleton5::getInstance() {

  if (instance == nullptr) {
    std::lock_guard<std::mutex> lock(mutx);
    if (instance == nullptr) {
      instance = new Singleton5();
    }
  }
  return instance;
}

void Singleton5::destoryInstance() {
  std::lock_guard<std::mutex> lock(mutx);
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

/*
线程非安全
堆上创建
可手动销毁
内存读写reorder不安全
*/

class Singleton6 {
private:
  Singleton6(){};
  Singleton6(const Singleton6 &other) = delete;
  ~Singleton6() { destoryInstance(); };
  static std::atomic<Singleton6 *> instance;
  static std::mutex mutx;

public:
  static Singleton6 *getInstance();
  static void destoryInstance();
};

Singleton6 *Singleton6::instance = nullptr;
std::atomic<Singleton6 *> Singleton6::instance;

void Singleton6::destoryInstance() {
  std::lock_guard<std::mutex> lock(mutx);
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

Singleton6 *Singleton6::getInstance() {
  Singleton6 *tmp = instance.load(std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_acquire); // 获取内存fence
  if (tmp == nullptr) {
    std::lock_guard<std::mutex> lock(mutx);
    tmp = instance.load(std::memory_order_relaxed);
    if (tmp == nullptr) {
      tmp = new Singleton6;
      std::atomic_thread_fence(std::memory_order_release); // 释放内存fence
      instance.store(tmp, std::memory_order_relaxed);
    }
  }
  return tmp;
}

/*
线程安全
堆上创建
可手动销毁
解决内存读写reorder不安全
*/