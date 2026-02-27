
#include <iostream>
#include <string>
using namespace std;

/// \brief Интерфейс для персонажей
class Character {
public:
    virtual string getType() = 0;
    virtual void attack() = 0;
};

/// \brief Класс с настройками для персонажа ВОИН
class Warrior : public Character {
public:
    /**
    * \brief Функция для получения типа персонажа
    * \return srting - строку, название персонажа
    * \remark Получаем только имя персонажа т.к. это учебный код
    */
    string getType() override { return "Воин"; }
    /**
    * \brief Функция для выполнения действий персонажем
    * \note Не влияет ни на что. Это учебный код
    * \todo Добавить возможность отбирать жизни у того, на кого нападаем
    */
    void attack() override { cout << "Воин атакует мечом!" << endl; }
};

/// \brief Класс с настройками для персонажа МАГ
class Mage : public Character {
public:
    /**
    * \brief Функция для получения типа персонажа
    * \return srting - строку, название персонажа
    * \remark Получаем только имя персонажа т.к. это учебный код
    */
    string getType() override { return "Маг"; }
    /**
    * \brief Функция для выполнения действий персонажем
    * \note Не влияет ни на что. Это учебный код
    * \todo Добавить возможность отбирать жизни у того, на кого нападаем
    */
    void attack() override { cout << "Маг кастует огненный шар!" << endl; }
};

/// \brief Класс с настройками для персонажа ЛУЧНИК
class Archer : public Character {
public:
    /**
    * \brief Функция для получения типа персонажа
    * \return srting - строку, название персонажа
    * \remark Получаем только имя персонажа т.к. это учебный код
    */
    string getType() override { return "Лучник"; }
    /**
    * \brief Функция для выполнения действий персонажем
    * \note Не влияет ни на что. Это учебный код
    * \todo Добавить возможность отбирать жизни у того, на кого нападаем
    */
    void attack() override { cout << "Лучник стреляет из лука!" << endl; }
};

/**
* \brief Абстрактная фабрика для генерации персонажей
* \note Используется для примера работы паттерна проектирования Creational
*/
class CharacterFactory {
public:
    virtual Character* createCharacter() = 0;
    /**
    * \brief Функция для создания персонажей и выполнения базовых его действий
    * \note После создания объекта, выполняет действие персонажа и уничтожает объект
    * \warning Нельзя будет использовать созданных персонажей в других частях кода
    */
    void spawnAndAttack() {
        Character* chara = createCharacter();
        cout << "Создан " << chara->getType() << ". ";
        chara->attack();
        delete chara;
    }
};

/// \brief Класс для создания Воина
class WarriorFactory : public CharacterFactory {
public:
    /**
    * \brief Функция для выделения памяти на класс персонажа
    * \return Возвращает указатель на созданного персонажа
    */
    Character* createCharacter() override { return new Warrior(); }
};
/// \brief Класс для создания Мага
class MageFactory : public CharacterFactory {
public:
    /**
    * \brief Функция для выделения памяти на класс персонажа
    * \return Возвращает указатель на созданного персонажа
    */
    Character* createCharacter() override { return new Mage(); }
};
/// \brief Класс для создания Лучника
class ArcherFactory : public CharacterFactory {
public:
    /**
    * \brief Функция для выделения памяти на класс персонажа
    * \return Возвращает указатель на созданного персонажа
    */
    Character* createCharacter() override { return new Archer(); }
};

/// \brief Функция для запуска конвеера с персонажами
/// \note Используется для учебного кода
int main()
{
    setlocale(0, "");
    // Симуляция игры: создаем разных персонажей через фабрики
    CharacterFactory* factory = new WarriorFactory();
    factory->spawnAndAttack();  // Вывод: Создан Воин. Воин атакует мечом!

    factory = new MageFactory();
    factory->spawnAndAttack();  // Вывод: Создан Маг. Маг кастует огненный шар!

    factory = new ArcherFactory();
    factory->spawnAndAttack();  // Вывод: Создан Лучник. Лучник стреляет из лука!

    delete factory;
}
