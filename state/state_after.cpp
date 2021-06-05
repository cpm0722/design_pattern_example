#include <iostream>
#include <string>

using namespace std;

class Light;
class State;
class ON;
class OFF;

class Light {
  private:
    State *state;
  public:
    Light(State *state);
    void setState(State *state);
    void on_button_pushed(void);
    void off_button_pushed(void);
};

class State {
  public:
    virtual void on_button_pushed(Light *light) = 0;
    virtual void off_button_pushed(Light *light) = 0;
};

class ON : public State {
  private:
    static ON on;
  public:
    static ON *getInstance(void) { return &on; }
    void on_button_pushed(Light *light) override;
    void off_button_pushed(Light *light) override;
};

class OFF : public State {
  private:
    static OFF off;
  public:
    static OFF *getInstance(void) { return &off; }
    void on_button_pushed(Light *light) override;
    void off_button_pushed(Light *light) override;
};

ON ON::on = ON();
OFF OFF::off = OFF();

Light::Light(State *state) {
  this->state = state;
}
void Light::setState(State *state) {
  this->state = state;
}
void Light::on_button_pushed(void) {
  this->state->on_button_pushed(this);
}
void Light::off_button_pushed(void) {
  this->state->off_button_pushed(this);
}
void ON::on_button_pushed(Light *light) {
      cout << "반응 없음" << endl;
}
void ON::off_button_pushed(Light *light) {
      light->setState(OFF::getInstance());
      cout << "Light Off!" << endl;
}
void OFF::on_button_pushed(Light *light) {
  light->setState(ON::getInstance());
  cout << "Light On!" << endl;
}
void OFF::off_button_pushed(Light *light) {
  cout << "반응 없음" << endl;
}

int main(void) {
  Light light(OFF::getInstance());
  light.off_button_pushed();
  light.on_button_pushed();
  light.off_button_pushed();
  return 0;
}
