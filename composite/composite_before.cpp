#include <iostream>
#include <string>

using namespace std;

class Keyboard {
  private:
    int price;
    int power;
  public:
    Keyboard(int price, int power) {
      this->power = power;
      this->price = price;
    }
    int getPrice(void) { return this->price; }
    int getPower(void) { return this->power; }
};

class Body {
  private:
    int price;
    int power;
  public:
    Body(int price, int power) {
      this->power = power;
      this->price = price;
    }
    int getPrice(void) { return this->price; }
    int getPower(void) { return this->power; }
};

class Monitor {
  private:
    int price;
    int power;
  public:
    Monitor(int price, int power) {
      this->power = power;
      this->price = price;
    }
    int getPrice(void) { return this->price; }
    int getPower(void) { return this->power; }
};

class Computer {
  private:
    Body *body;
    Keyboard *keyboard;
    Monitor *monitor;
  public:
    void addBody(Body *body) { this->body = body; }
    void addKeyboard(Keyboard *keyboard) { this->keyboard = keyboard; }
    void addMonitor(Monitor *monitor) { this->monitor = monitor; }
    int getPrice(void) {
      int bodyPrice = this->body->getPrice();
      int keyboardPrice = this->keyboard->getPrice();
      int monitorPrice = this->monitor->getPrice();
      return bodyPrice + keyboardPrice + monitorPrice;
    }
    int getPower(void) {
      int bodyPower = this->body->getPower();
      int keyboardPower = this->keyboard->getPower();
      int monitorPower = this->monitor->getPower();
      return bodyPower + keyboardPower + monitorPower;
    }
};

int main(void)
{
  Body *body = new Body(100, 70);
  Keyboard *keyboard = new Keyboard(5, 2);
  Monitor *monitor = new Monitor(20, 30);

  Computer computer;
  computer.addBody(body);
  computer.addKeyboard(keyboard);
  computer.addMonitor(monitor);

  int computerPrice = computer.getPrice();
  int computerPower = computer.getPower();
  cout << "Computer Price: " << computerPrice << "만원" << endl;
  cout << "Computer Power: " << computerPower << "W" << endl;
  return 0;
}
