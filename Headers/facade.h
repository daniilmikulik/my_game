#ifndef FACADE_H
#define FACADE_H

#include "Headers/command.h"
#include "Headers/leftcommand.h"
#include "Headers/rightcommand.h"
#include "Headers/upcommand.h"
#include "Headers/downcommand.h"
#include "Headers/fileexception.h"

class Facade;

class Condition{
protected:
    Facade* facade;
public:
    void setFacade(Facade* item){
        facade = item;
    }
    virtual void Handle() = 0;
    virtual ~Condition(){}
};

class Facade{
private:
    QGraphicsScene *scene;

    Board::MapIterator* mapTraverse = nullptr;
    Strategy::PlayerMoveObserver* playerMoveObserver;
    Strategy::Abstraction* abstraction;
    Strategy::Command* command;
    std::vector<Hero::Enemy<State, Fight>*> enemies;
    Condition* condition = nullptr;
    int mapTemplate;
public:
    Board::Map* main_map;
    Facade(QGraphicsScene *scene, int val);
    void StartGame();
    void SetCommand(Strategy::Command* command);
    void SpawnEnemies();
    bool IteratorConsists();
    bool IsGameEnded();
    bool IsPlayerKilled();
    void Clashed();
    void SetPlayerPosition();
    void ChangeCondition(Condition* cond);
    void Request();
    void SetEnemyStrategies();
    void Repaint(int val);

    QString Execute();
    QString Info();
    ~Facade();

    class FacadeMemento : public Memento{
    private:
        std::fstream fs;
        QGraphicsScene *scene;
        int mapTemplate;
        int playerX;
        int playerY;

        int defense;
        int bonusDefense;
        int attack;
        int bonusAttack;
        int coins;
        int health;

        std::vector<int> enemyX;
        std::vector<int> enemyY;
        std::vector<int> healthEnemy;
        std::vector<Fight> attackState;
        std::vector<State> moveState;

        std::string date;
        void SaveToFile();
        void LoadFromFile();
    public:
        friend class Facade;
        friend class Hero::Player;
        friend class Hero::Enemy<State, Fight>;
        std::string Date() override;
        explicit FacadeMemento(Facade& facade);
        explicit FacadeMemento(std::string& filename);
        ~FacadeMemento();
    };
    FacadeMemento* Save();
    void Restore(FacadeMemento* mem);
};

class FacadeCaretaker : public Caretaker{
    std::vector<Facade::FacadeMemento*> mementos;
    Facade* facade;
public:
    FacadeCaretaker(Facade* facade);
    void BackUp() override;
    void Undo() override;
    Memento* GetMemento();
    void SetMemento(Facade::FacadeMemento* mem);
};

class PlayerMove : public Condition{
public:
    void Handle() override;
};

class EnemyMove : public Condition{
public:
    void Handle() override{
        cout << "Enemy move" << endl;
        facade->SetPlayerPosition();
        facade->SetEnemyStrategies();
        facade->Clashed();
        this->facade->ChangeCondition(new PlayerMove);
    }
};



#endif // FACADE_H
