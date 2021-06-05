#include <iostream>
#include <string>

using namespace std;

class MovingStrategy {
  public:
    virtual void move(void) = 0;
};

class AttackStrategy {
  public:
    virtual void attack(void) = 0;
};

class Robot {
  private:
    string name;
    MovingStrategy *movingStrategy;
    AttackStrategy *attackStrategy;
  public:
    Robot(string name) { this->name = name; }
    string getName(void) { return this->name; }
    void attack(void) { this->attackStrategy->attack(); }
    void move(void) { this->movingStrategy->move(); }
    void setMovingStrategy(MovingStrategy *movingStrategy) { this->movingStrategy = movingStrategy; }
    void setAttackStrategy(AttackStrategy *attackStrategy) { this->attackStrategy = attackStrategy; }
};


class TaekwonV: public Robot {
  public:
    TaekwonV(string name) : Robot(name) { }
};

class Atom: public Robot {
  public:
    Atom(string name) : Robot(name) { }
};

class FlyingStrategy : public MovingStrategy {
  public:
    void move() override {
      cout << "I can fly." << endl;
    }
};

class WalkingStrategy : public MovingStrategy {
  public:
    void move() override {
      cout << "I can only walk." << endl;
    }
};

class MissileStrategy : public AttackStrategy {
  public:
    void attack() override {
      cout << "I have Missile and can attack with it." << endl;
    }
};

class PunchStrategy : public AttackStrategy {
  public:
    void attack() override {
      cout << "I have strong punch and can attack with it." << endl;
    }
};

int main(void) {
  Robot *taekwonV = new TaekwonV("TaekwonV");
  Robot *atom = new Atom("Atom");

  taekwonV->setMovingStrategy(new WalkingStrategy());
  taekwonV->setAttackStrategy(new MissileStrategy());
  atom->setMovingStrategy(new FlyingStrategy());
  atom->setAttackStrategy(new PunchStrategy());

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
