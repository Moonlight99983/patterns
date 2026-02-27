#include <iostream>
#include <string>
#include <vector>
using namespace std;

/**
 * \brief Класс, моделирующий компьютерную систему (Receiver)
 * Выполняет реальные действия, которые вызываются командами.
 */
class ComputerSystem
{
public:
    /// \brief Открытие файла
    void openFile(const string& file) { cout << "Открываем файл: " << file << endl; }

    /// \brief Выключение компьютера
    void shutdown() { cout << "Выключаем компьютер" << endl; }

    /// \brief Запуск браузера
    void launchBrowser() { cout << "Запускаем браузер" << endl; }
};

/**
 * \brief Абстрактный интерфейс команды
 */
class Command
{
public:
    virtual void execute() = 0; ///   \Выполнить действие
    virtual void undo() = 0;    /// \Отменить действие
    virtual ~Command() {}
};

/**
 * \brief Команда открытия файла
 */
class OpenFileCommand : public Command
{
private:
    ComputerSystem* system;
    string fileName;

public:
    OpenFileCommand(ComputerSystem* s, const string& fn)
        : system(s), fileName(fn) {
    }

    void execute() override { system->openFile(fileName); }

    void undo() override { cout << "Закрываем файл: " << fileName << endl; }
};

/**
 * \brief Команда выключения компьютера
 */
class ShutdownCommand : public Command
{
private:
    ComputerSystem* system;

public:
    ShutdownCommand(ComputerSystem* s) : system(s) {}

    void execute() override { system->shutdown(); }

    void undo() override { cout << "Отмена: включаем компьютер обратно" << endl; }
};

/**
 * \brief Команда запуска браузера
 */
class LaunchBrowserCommand : public Command
{
private:
    ComputerSystem* system;

public:
    LaunchBrowserCommand(ComputerSystem* s) : system(s) {}

    void execute() override { system->launchBrowser(); }

    void undo() override { cout << "Закрываем браузер" << endl; }
};

/**
 * \brief Класс-инициатор (Invoker)
 * Хранит команды и вызывает их выполнение.
 */
class RemoteControl
{
private:
    vector<Command*> commands;

public:
    /// \brief Добавление команды
    void addCommand(Command* cmd) { commands.push_back(cmd); }

    /// \brief Выполнение всех команд
    void pressButton()
    {
        for (auto cmd : commands)
            cmd->execute();
    }

    /// \brief Отмена последней команды
    void undoLast()
    {
        if (!commands.empty())
        {
            commands.back()->undo();
            commands.pop_back();
        }
    }
};

/**
 * \brief Абстрактный базовый класс персонажа
 */
class Character
{
public:
    virtual string getType() = 0; ///< Тип персонажа
    virtual void attak() = 0;     ///< Действие атаки
    virtual int getHealth() = 0;  ///< Количество здоровья
    virtual ~Character() {}
};

/**
 * \brief Класс Воина
 */
class Warrior : public Character
{
public:
    string getType() override { return "Воин"; }
    void attak() override { cout << "Воин атакует мечом!" << endl; }
    int getHealth() override { return 100; }
};

/**
 * \brief Класс Рыцаря
 */
class Knight : public Character
{
public:
    string getType() override { return "Рыцарь"; }
    void attak() override { cout << "Рыцарь атакует копьём!" << endl; }
    int getHealth() override { return 80; }
};

/**
 * \brief Класс Мага
 */
class Mage : public Character
{
public:
    string getType() override { return "Маг"; }
    void attak() override { cout << "Маг кастует заклинание!" << endl; }
    int getHealth() override { return 50; }
};

/**
 * \brief Класс Лучника
 */
class Archer : public Character
{
public:
    string getType() override { return "Лучник"; }
    void attak() override { cout << "Лучник стреляет из лука!" << endl; }
    int getHealth() override { return 70; }
};
/**
 * \brief Абстрактная фабрика персонажей
 */
class CharacterFactory
{
public:
    /// \brief Фабричный метод создания персонажа
    virtual Character* createHero() = 0;

    /**
     * \brief Создание персонажа и выполнение его действия
     * Используется для демонстрации работы фабрики.
     */
    void spawnAndAttak()
    {
        Character* charact = createHero();

        cout << "Создан " << charact->getType()
            << " со здоровьем " << charact->getHealth() << ". ";

        charact->attak();
        delete charact;
    }

    virtual ~CharacterFactory() {}
};
/**
 * \brief Конкретные фабрики персонажей
 */
class WarriorFactory : public CharacterFactory
{
public:
    Character* createHero() override { return new Warrior(); }
};

class KnightFactory : public CharacterFactory
{
public:
    Character* createHero() override { return new Knight(); }
};

class MageFactory : public CharacterFactory
{
public:
    Character* createHero() override { return new Mage(); }
};

class ArcherFactory : public CharacterFactory
{
public:
    Character* createHero() override { return new Archer(); }
};

/**
 * \brief Точка входа в программу
 * Демонстрирует работу двух паттернов проектирования.
 */
int main()
{
    setlocale(LC_ALL, "ru");

    cout << "Демонстрация Command" << endl;

    ComputerSystem system;

    Command* openCmd = new OpenFileCommand(&system, "document.txt");
    Command* browserCmd = new LaunchBrowserCommand(&system);
    Command* shutdownCmd = new ShutdownCommand(&system);

    RemoteControl remote;
    remote.addCommand(openCmd);
    remote.addCommand(browserCmd);
    remote.addCommand(shutdownCmd);

    remote.pressButton();
    remote.undoLast();

    delete openCmd;
    delete browserCmd;
    delete shutdownCmd;

    cout << "\n Демонстрация Factory Method" << endl;

    CharacterFactory* factory;

    factory = new WarriorFactory();
    factory->spawnAndAttak();
    delete factory;

    factory = new MageFactory();
    factory->spawnAndAttak();
    delete factory;

    factory = new ArcherFactory();
    factory->spawnAndAttak();
    delete factory;

    factory = new KnightFactory();
    factory->spawnAndAttak();
    delete factory;

    return 0;
}