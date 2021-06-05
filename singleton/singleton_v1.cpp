#include <iostream>
#include <string>

#define USER_NUM 5

using namespace std;

class Printer {
  private:
    static Printer *printer;
    Printer(void) { }
  public:
    static Printer *getPrinter(void) {
      if (printer == NULL)
        printer = new Printer();
      return printer;
    }
    void print(string str) {
      cout << str << endl;
    }
};

Printer *Printer::printer = NULL;

class User {
  private:
    string name;
  public:
    User(string name) {
      this->name = name;
    }
    void print(void) {
      Printer *printer = Printer::getPrinter();
      cout << this->name <<  " using printer " << printer << endl;
    }
};

int main(void) {
  User users[USER_NUM] = { User("User1"), User("User2"), User("User3"), User("User4"), User("User5") };
  for (int i = 0; i < USER_NUM; i++)
    users[i].print();
  return 0;
}
