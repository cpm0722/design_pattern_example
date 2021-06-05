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
  private:
    static ElevatorScheduler *scheduler;
    ThroughputScheduler(void) { }
  public:
    static ElevatorScheduler *getInstance(void) {
      if (ThroughputScheduler::scheduler == NULL)
        ThroughputScheduler::scheduler = new ThroughputScheduler();
      return ThroughputScheduler::scheduler;
    }
    int selectElevator(ElevatorManager *manager, int destination, Direction direction) override {
      return 1;  // 임의 지정
    }
};

class ResponseTimeScheduler : public ElevatorScheduler {
  private:
    static ElevatorScheduler *scheduler;
    ResponseTimeScheduler(void) { }
  public:
    static ElevatorScheduler *getInstance(void) {
      if (ResponseTimeScheduler::scheduler == NULL)
        ResponseTimeScheduler::scheduler = new ResponseTimeScheduler();
      return ResponseTimeScheduler::scheduler;
    }
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
    void requestElevator(int destination, Direction direction) {
      ElevatorScheduler *scheduler = getScheduler();
      int selectedElevator = scheduler->selectElevator(this, destination, direction);
      this->controllers[selectedElevator]->goToFloor(destination);
    }
  protected:
    virtual ElevatorScheduler *getScheduler(void) = 0;
};

class ElevatorManagerWithThroughputScheduling : public ElevatorManager {
  public:
    ElevatorManagerWithThroughputScheduling(int controllerCount) : ElevatorManager(controllerCount) { }
  protected:
    ElevatorScheduler *getScheduler(void) override {
      return ThroughputScheduler::getInstance();
    }
};

class ElevatorManagerWithResponseTimeScheduling : public ElevatorManager {
  public:
    ElevatorManagerWithResponseTimeScheduling(int controllerCount) : ElevatorManager(controllerCount) { }
  protected:
    ElevatorScheduler *getScheduler(void) override {
      return ResponseTimeScheduler::getInstance();
    }
};

class ElevatorManagerWithDynamicScheduling : public ElevatorManager {
  public:
    ElevatorManagerWithDynamicScheduling(int controllerCount) : ElevatorManager(controllerCount) { }
  protected:
    ElevatorScheduler *getScheduler(void) override {
      int hour = 12; // 임의 지정
      if (hour < 12)
        return ResponseTimeScheduler::getInstance();
      else
        return ThroughputScheduler::getInstance();
    }
};

ElevatorScheduler *ThroughputScheduler::scheduler = NULL;
ElevatorScheduler *ResponseTimeScheduler::scheduler = NULL;

int main(void) {
  ElevatorManager *emWithResponseTimeScheduler = new ElevatorManagerWithResponseTimeScheduling(2);
  emWithResponseTimeScheduler->requestElevator(10, UP);

  ElevatorManager *emWithThroughputScheduler = new ElevatorManagerWithThroughputScheduling(2);
  emWithThroughputScheduler->requestElevator(10, UP);

  ElevatorManager *emWithDynamicScheduler = new ElevatorManagerWithDynamicScheduling(2);
  emWithDynamicScheduler->requestElevator(10, UP);
  return 0;
}
