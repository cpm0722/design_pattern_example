#include <iostream>
#include <string>
#include <vector>

using namespace std;

enum Direction { UP, DOWN };

enum SchedulingStrategy { RESPONSE_TIME, THROUGHPUT, DYNAMIC };

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

class SchedulerFactory {
  public:
    static ElevatorScheduler *getScheduler(SchedulingStrategy strategy) {
      ElevatorScheduler *scheduler = NULL;
        switch (strategy) {
          case RESPONSE_TIME:
            scheduler = new ResponseTimeScheduler();
            break;
          case THROUGHPUT:
            scheduler = new ThroughputScheduler();
            break;
          case DYNAMIC:
            int hour = 12;  // 임의 지정
            if (hour < 12)
              scheduler = new ResponseTimeScheduler();
            else
              scheduler = new ThroughputScheduler();
            break;
        }
      return scheduler;
    }
};

class ElevatorManager {
  private:
    vector<ElevatorController *>controllers;
    SchedulingStrategy strategy;
  public:
    ElevatorManager(int controllerCount, SchedulingStrategy strategy) {
      for (int i = 0; i < controllerCount; i++)
        this->controllers.push_back(new ElevatorController(i + 1));
      this->strategy = strategy;
    }
    void setStrategy(SchedulingStrategy strategy) { this->strategy = strategy; }
    void requestElevator(int destination, Direction direction) {
      ElevatorScheduler *scheduler = SchedulerFactory::getScheduler(this->strategy);
      int selectedElevator = scheduler->selectElevator(this, destination, direction);
      this->controllers[selectedElevator]->goToFloor(destination);
    }
};

int main(void) {
  ElevatorManager *emWithResponseTimeScheduler = new ElevatorManager(2, RESPONSE_TIME);
  emWithResponseTimeScheduler->requestElevator(10, UP);

  ElevatorManager *emWithThroughputScheduler = new ElevatorManager(2, THROUGHPUT);
  emWithThroughputScheduler->requestElevator(10, UP);

  ElevatorManager *emWithDynamicScheduler = new ElevatorManager(2, DYNAMIC);
  emWithDynamicScheduler->requestElevator(10, UP);
  return 0;
}
