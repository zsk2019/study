#include <iostream>

using namespace std;

class Strategy {
public:
  virtual ~Strategy() {}
  virtual void exec() = 0;
};

class StrategyA : public Strategy {
public:
  void exec() { cout << "StrategyA::exec()" << endl; }
};

class StrategyB : public Strategy {
public:
  void exec() { cout << "StrategyB::exec()" << endl; }
};

class Context {
public:
  explicit Context(Strategy *strategy) : _strategy(strategy) {}
  void set_strategy(Strategy *strategy) { _strategy = strategy; }
  void exec() { _strategy->exec(); }

private:
  Strategy *_strategy;
};

int main() {

  StrategyA Sa;
  StrategyB Sb;

  Context Ca(&Sa);
  Context Cb(&Sb);
  Ca.exec();
  Cb.exec();
}