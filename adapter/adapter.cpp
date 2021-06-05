#include <iostream>
#include <string>

using namespace std;

class Duck {
  public:
    virtual void quack(void) = 0;
    virtual void fly(void) = 0;
};

class MallarDuck : public Duck {
  public:
    void quack(void) override {
      cout << "Quack" << endl;
    }
    void fly(void) override {
      cout << "I'm flying" << endl;
    }
};

class Turkey {
  public:
    virtual void gobble(void) = 0;
    virtual void fly(void) = 0;
};

class WildTurkey: public Turkey {
  public:
    void gobble(void) override {
      cout << "Gobble" << endl;
    }
    void fly(void) override {
      cout << "I'm flying a short distance" << endl;
    }
};

class TurkeyAdapter : public Duck {
  private:
    Turkey *turkey;
  public:
    TurkeyAdapter(Turkey *turkey) { this->turkey = turkey; }
    void quack(void) override { this->turkey->gobble(); }
    void fly(void) override { this->turkey->fly(); }
};

int main(void) {
  MallarDuck *duck = new MallarDuck();
  WildTurkey *turkey = new WildTurkey();
  Duck *turkeyAdapter = new TurkeyAdapter(turkey);
  cout << "The Turkey says..." << endl;
  turkey->gobble();
  turkey->fly();
  cout << endl;
  cout << "The Duck says..." << endl;
  duck->quack();
  duck->fly();
  cout << endl;
  cout << "The TurkeyAdapter says..." << endl;
  turkeyAdapter->quack();
  turkeyAdapter->fly();
  cout << endl;
  return 0;
}
