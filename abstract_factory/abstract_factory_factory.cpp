#include <iostream>
#include <string>

using namespace std;

enum Vendor      { LG,     HYUNDAI };
enum DoorStatus  { CLOSED, OPENED  };
enum MotorStatus { MOVING, STOPPED };
enum Direction   { UP,     DOWN    };

class Door;

class Motor {
  private:
    MotorStatus motorStatus;
    void setMotorStatus(MotorStatus motorStatus) {
      this->motorStatus = motorStatus;
    }
  protected:
    Door *door;
    virtual void moveMotor(Direction direction) = 0;
  public:
    Motor(void) {
      motorStatus = STOPPED;
    }
    void setDoor(Door *door) {
      this->door = door;
    }
    MotorStatus getMotorStatus(void) {
      return this->motorStatus;
    }
    void move(Direction direction) {
      if (this->motorStatus == MOVING)
        return;
      moveMotor(direction);
      setMotorStatus(MOVING);
    }
};

class HyundaiMotor : public Motor {
  protected:
    void moveMotor(Direction direction) override {
      cout << "Hyundai Motor move to ";
      if (direction == UP)
        cout << "UP";
      else if (direction == DOWN)
        cout << "DOWN";
      cout << endl;
    }
};

class LGMotor : public Motor {
  protected:
    void moveMotor(Direction direction) override {
      cout << "LG Motor move to ";
      if (direction == UP)
        cout << "UP";
      else if (direction == DOWN)
        cout << "DOWN";
      cout << endl;
    }
};

class Door {
  private:
    DoorStatus doorStatus;
  public:
    Door(void) {
      this->doorStatus = CLOSED;
    }
    DoorStatus getDoorStatus(void) {
      return this->doorStatus;
    }
    void close(void) {
      if (this->doorStatus == CLOSED)
        return;
      doOpen();
      this->doorStatus = CLOSED;
    }
    void open(void) {
      if (this->doorStatus == OPENED)
        return;
      doClose();
      this->doorStatus = OPENED;
    }
  protected:
    virtual void doClose(void) = 0;
    virtual void doOpen(void) = 0;
};

class HyundaiDoor: public Door {
  protected:
    void doClose(void) override {
      cout << "close Hyundai Door" << endl;
    }
    void doOpen(void) override {
      cout << "open Hyundai Door" << endl;
    }
};

class LGDoor : public Door {
  protected:
    void doClose(void) override {
      cout << "close LG Door" << endl;
    }
    void doOpen(void) override {
      cout << "open LG Door" << endl;
    }
};

class ElevatorFactory {
  public:
    virtual Motor *createMotor(void) = 0;
    virtual Door *createDoor(void) = 0;
};

class HyundaiElevatorFactory : public ElevatorFactory {
  private:
    static ElevatorFactory *instance;
    HyundaiElevatorFactory(void) { }
  public:
    static ElevatorFactory *getInstance(void) {
      if (HyundaiElevatorFactory::instance == NULL) {
        HyundaiElevatorFactory::instance = new HyundaiElevatorFactory();
      }
      return HyundaiElevatorFactory::instance;
    }
    Motor *createMotor(void) override {
      return new HyundaiMotor();
    }
    Door *createDoor(void) override {
      return new HyundaiDoor();
    }
};

class LGElevatorFactory : public ElevatorFactory {
  private:
    static ElevatorFactory *instance;
    LGElevatorFactory(void) { }
  public:
    static ElevatorFactory *getInstance(void) {
      if (LGElevatorFactory::instance == NULL) {
        LGElevatorFactory::instance = new LGElevatorFactory();
      }
      return LGElevatorFactory::instance;
    }
    Motor *createMotor(void) override {
      return new LGMotor();
    }
    Door *createDoor(void) override {
      return new LGDoor();
    }
};

class ElevatorFactoryFactory {
  public:
    static ElevatorFactory *getFactory(Vendor vendor) {
      ElevatorFactory *factory = NULL;
      switch (vendor) {
        case HYUNDAI:
          factory = HyundaiElevatorFactory::getInstance();
          break;
        case LG:
          factory = LGElevatorFactory::getInstance();
          break;
      }
      return factory;
    }
};

ElevatorFactory *HyundaiElevatorFactory::instance = NULL;
ElevatorFactory *LGElevatorFactory::instance = NULL;

int main(void) {
  ElevatorFactory *factory = ElevatorFactoryFactory::getFactory(LG);
  Door *lgDoor = factory->createDoor();
  Motor *lgMotor = factory->createMotor();
  lgMotor->setDoor(lgDoor);
  lgDoor->open();
  lgMotor->move(UP);
  return 0;
}
