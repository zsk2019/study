#include <iostream>

class Clothe {
public:
  virtual void Show() = 0;
  virtual ~Clothe() {}
};

// 耐克衣服
class NiKeClothe : public Clothe {
public:
  void Show() { std::cout << "我是耐克衣服，时尚我最在行！" << std::endl; }
};

// 基类 鞋子
class Shoes {
public:
  virtual void Show() = 0;
  virtual ~Shoes() {}
};

// 耐克鞋子
class NiKeShoes : public Shoes {
public:
  void Show() { std::cout << "我是耐克球鞋，让你酷起来！" << std::endl; }
};

class Factory {
public:
  virtual Shoes *CreateShoes() = 0;
  virtual Clothe *CreateClothe() = 0;
  virtual ~Factory() {}
};

// 耐克生产者/生产链
class NiKeProducer : public Factory {
public:
  Shoes *CreateShoes() { return new NiKeShoes(); }

  Clothe *CreateClothe() { return new NiKeClothe(); }
};