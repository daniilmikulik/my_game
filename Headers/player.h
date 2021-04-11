#ifndef PLAYER_H
#define PLAYER_H

#include "libs.h"
#include "Headers/tile.h"
#include "Headers/abstractstrategy.h"
#include "Headers/publisher.h"
#include "Headers/observer.h"
#include "Headers/memento.h"
#include <string>

using namespace std;

#define FILE_NAME_2 "log.txt"

enum State{STAY, GO};
enum Fight{FIRE, MELEE};

namespace Strategy {
    class AbstractStrategy;
    class BinTree;
}

class AbstractEnemyStrategy;
class FortressEnemyStrategy;
class TowerEnemyStrategy;
class DefaultEnemyStrategy;
class Player;


namespace Hero{

    template<typename T, typename U>
    class Enemy;

    class Player : public Publisher{
    private:
        int curX;
        int curY;

        Strategy::AbstractStrategy* abstractStrategy;
        QGraphicsScene* playerScene;
        QGraphicsPixmapItem* playerUnit;

        int defense;
        int bonusDefense;
        int attack;
        int bonusAttack;
        int coins;
        int health;
        Board::Tile* curTile;
        std::list<Strategy::Abstraction*> observerList;

    public:

        Player(int x, int y, QGraphicsScene* scene, Board::Tile& tileObject);
        void Move();
        void SetCurTile(Board::Tile& tileObject);
        void SetCurX(int x);
        void SetCurY(int y);
        int GetCurX();
        int GetCurY();

        void SetDefenseBonus(int val);
        void SetAttackBonus(int val);
        void AddCoins(int val);
        int GetDefenseBonus();
        int GetAttackBonus();
        int GetCoins();
        int GetHealth();
        void SetHealth(int val);
        void SetStrategy(Strategy::AbstractStrategy* strategy);
        void Subscribe(Strategy::Abstraction* abstraction) override;
        void Unsubscribe(Strategy::Abstraction* abstraction) override;
        void Notify() override;
        void Hit(int val);
        QString GetInfo();
        virtual ~Player();
        void operator-=(Hero::Enemy<State, Fight>* const& enemy);
        void operator+=(Board::AbstractTile* const& tile);
        bool IsKilled();
        friend std::ostream& operator<<(std::ostream &out, Player* unit){
            out << "PLAYER: changed coordinates x = " << unit->GetCurX() << " y = " << unit->GetCurY() << "\n";
            out << "PLAYER: changed bonuses Defense = " << unit->GetDefenseBonus() << " Attack = " << unit->GetAttackBonus() << " Coins = " << unit->GetCoins() <<"\n";
            return out;
        }
    };



    template<typename T, typename U>
    class Enemy{
    private:
        int curX;
        int curY;

        int playerX;
        int playerY;


        QGraphicsScene* enemyScene;


        int defense;
        int bonusDefense;
        int meleeAttack;
        int fireAttack;
        int bonusAttack;
        int health;
        Board::Tile* curTile;


        bool isDead = false;
    public:
        U attackState;
        T moveState;
        QGraphicsPixmapItem* enemyUnit;

        Enemy(int x, int y, QGraphicsScene* scene, Board::Tile& tileObject){
            SetCurTile(tileObject);
            curX = x;
            curY = y;
            enemyScene = scene;
            enemyUnit = scene -> addPixmap(QPixmap(":/Resource/Images/enemy.png"));

            defense = 2;
            bonusDefense = 0;
            meleeAttack = 2;
            fireAttack = 1;
            bonusAttack = 0;
            health = 6;
            Move();
        }
        static Enemy* GetInstance(int x, int y, QGraphicsScene* scene, Board::Tile& tileObject){
               return new Enemy<T, U>(x, y, scene, tileObject);
        }
        void Move(){
            enemyUnit -> setOffset(curX*110, curY*110);
        }
        void SetCurTile(Board::Tile& tileObject){
            curTile = &tileObject;
        }
        void SetCurX(int x){
            curX = x;
        }
        void SetCurY(int y){
            curY = y;
        }
        int GetCurX(){
            return curX;
        }
        int GetCurY(){
            return curY;
        }

