#include <iostream>
#include <string>

using namespace std;

class Lamp {
  public:
    void turnOn(void) {
      cout << "Lamp On" << endl;
    }
};

class Button {
  private:
    Lamp lamp;
  public:
    Button(Lamp lamp) {
      this->lamp = lamp;
    }
    void pressed(void) {
      lamp.turnOn();
    }
};

int main(void) {
  Lamp lamp;
  Button button(lamp);
  button.pressed();
  return 0;
}
