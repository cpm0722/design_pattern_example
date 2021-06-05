#include <iostream>
#include <string>
#include <vector>

using namespace std;

class DataSheetView;
class ScoreRecord;

class ScoreRecord {
  private:
    vector<int> scores;
    DataSheetView *dataSheetView;
  public:
    void setDataSheetView(DataSheetView *dataSheetView);
    void addScore(int score);
    vector<int> &getScores(void);
};

class DataSheetView {
  private:
    ScoreRecord *scoreRecord;
    int viewCount;
    void displayScores(vector<int> &record, int viewCount);
  public:
    DataSheetView(ScoreRecord *scoreRecord, int viewCount);
    void update(void);
};

void ScoreRecord::setDataSheetView(DataSheetView *dataSheetView) {
  this->dataSheetView = dataSheetView;
}
void ScoreRecord::addScore(int score) {
  this->scores.push_back(score);
  this->dataSheetView->update();
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
  DataSheetView *dataSheetView = new DataSheetView(scoreRecord, 3);
  scoreRecord->setDataSheetView(dataSheetView);

  for (int i = 1; i <= 5; i++) {
    int score = i * 10;
    cout << "Adding " << score << endl;
    scoreRecord->addScore(score);
  }

  return 0;
}
