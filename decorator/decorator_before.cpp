#include <iostream>
#include <string>

using namespace std;

class RoadDisplay {
  public:
    void draw(void) {
      cout << "기본 도로 표시" << endl;
    }
};

class RoadDisplayWithLane : public RoadDisplay {
  private:
    void drawLane(void) {
      cout << "차선 표시" << endl;
    }
  public:
    void draw(void) {
      RoadDisplay::draw();
      drawLane();
    }
};

int main(void) {
  RoadDisplay *roadDisplay = new RoadDisplay();
  roadDisplay->draw();

  RoadDisplayWithLane *roadDisplayWithLane = new RoadDisplayWithLane();
  roadDisplayWithLane->draw();
  return 0;
}
