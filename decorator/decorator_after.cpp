#include <iostream>
#include <string>

using namespace std;

class Display {
  public:
    virtual void draw(void) = 0;
};

class DisplayDecorator : public Display {
  private:
    Display *decoratedDisplay;
  public:
    DisplayDecorator(Display *decoratedDisplay) {
      this->decoratedDisplay = decoratedDisplay;
    }
    virtual void draw(void) {
      this->decoratedDisplay->draw();
    }
};

class RoadDisplay : public Display {
  public:
    void draw(void) {
      cout << "기본 도로 표시" << endl;
    }
};

class LaneDecorator : public DisplayDecorator {
  private:
    void drawLane(void) {
      cout << "차선 표시" << endl;
    }
  public:
    LaneDecorator(Display *decoratedDisplay) : DisplayDecorator(decoratedDisplay) {
    }
    void draw(void) override {
      DisplayDecorator::draw();
      drawLane();
    }
};

class TrafficDecorator : public DisplayDecorator {
  private:
    void drawTraffic(void) {
      cout << "교통량 표시" << endl;
    }
  public:
    TrafficDecorator(Display *decoratedDisplay) : DisplayDecorator(decoratedDisplay) {
    }
    void draw(void) override {
      DisplayDecorator::draw();
      drawTraffic();
    }
};

int main(void) {
  Display *road = new RoadDisplay();
  road->draw();
  cout << endl;

  Display *roadWithLane = new LaneDecorator(new RoadDisplay());
  roadWithLane->draw();
  cout << endl;

  Display *roadWithTraffic = new TrafficDecorator(new RoadDisplay());
  roadWithTraffic->draw();
  cout << endl;

  Display *roadWithLandAndTraffic = new TrafficDecorator(new LaneDecorator(new RoadDisplay()));
  roadWithLandAndTraffic->draw();
  cout << endl;

  return 0;
}