        void SetPlayerCoord(int x, int y){
            playerX = x;
            playerY = y;
        }
        int GetPlayerX(){
            return playerX;
        }
        int GetPlayerY(){
            return playerY;
        }
        void SetDefenseBonus(int val){
            bonusAttack = val;
        }
        void SetAttackBonus(int val){
            bonusDefense = val;
        }

        int GetDefenseBonus(){
            return bonusDefense;
        }
        int GetAttackBonus(){
            return bonusAttack;
        }
        int GetHealth(){
            return health;
        }
        void SetHealth(int val){
            health = val;
        }
        bool IsDead(){
            return (isDead == true);
        }

        Strategy::BinTree* CreateDecisionTree();
        void DefineBehaviour();


        void operator-=(Hero::Player* const& player){
            if((curX == playerX) && (curY == playerY)){
                player->Hit(meleeAttack);
            } else {
                player->Hit(fireAttack);
            }
        }

        void Hit(int val){
            if(health > 0){
                health -= val;
            }
            if(health < 0){
                enemyScene->removeItem(enemyUnit);
                enemyUnit = enemyScene -> addPixmap(QPixmap(":/Resource/Images/grave.png"));
                Move();
                health = 0;
            }
        }
        bool Fire(){
            return (attackState == FIRE);
        }

        std::pair<int,int> MoveAI(){
            int dX = (this->GetPlayerX())-(this->GetCurX());
            int dY = (this->GetPlayerY()) - (this->GetCurY());
            int tmpX = curX;
            int tmpY = curY;
            if (dX > 0 && dY > 0){
                tmpX = curX + 1;
            } else if(dX > 0 && dY < 0){
                tmpX = curX - 1;
            } else if(dX < 0 && dY > 0){
                tmpY = curY - 1;
            } else if(dX < 0 && dY < 0){
                tmpY = curY + 1;
            }
            std::pair<int, int> pair = {tmpX, tmpY};
            return pair;
            //Move();
        }

        bool MoveCond(){
            return ((attackState == MELEE) || moveState == GO);
        }

        bool IsKilled(){
            return (health == 0);
        }
        ~Enemy(){}
    };

}

namespace Strategy{

    class FortressStrategy : public AbstractStrategy {
        int val;
    public:
        FortressStrategy(int val) {
            this->val = val;
        };
        void Interact(Hero::Player* unit) override {
            unit->SetAttackBonus(val);
            unit->SetDefenseBonus(val);
        }
    };

    class TowerStrategy : public AbstractStrategy {
    int val;
    public:
        TowerStrategy(int val){
            this->val = val;
        }
        void Interact(Hero::Player* unit) override {
            unit->SetAttackBonus(val);
            unit->SetDefenseBonus(val);
        }
    };

    class VillageStrategy : public AbstractStrategy {
    int val;
    int numCoins;
    public:
        VillageStrategy(int val, int num_coins){
            this->val = val;
            this->numCoins = num_coins;
        }
        void Interact(Hero::Player* unit) override {
            unit->AddCoins(numCoins);
            unit->SetDefenseBonus(val);
        }
    };

    class MillStrategy : public AbstractStrategy {
        int numCoins;
    public:
        MillStrategy(int num_coins) {
            this->numCoins = num_coins;
        }
        void Interact(Hero::Player* unit) override {
            unit->AddCoins(numCoins);
        }
    };


    class DefaultStrategy : public AbstractStrategy {
    public:
        void Interact(Hero::Player* unit) override {
            unit->SetAttackBonus(0);
            unit->SetDefenseBonus(0);
        }
    };


    class PlayerMoveObserver : public AbstractObserver{
        std::fstream file;
    public:
        PlayerMoveObserver(){
            file.open(FILE_NAME_2, std::fstream::in | std::fstream::out | std::fstream::app );
        }
        void Update(Publisher* unit) override{
            std::cout << dynamic_cast<Hero::Player*>(unit);
            file << dynamic_cast<Hero::Player*>(unit);
        }
        virtual ~PlayerMoveObserver(){
            file.close();
        }
    };





    class AbstractEnemyStrategy{
    public:

        virtual void Interact(Hero::Enemy<State, Fight>* unit) = 0;
    };

