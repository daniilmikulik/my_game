#include "Headers/player.h"

Hero::Player::Player(int x, int y, QGraphicsScene* scene, Board::Tile& tileObject){
    this -> SetCurTile(tileObject);
    curX = x;
    curY = y;
    playerScene = scene;
    playerUnit = scene -> addPixmap(QPixmap(":/Resource/Images/pikeman.png"));

    defense = 2;
    bonusDefense = 0;
    attack = 5;
    bonusAttack = 0;
    coins = 0;
    health = 15;
    this -> Move();
}

void Hero::Player::Move(){
    playerUnit -> setOffset(curX*110, curY*110);
    this->Notify();
}

void Hero::Player::SetCurTile(Board::Tile &tileObject){
    this -> curTile = &tileObject;
    *this += curTile -> object;
}

void Hero::Player::SetCurX(int x){
    curX = x;
}

void Hero::Player::SetCurY(int y){
    curY = y;
}

int Hero::Player::GetCurX(){
    return curX;
}

int Hero::Player::GetCurY(){
    return curY;
}

void Hero::Player::SetStrategy(Strategy::AbstractStrategy* strategy){
    abstractStrategy = strategy;
}

void Hero::Player::operator+=(Board::AbstractTile *const &tile){
    if (tile->GetTileId() == 5){
        Strategy::FortressStrategy* fortressStrategy = new Strategy::FortressStrategy(2);
        this->SetStrategy(fortressStrategy);
    }
    if (tile->GetTileId() == 6 && (!curTile->object->IsUsed())){
        Strategy::MillStrategy* millStrategy = new Strategy::MillStrategy(300);
        this->SetStrategy(millStrategy);
        curTile->object->SetUsed();
    }
    if (tile->GetTileId() == 7){
        Strategy::TowerStrategy* towerStrategy = new Strategy::TowerStrategy(1);
        this->SetStrategy(towerStrategy);
    }
    if (tile->GetTileId() == 8 && (!curTile->object->IsUsed())){
        Strategy::VillageStrategy* villageStrategy = new Strategy::VillageStrategy(1, 300);
        this->SetStrategy(villageStrategy);
        curTile->object->SetUsed();
    }
    if ((tile->GetTileId() < 5) || (tile->GetTileId() > 8)){
        Strategy::DefaultStrategy* defaultStrategy = new Strategy::DefaultStrategy();
        this->SetStrategy(defaultStrategy);
    }
    abstractStrategy->Interact(this);
}

void Hero::Player::SetDefenseBonus(int val){
    bonusDefense = val;
}
void Hero::Player::SetAttackBonus(int val){
    bonusAttack = val;
}

void Hero::Player::AddCoins(int val){
    coins += val;
}

int Hero::Player::GetDefenseBonus(){
    return bonusDefense;
}
int Hero::Player::GetAttackBonus(){
    return bonusAttack;
}
int Hero::Player::GetCoins(){
    return coins;
}
int Hero::Player::GetHealth(){
    return health;
}

void Hero::Player::SetHealth(int val){
    health = val;
}

QString Hero::Player::GetInfo(){
    QString def("Defense: ");
    QString bonusDef = QString::number(this->bonusDefense);
    QString att(" Attack: ");
    QString bonusAtt = QString::number(this->bonusAttack);
    QString coin(" Coins: ");
    QString coinStr = QString::number(this->coins);
    QString heal(" Health: ");
    QString healStr = QString::number(this->health);
    return QString(def + bonusDef + att + bonusAtt + coin + coinStr + heal + healStr);
}


void Hero::Player::Subscribe(Strategy::Abstraction* abstraction) {
    this->observerList.push_back(abstraction);
}

void Hero::Player::Unsubscribe(Strategy::Abstraction* abstraction) {
    this->observerList.remove(abstraction);
}

void Hero::Player::Notify() {
    std::list<Strategy::Abstraction *>::iterator iterator = observerList.begin();
        while (iterator != observerList.end()) {
          (*iterator)->Operation(this);
          ++iterator;
    }
}
void Hero::Player::Hit(int val){
    if(health > 0){
        health -= val;
    }
    if(health < 0){
        health = 0;

        playerScene->removeItem(playerUnit);
        playerUnit = playerScene -> addPixmap(QPixmap(":/Resource/Images/grave.png"));
        playerUnit -> setOffset(curX*110, curY*110);
    }
}

void Hero::Player::operator-=(Enemy<State,Fight>* const& enemy){
        enemy->Hit(attack);
}

bool Hero::Player::IsKilled(){
    return (health == 0);
}



Hero::Player::~Player() {
    playerScene->removeItem(playerUnit);
}


