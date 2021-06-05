#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Subject;
class Observer;
class DataSheetView;
class ScoreRecord;

class Subject {
  private:
    vector<Observer *>observers;
  public:
    void attach(Observer *observer);
    void detach(Observer *observer);
    void notifyObservers(void);
};

class Observer {
  public:
    virtual void update(void) = 0;
};

class ScoreRecord : public Subject{
  private:
    vector<int> scores;
  public:
    void addScore(int score);
    vector<int> &getScores(void);
};

class DataSheetView : public Observer {
  private:
    ScoreRecord *scoreRecord;
    int viewCount;
    void displayScores(vector<int> &record, int viewCount);
  public:
    DataSheetView(ScoreRecord *scoreRecord, int viewCount);
    void update(void) override;
};

void Subject::attach(Observer *observer) {
  this->observers.push_back(observer);
}
void Subject::detach(Observer *observer) {
  for (int i = 0; i < this->observers.size(); i++)
    if (this->observers[i] == observer) {
      this->observers.erase(this->observers.begin() + i, this->observers.begin() + i + 1);
      break;
    }
}
void Subject::notifyObservers(void) {
  for (int i = 0; i < this->observers.size(); i++)
    this->observers[i]->update();
}
void ScoreRecord::addScore(int score) {
  this->scores.push_back(score);
  this->notifyObservers();
}
vector<int> &ScoreRecord::getScores(void) {
  return this->scores;
}
DataSheetView::DataSheetView(ScoreRecord *scoreRecord, int viewCount) {
  this->scoreRecord = scoreRecord;
  this->viewCount = viewCount;
}
void DataSheetView::displayScores(vector<int> &record, int viewCount) {
  cout << "List of " << viewCount << " entries:";
  for (int i = 0; i < viewCount && i < record.size(); i++)
    cout << record[i] << " ";
  cout << endl;
}
void DataSheetView::update(void) {
  vector<int> &record  = this->scoreRecord->getScores();
  displayScores(record, viewCount);
}

int main(void) {
  ScoreRecord *scoreRecord = new ScoreRecord();
  DataSheetView *dataSheetView3 = new DataSheetView(scoreRecord, 3);
  DataSheetView *dataSheetView5 = new DataSheetView(scoreRecord, 5);

  scoreRecord->attach(dataSheetView3);
  scoreRecord->attach(dataSheetView5);

  for (int i = 1; i <= 5; i++) {
    int score = i * 10;
    cout << "Adding " << score << endl;
    scoreRecord->addScore(score);
  }

  return 0;
}
