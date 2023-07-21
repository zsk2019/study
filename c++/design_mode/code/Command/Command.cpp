#include <iostream>
#include <list>
#include <vector>

using namespace std;

class Receiver {
public:
  Receiver(){};
  virtual ~Receiver(){};

  void action1() { cout << "exec action1" << endl; };
  void action2() { cout << "exec action2" << endl; };
};

class Command {
public:
  Command(Receiver *p) : p_recv(p) {}
  virtual void exec() = 0;

protected:
  Receiver *p_recv = nullptr;
};

class ConcreteCommand1 : public Command {
public:
  ConcreteCommand1(Receiver *p) : Command(p) {}
  void exec() { p_recv->action1(); }
};

class ConcreteCommand2 : public Command {
public:
  ConcreteCommand2(Receiver *p) : Command(p) {}
  void exec() { p_recv->action2(); }
};

class Invoker {
private:
  list<Command *> commands;

public:
  void addCommand(Command *c) { commands.push_back(c); }
  void Notify() {
    for (auto c = commands.begin(); c != commands.end(); c++) {
      (*c)->exec();
    }
  }
};

int main() {

  Receiver rev1;
  ConcreteCommand1 cmd1(&rev1);
  ConcreteCommand2 cmd2(&rev1);
  Invoker invok;
  invok.addCommand(&cmd1);
  invok.addCommand(&cmd2);

  invok.Notify();
}