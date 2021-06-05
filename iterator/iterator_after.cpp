#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Iterator {
  public:
    virtual bool hasNext(void) = 0;
    virtual void *next(void) = 0;
};

class MenuItem {
  private:
    string name;
    string description;
    bool vegetarian;
    double price;
  public:
    MenuItem(string name, string description, bool vegetarian, double price) {
      this->name = name;
      this->description = description;
      this->vegetarian = vegetarian;
      this->price = price;
    }
    string getName(void) { return this->name; }
    string getDescription(void) { return this->description; }
    double getPrice(void) { return this->price; }
    bool isVegetarian(void) { return vegetarian; }
};

class PancakeHouseMenuIterator : public Iterator {
  private:
    vector<MenuItem *> items;
    int position;
  public:
    PancakeHouseMenuIterator(vector<MenuItem *>items) {
      this->items = items;
      this->position = 0;
    }
    bool hasNext(void) override {
      if (this->position >= this->items.size() || this->items[this->position] == NULL)
        return false;
      return true;
    }
    void *next(void) override {
      return (void *)(this->items[this->position++]);
    }
};

class DinerMenuIterator : public Iterator {
  private:
    vector<MenuItem *> items;
    int position;
  public:
    DinerMenuIterator(vector<MenuItem *>items) {
      this->items = items;
      this->position = 0;
    }
    bool hasNext(void) override {
      if (this->position >= this->items.size() || this->items[this->position] == NULL)
        return false;
      return true;
    }
    void *next(void) override {
      return (void *)(this->items[this->position++]);
    }
};

class PancakeHouseMenu {
  private:
    vector<MenuItem *> menuItems;
  public:
    PancakeHouseMenu(void) {
      addItem("K&B's Pancake Breakfast",
              "Pancakes with scrambled eggs, and toast",
              true,
              2.99);
      addItem("Regular Pancake Breakfast",
              "Pancakes with fried eggs, sausage",
              false,
              2.99);
      addItem("Blueberry Pancakes",
              "Pancakes made with fresh blueberries",
              true,
              3.49);
      addItem("Waffles",
              "Waffles, with your choice of blueberries or strawberries",
              true,
              3.59);
    }
    void addItem(string name, string description, bool vegetarian, double price) {
      this->menuItems.push_back(new MenuItem(name, description, vegetarian, price));
    }
    Iterator *createIterator(void) {
      return new DinerMenuIterator(this->menuItems);
    }
};

class DinerMenu {
  private:
    static const int MAX_ITEMS = 6;
    int numberOfItems;
    vector<MenuItem *> menuItems;
  public:
    DinerMenu(void) {
      this->numberOfItems = 0;
      addItem("Vegetarian BLT",
              "(Fakin') Bacon with lettuce & tomato on whole wheat",
              true,
              2.99);
      addItem("BLT",
              "Bacon with lettuce & tomato on whole wheat",
              false,
              2.99);
      addItem("Soup of the day",
              "Soup of the day, with a side of potato salad",
              true,
              3.29);
      addItem("Hotdog",
              "A hot dog, with saurkraut, relish, onions, topped with cheese",
              true,
              3.05);
    }
    void addItem(string name, string description, bool vegetarian, double price) {
      if (this->numberOfItems >= DinerMenu::MAX_ITEMS)
        cout << "Sorry, menu is full! Can't add item to menu";
      else {
        this->menuItems.push_back(new MenuItem(name, description, vegetarian, price));
        this->numberOfItems++;
      }
    }
    Iterator *createIterator(void) {
      return new DinerMenuIterator(this->menuItems);
    }
};

class Waitress {
  private:
    PancakeHouseMenu *pancakeHouseMenu;
    DinerMenu *dinerMenu;
    void printMenu(Iterator *iterator) {
      while (iterator->hasNext()) {
        MenuItem *menuItem = (MenuItem *)iterator->next();
        cout << menuItem->getName() << ", ";
        cout << menuItem->getPrice() << "-- ";
        cout << menuItem->getDescription() << endl;
      }
    }
  public:
    Waitress(PancakeHouseMenu *pancakeHouseMenu, DinerMenu *dinerMenu) {
      this->pancakeHouseMenu = pancakeHouseMenu;
      this->dinerMenu = dinerMenu;
    }
    void printMenu(void) {
      Iterator *pancakeIterator = pancakeHouseMenu->createIterator();
      Iterator *dinerIterator = dinerMenu->createIterator();
      cout << "MENU" << endl << "----" << endl << "BREAKFAST" << endl;
      printMenu(pancakeIterator);
      cout << endl << "LUNCH" << endl;
      printMenu(dinerIterator);
      cout << endl;
    }
};

int main(void) {
  PancakeHouseMenu *pancakeHouseMenu = new PancakeHouseMenu();
  DinerMenu *dinerMenu = new DinerMenu();
  Waitress *waitress = new Waitress(pancakeHouseMenu, dinerMenu);
  waitress->printMenu();
  return 0;
}