    class FortressEnemyStrategy : public AbstractEnemyStrategy {
        int val;
    public:
        FortressEnemyStrategy(int val) {
            this->val = val;
        };
        void Interact(Hero::Enemy<State, Fight>* unit) override {
            unit->SetAttackBonus(val);
            unit->SetDefenseBonus(val);
        }
    };

    class TowerEnemyStrategy : public AbstractEnemyStrategy {
    int val;
    public:
        TowerEnemyStrategy(int val){
            this->val = val;
        }
        void Interact(Hero::Enemy<State, Fight>* unit) override {
            unit->SetAttackBonus(val);
            unit->SetDefenseBonus(val);
        }
    };

    class DefaultEnemyStrategy : public AbstractEnemyStrategy {
    public:
        void Interact(Hero::Enemy<State,Fight>* unit) override {
            unit->SetAttackBonus(0);
            unit->SetDefenseBonus(0);
        }
    };

    class BinTree{
    public:

        class Node{
        public:
            int value;
            Node* left = nullptr;
            Node* right = nullptr;

            static void setVal(Node** node, int value){
                if(*node){
                    (*node)->value = value;
                }
                else {
                    *node = new Node;
                    (*node)->value = value;
                }
            }
        };
        Node* data = nullptr;

        void readTree(string& line, int& cur, int& len, Node** node){
                if(cur < len){
                    Node::setVal(node, 0);
                    if(isalnum(line[cur])){
                        Node::setVal(node, ((int)line[cur] - 48));
                        //cout << line[cur];
                        cur++;

                    } else if (line[cur] == '(') {
                        //cout << line[cur];
                        cur++;
                        readTree(line, cur, len, &((*node)->left));

                        //cout << line[cur];
                        Node::setVal(node, (int)line[cur] - 48);
                        cur++;
                        readTree(line, cur, len, &((*node)->right));

                        //cout <<line[cur];
                        cur++;
                    }

                } else {
                    return;
                }
            }

        void read(string& line, int& cur, int& len){
            readTree(line, cur, len, &data);
        }

        template<class T, class U>
        int makeDecision(Hero::Enemy<T,U>* enemy){
            Node* cur = this->data;
            while((cur->left) && (cur->right)){
                if (!(cur->value)){
                    if((enemy->GetAttackBonus() + enemy->GetDefenseBonus()) > (cur->value)){
                        cur = cur->right;
                    }
                    else{
                        cur = cur->left;
                    }
                } else{
                    if((abs((enemy->GetPlayerX())-(enemy->GetCurX())) + abs((enemy->GetPlayerY()) - (enemy->GetCurY()))) > (cur->value)){
                        cur = cur->right;
                    }
                    else{
                        cur = cur->left;
                    }
                }

            }
            return cur->value;
        }

        template<class T, class U>
        int decise(Hero::Enemy<T,U>* enemy){
            return makeDecision( enemy);
        }

        void PrintInOrderTraversal(Node* node, int k){
                if (node){

                    PrintInOrderTraversal(node->left, k+1);
                    for(int i = 0; i < k; i++){
                        cout << " " ;
                    }
                    cout << node->value ;
                    cout << endl;
                    PrintInOrderTraversal(node->right, k+1);

                }
                else{
                    return;
                }
            }

            void print(){
                PrintInOrderTraversal(this->data, 0);
                cout << "\n";
            }
    };
}


namespace Hero{
template<typename T,typename U>
void Enemy<T,U>::DefineBehaviour(){
    Strategy::BinTree* bt = CreateDecisionTree();

    int res = bt->decise(this);
    switch(res){
        case 1:
            this->attackState = FIRE;
            break;
        case 2:
            this->attackState = MELEE;
            break;
        case 3:
            this->moveState = STAY;
            break;
        case 4:
            this->moveState = GO;
            break;
    }
    delete bt;
}
template<typename T, typename U>
Strategy::BinTree* Enemy<T,U>::CreateDecisionTree(){
    string line = "((112)3(40(453)))";
    int len = line.length();
    int cur = 0;
    Strategy::BinTree* bt = new Strategy::BinTree;
    bt->read(line, cur, len);
    //bt->print();
    return bt;
}

}
#endif // PLAYER_H

