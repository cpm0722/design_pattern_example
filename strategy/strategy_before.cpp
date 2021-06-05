#include <iostream>
#include <string>

using namespace std;

class Robot {
  private:
    string name;
  public:
    Robot(string name) { this->name = name; }
    string getName() { return this->name; }
    virtual void attack() = 0;
    virtual void move() = 0;
};

class TaekwonV: public Robot {
  public:
    TaekwonV(string name) : Robot(name) { }
    void attack(void) override {
       cout << "I have Missile and can attack with it." << endl;
    }
    void move(void) override {
      return;
    }
};

class Atom: public Robot {
  public:
    Atom(string name) : Robot(name) { }
    void attack(void) override {
       cout << "I have strong punch and can attack with it." << endl;
    }
    void move(void) override {
       cout << "I can fly." << endl;
    }
};

int main(void) {
  Robot *taekwonV = new TaekwonV("TaekwonV");
  Robot *atom = new Atom("Atom");

  cout << "My name is" << taekwonV->getName() << endl;
  taekwonV->move();
  taekwonV->attack();

  cout << endl;

  cout << "My name is" << atom->getName() << endl;
  atom->move();
  atom->attack();
  cout << endl;
  return 0;
}
