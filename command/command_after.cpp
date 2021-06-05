#include <iostream>
#include <string>

using namespace std;

class Command {
  public:
    virtual void execute(void) = 0;
};

class Button {
  private:
    Command *command;
  public:
    Button(Command *command) {
      setCommand(command);
    }
    void setCommand(Command *command) {
      this->command = command;
    }
    void pressed(void) {
      this->command->execute();
    }
};

class Lamp {
  public:
    void turnOn(void) {
      cout << "Lamp On" << endl;
    }
};

class Alarm {
  public:
    void start(void) {
      cout << "Alarming..." << endl;
    }
};

class LampOnCommand : public Command {
  private:
    Lamp lamp;
  public:
    LampOnCommand(Lamp lamp) {
      this->lamp = lamp;
    }
    void execute(void) override {
      this->lamp.turnOn();
    }
};

class AlarmOnCommand : public Command {
  private:
    Alarm alarm;
  public:
    AlarmOnCommand(Alarm alarm) {
      this->alarm = alarm;
    }
    void execute(void) override {
      this->alarm.start();
    }
};

int main(void) {
  Lamp lamp;
  Command *lampOnCommand = new LampOnCommand(lamp);
  Button button1(lampOnCommand);
  button1.pressed();

  Alarm alarm;
  Command *alarmOnCommand = new AlarmOnCommand(alarm);
  Button button2(alarmOnCommand);
  button2.pressed();

  button2.setCommand(lampOnCommand);
  button2.pressed();
  return 0;
}
