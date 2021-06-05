#include <iostream>
#include <string>

#define ON  0
#define OFF 1

using namespace std;

class Light {
  private:
    int state;
  public:
    Light(void) { this->state = OFF; }
    void on(void) {
      if (this->state == ON)
        cout << "반응 없음" << endl;
      else
      {
        cout << "Light On!" << endl;
        this->state = ON;
      }
    }
    void off(void) {
      if (this->state == OFF)
        cout << "반응 없음" << endl;
      else
      {
        cout << "Light OFF!" << endl;
        this->state = OFF;
      }
    }
};

int main(void) {
  Light light;
  light.off();
  light.on();
  light.off();
  return 0;
}
