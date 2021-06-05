#include <iostream>
#include <string>
#include <vector>

using namespace std;

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
    vector<MenuItem *> getMenuItems(void) { return this->menuItems; }
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
    vector<MenuItem *> getMenuItems(void) { return this->menuItems; }
};

int main(void) {
  PancakeHouseMenu pancakeHouseMenu;
  DinerMenu dinerMenu;
  vector<MenuItem *> pancakeHouseMenuItems = pancakeHouseMenu.getMenuItems();
  vector<MenuItem *> dinerMenuItems = dinerMenu.getMenuItems();
  for (int i = 0; i < pancakeHouseMenuItems.size(); i++) {
    MenuItem *item = pancakeHouseMenuItems[i];
    cout << item->getName() << ", " << item->getPrice() << "-- " << item->getDescription() << endl;
  }
  cout << endl;
  for (int i = 0; i < dinerMenuItems.size(); i++) {
    MenuItem *item = dinerMenuItems[i];
    cout << item->getName() << ", " << item->getPrice() << "-- " << item->getDescription() << endl;
  }
  return 0;
}
