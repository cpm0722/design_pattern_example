#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Direction { UP, DOWN };

class ElevatorManager;

class ElevatorController {
  private:
    int id;
    int curFloor;
  public:
    ElevatorController(int id) {
      this->id = id;
      this->curFloor = 1;
    }
    void goToFloor(int destination) {
      cout << "Elevator [" << this->id << "] Floor: " << this->curFloor << endl;
      this->curFloor = destination;
      cout << " ==> " << this->curFloor << endl;
    }
};

class ElevatorScheduler {
  public:
    virtual int selectElevator(ElevatorManager *manager, int destination, Direction direction) = 0;
};

class ThroughputScheduler : public ElevatorScheduler {
  public:
    int selectElevator(ElevatorManager *manager, int destination, Direction direction) override {
      return 1;  // 임의 지정
    }
};

class ResponseTimeScheduler : public ElevatorScheduler {
  public:
    int selectElevator(ElevatorManager *manager, int destination, Direction direction) override {
      return 0;  // 임의 지정
    }
};

class ElevatorManager {
  private:
    vector<ElevatorController *>controllers;
  public:
    ElevatorManager(int controllerCount) {
      for (int i = 0; i < controllerCount; i++)
        this->controllers.push_back(new ElevatorController(i + 1));
    }
    void requestElevator(int destination, Direction direction, int hour) {
      ElevatorScheduler *scheduler;
      if (hour < 12)
        scheduler = new ResponseTimeScheduler();
      else
        scheduler = new ThroughputScheduler();
      int selectedElevator = scheduler->selectElevator(this, destination, direction);
      this->controllers[selectedElevator]->goToFloor(destination);
    }
};
