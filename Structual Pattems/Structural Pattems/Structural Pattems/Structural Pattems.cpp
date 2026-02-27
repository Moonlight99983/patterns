#include <iostream>
#include <string>
using namespace std;
/**
 * \brief Абстрактный базовый класс напитка (Component)
 * Определяет общий интерфейс для всех видов кофе и добавок.
 */
class Beverage {
public:
    /// \brief Получить описание напитка
    virtual string getDescription() = 0;

    /// \brief Получить стоимость напитка
    virtual double cost() = 0;

    virtual ~Beverage() {}
};

/**
 * \brief Конкретный компонент — базовый кофе Эспрессо
 */
class Espresso : public Beverage {
public:
    string getDescription() override { return "Экспрессо"; }
    double cost() override { return 1.99; }
};

/**
 * \brief Абстрактный декоратор (Decorator)
 * Хранит ссылку на объект напитка и расширяет его поведение.
 */
class CondimentDecorator : public Beverage {
protected:
    Beverage* beverage;

public:
    /// \param b Декорируемый напиток
    CondimentDecorator(Beverage* b) : beverage(b) {}

    /// \brief Делегирует получение описания базовому объекту
    string getDescription() override { return beverage->getDescription(); }

    /// \brief Делегирует вычисление стоимости базовому объекту
    double cost() override { return beverage->cost(); }

    virtual ~CondimentDecorator() { delete beverage; }
};

/**
 * \brief Конкретный декоратор — добавление молока
 */
class Milk : public CondimentDecorator {
public:
    Milk(Beverage* b) : CondimentDecorator(b) {}

    /// \brief Расширяет описание напитка
    string getDescription() override {
        return beverage->getDescription() + ", Молоко";
    }

    /// \brief Увеличивает стоимость напитка
    double cost() override {
        return beverage->cost() + 0.10;
    }
};

/**
 * \brief Конкретный декоратор — добавление сахара
 */
class Sugar : public CondimentDecorator {
public:
    Sugar(Beverage* b) : CondimentDecorator(b) {}

    string getDescription() override {
        return beverage->getDescription() + ", Сахар";
    }

    double cost() override {
        return beverage->cost() + 0.05;
    }
};

/**
 * \brief Конкретный декоратор — добавление сиропа
 */
class Syrup : public CondimentDecorator {
public:
    Syrup(Beverage* b) : CondimentDecorator(b) {}

    string getDescription() override {
        return beverage->getDescription() + ", Сироп";
    }

    double cost() override {
        return beverage->cost() + 0.05;
    }
};
/**
 * \brief Демонстрация работы паттерна Декоратор
 * Позволяет динамически добавлять ингредиенты к напитку.
 */
int main()
{
    setlocale(LC_ALL, "RU");

    /// Создаём базовый напиток
    Beverage* drink = new Espresso();

    /// Последовательно оборачиваем его добавками
    drink = new Milk(drink);
    drink = new Sugar(drink);
    drink = new Syrup(drink);

    /// Вывод итогового напитка
    cout << drink->getDescription()
        << " стоит $" << drink->cost() << endl;

    /// Пример простого напитка без добавок
    Beverage* simpleDrink = new Espresso();
    cout << simpleDrink->getDescription()
        << " стоит $" << simpleDrink->cost() << endl;

    delete drink;
    delete simpleDrink;

    return 0;
}