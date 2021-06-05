#include <iostream>
#include <string>

using namespace std;

enum DoorStatus  { CLOSED, OPENED  };
enum MotorStatus { MOVING, STOPPED };
enum Direction   { UP,     DOWN    };

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
      this->doorStatus = CLOSED;
    }
    void open(void) {
      this->doorStatus = OPENED;
    }
};

class Motor {
  private:
    Door *door;
    MotorStatus motorStatus;
    void setMotorStatus(MotorStatus motorStatus) {
      this->motorStatus = motorStatus;
    }
  protected:
    virtual void moveMotor(Direction direction) = 0;
  public:
    Motor(Door *door) {
      this->door = door;
      motorStatus = STOPPED;
    }
    MotorStatus getMotorStatus(void) {
      return this->motorStatus;
    }
    void move(Direction direction) {
      if (this->motorStatus == MOVING)
        return;
      DoorStatus doorStatus = this->door->getDoorStatus();
      if (doorStatus == OPENED)
        door->close();
      moveMotor(direction);
      setMotorStatus(MOVING);
    }
};

class HyundaiMotor : public Motor {
  private:
  protected:
    void moveMotor(Direction direction) override {
      cout << "Hyundai Motor move to ";
      if (direction == UP)
        cout << "UP";
      else if (direction == DOWN)
        cout << "DOWN";
      cout << endl;
    }
  public:
    HyundaiMotor(Door *door) : Motor(door) {
    }
};

class LGMotor : public Motor {
  private:
  protected:
    void moveMotor(Direction direction) override {
      cout << "LG Motor move to ";
      if (direction == UP)
        cout << "UP";
      else if (direction == DOWN)
        cout << "DOWN";
      cout << endl;
    }
  public:
    LGMotor(Door *door) : Motor(door) {
    }
};

int main(void){
  Door *door = new Door();

  HyundaiMotor hyundaiMotor(door);
  hyundaiMotor.move(UP);

  LGMotor lgMotor(door);
  lgMotor.move(UP);
  return 0;
}
