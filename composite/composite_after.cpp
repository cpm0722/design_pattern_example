#include <iostream>
#include <string>
#include <vector>

using namespace std;

class ComputerDevice {
  protected:
    int price;
    int power;
  public:
    virtual int getPrice(void) = 0;
    virtual int getPower(void) = 0;
};

class Keyboard : public ComputerDevice {
  public:
    Keyboard(int price, int power) {
      this->power = power;
      this->price = price;
    }
    int getPrice(void) override { return this->price; }
    int getPower(void) override { return this->power; }
};

class Body : public ComputerDevice {
  public:
    Body(int price, int power) {
      this->power = power;
      this->price = price;
    }
    int getPrice(void) override { return this->price; }
    int getPower(void) override { return this->power; }
};

class Monitor : public ComputerDevice {
  public:
    Monitor(int price, int power) {
      this->power = power;
      this->price = price;
    }
    int getPrice(void) override { return this->price; }
    int getPower(void) override { return this->power; }
};

class Computer : public ComputerDevice {
  private:
    vector<ComputerDevice *> components;
  public:
    void addComponent(ComputerDevice *component) { this->components.push_back(component); }
    void removeCOmponent(ComputerDevice *component) {
      for (int i = 0; i < this->components.size(); i++)
        if (this->components[i] == component) {
          this->components.erase(this->components.begin() + i, this->components.begin() + i + 1);
          break;
      }
    }
    int getPrice(void) override {
      int price = 0;
      for (int i = 0; i < this->components.size(); i++)
        price += this->components[i]->getPrice();
      return price;
    }
    int getPower(void) override {
      int power = 0;
      for (int i = 0; i < this->components.size(); i++)
        power += this->components[i]->getPower();
      return power;
    }
};

int main(void)
{
  Body *body = new Body(100, 70);
  Keyboard *keyboard = new Keyboard(5, 2);
  Monitor *monitor = new Monitor(20, 30);

  Computer computer;
  computer.addComponent(body);
  computer.addComponent(keyboard);
  computer.addComponent(monitor);

  int computerPrice = computer.getPrice();
  int computerPower = computer.getPower();
  cout << "Computer Price: " << computerPrice << "만원" << endl;
  cout << "Computer Power: " << computerPower << "W" << endl;
  return 0;
}
