
#include <iostream>
#include <string>
using namespace std;
class Beverage {
public:
    virtual string getDescription() = 0;
    virtual double cost() = 0;
};

class Espresso : public Beverage { // Базовые кофе
public:
    string getDescription() override { return "Экспрессо"; }
    double cost() override { return 1.99; }
};
class CondimentDecorator : public Beverage {
protected:
    Beverage* beverage;
public:
    CondimentDecorator(Beverage* b) : beverage(b) {}
    string getDescription() override { return beverage->getDescription(); }
    double cost() override { return beverage->cost(); }
};
class Milk : public CondimentDecorator {
public:
    Milk(Beverage* b) : CondimentDecorator(b) {}
    std::string getDescription() override { return beverage->getDescription() + ", Молоко"; }
    double cost() override { return beverage->cost() + 0.10; }
};
class Sugar : public CondimentDecorator {
public:
    Sugar(Beverage* b) : CondimentDecorator(b) {}
    std::string getDescription() override { return beverage->getDescription() + ", Сахар"; }
    double cost() override { return beverage->cost() + 0.05; }
};
class Syrup : public CondimentDecorator {
public:
    Syrup(Beverage* b) : CondimentDecorator(b) {}
    std::string getDescription() override { return beverage->getDescription() + ",Сироп "; }
    double cost() override { return beverage->cost() + 0.05; }
};

int main()
{
    setlocale(LC_ALL, "RU");
    Beverage* drink = new Espresso();
    drink = new Milk(drink);
    drink = new Sugar(drink);
    drink = new Syrup(drink);

    cout << drink->getDescription() << " стоит $" << drink->cost() << endl;
    Beverage* simpleDrink = new Espresso();
    cout << simpleDrink->getDescription() << "стоит $" << simpleDrink->cost() << endl;
    delete drink;
    delete simpleDrink;
}
