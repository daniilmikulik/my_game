#include "Headers/facade.h"

Facade::Facade(QGraphicsScene *scene, int val){
    int** arr_num = nullptr;
    mapTemplate = val;
    this->scene = scene;
    int arr1[6][6] = {{1, 1, 1, 4, 1, 1},
                      {1, 5, 1, 4, 4, 1},
                      {1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 2, 1, 1},
                      {9, 1, 4, 5, 1, 1},
                      {3, 1, 6, 1, 1, 10}};
    int arr2[8][8] = {{1, 1, 1, 1, 1, 1, 7, 10},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {4, 2, 1, 4, 1, 1, 1, 1},
                      {4, 4, 4, 4, 4, 4, 1, 1},
                      {4, 4, 4, 4, 3, 1, 1, 1},
                      {1, 1, 1, 4, 1, 1, 1, 3},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {9, 1, 1, 1, 7, 1, 1, 1}};
    int arr3[10][10] = {{4, 4, 1, 1, 1, 1, 1, 1, 1, 10},
                        {3, 8, 1, 4, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 4, 4, 4, 1, 1, 1},
                        {1, 1, 1, 4, 4, 2, 4, 4, 4, 1},
                        {1, 1, 1, 1, 4, 4, 4, 3, 1, 1},
                        {1, 1, 1, 1, 1, 4, 3, 1, 1, 1},
                        {1, 1, 1, 1, 1, 4, 1, 1, 1, 1},
                        {7, 1, 1, 1, 1, 1, 1, 1, 5, 6},
                        {1, 1, 1, 1, 1, 1, 1, 1, 8, 8},
                        {9, 1, 7, 1, 1, 1, 1, 1, 1, 1}};
    int HEIGHT = 0;
    int WIDTH = 0;

    switch (val){
    case 1:
        HEIGHT = 6;
        WIDTH = 6;
        arr_num = new int*[HEIGHT];
        for (int i = 0; i < WIDTH; i++){
            arr_num[i] = new int[WIDTH];
        }
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                    arr_num[i][j] = arr1[i][j];
            }
        }
        break;

    case 2:
        HEIGHT = 8;
        WIDTH = 8;
        arr_num = new int*[HEIGHT];
        for (int i = 0; i < WIDTH; i++){
            arr_num[i] = new int[WIDTH];
        }
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                    arr_num[i][j] = arr2[i][j];
            }
        }
        break;

    case 3:
        HEIGHT = 10;
        WIDTH = 10;
        arr_num = new int*[HEIGHT];
        for (int i = 0; i < WIDTH; i++){
            arr_num[i] = new int[WIDTH];
        }
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                    arr_num[i][j] = arr3[i][j];
            }
        }
        break;
    }

     main_map = Board::Map::GetInstance(HEIGHT, WIDTH, arr_num, this->scene);

     for (int i = 0; i < HEIGHT; i++){
         delete [] arr_num[i];
     }
     delete [] arr_num;
     command = nullptr;

     //StartGame(scene);

}

void Facade::StartGame(){
    if(mapTraverse){
        delete mapTraverse;
        for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
                    scene->removeItem(((*it)->enemyUnit));
        //            delete (*it);
        //            //enemies.erase(it);
        }
        //for(int i = 0; i < (int)enemies.size(); i++){
        //    enemies.erase(enemies[i]);
        //}
        enemies.clear();
    }

    mapTraverse = new Board::MapIterator(main_map);
    mapTraverse->SpawnMainUnit(scene);
    playerMoveObserver = new Strategy::PlayerMoveObserver();
    abstraction = new Strategy::Abstraction(playerMoveObserver);
    mapTraverse->GetUnit() -> Subscribe(abstraction/*playerMoveObserver*/);
    SpawnEnemies();
    ChangeCondition(new PlayerMove);

}

void Facade::Repaint(int val){
    main_map->Clear(scene);
    mapTemplate = val;
    int** arr_num = nullptr;
    int arr1[6][6] = {{1, 1, 1, 4, 1, 1},
                      {1, 5, 1, 4, 4, 1},
                      {1, 1, 1, 1, 1, 1},
                      {1, 1, 1, 2, 1, 1},
                      {9, 1, 4, 5, 1, 1},
                      {3, 1, 6, 1, 1, 10}};
    int arr2[8][8] = {{1, 1, 1, 1, 1, 1, 7, 10},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {4, 2, 1, 4, 1, 1, 1, 1},
                      {4, 4, 4, 4, 4, 4, 1, 1},
                      {4, 4, 4, 4, 3, 1, 1, 1},
                      {1, 1, 1, 4, 1, 1, 1, 3},
                      {1, 1, 1, 1, 1, 1, 1, 1},
                      {9, 1, 1, 1, 7, 1, 1, 1}};
    int arr3[10][10] = {{4, 4, 1, 1, 1, 1, 1, 1, 1, 10},
                        {3, 8, 1, 4, 1, 1, 1, 1, 1, 1},
                        {1, 1, 1, 1, 4, 4, 4, 1, 1, 1},
                        {1, 1, 1, 4, 4, 2, 4, 4, 4, 1},
                        {1, 1, 1, 1, 4, 4, 4, 3, 1, 1},
                        {1, 1, 1, 1, 1, 4, 3, 1, 1, 1},
                        {1, 1, 1, 1, 1, 4, 1, 1, 1, 1},
                        {7, 1, 1, 1, 1, 1, 1, 1, 5, 6},
                        {1, 1, 1, 1, 1, 1, 1, 1, 8, 8},
                        {9, 1, 7, 1, 1, 1, 1, 1, 1, 1}};
    int HEIGHT = 0;
    int WIDTH = 0;

    switch (val){
    case 1:
        HEIGHT = 6;
        WIDTH = 6;
        arr_num = new int*[HEIGHT];
        for (int i = 0; i < WIDTH; i++){
            arr_num[i] = new int[WIDTH];
        }
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                    arr_num[i][j] = arr1[i][j];
            }
        }
        break;

    case 2:
        HEIGHT = 8;
        WIDTH = 8;
        arr_num = new int*[HEIGHT];
        for (int i = 0; i < WIDTH; i++){
            arr_num[i] = new int[WIDTH];
        }
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                    arr_num[i][j] = arr2[i][j];
            }
        }
        break;

    case 3:
        HEIGHT = 10;
        WIDTH = 10;
        arr_num = new int*[HEIGHT];
        for (int i = 0; i < WIDTH; i++){
            arr_num[i] = new int[WIDTH];
        }
        for (int i = 0; i < HEIGHT; i++){
            for (int j = 0; j < WIDTH; j++){
                    arr_num[i][j] = arr3[i][j];
            }
        }
        break;
    }

     main_map->Board::Map::Repaint(HEIGHT, WIDTH, arr_num, scene);

     for (int i = 0; i < HEIGHT; i++){
         delete [] arr_num[i];
     }
     delete [] arr_num;
}

void Facade::SetCommand(Strategy::Command *command){
    this->command = command;
}

bool Facade::IteratorConsists(){
    return (mapTraverse != nullptr);
}

bool Facade::IsPlayerKilled(){
    return mapTraverse->GetUnit()->IsKilled();
}

bool Facade::IsGameEnded(){
    return (mapTraverse -> IsDone());
}

QString Facade::Execute(){
    command->Execute(this->mapTraverse);
    Hero::Player* player = mapTraverse->GetUnit();
    QString line = player->GetInfo();
    return line;
}

QString Facade::Info(){
    Hero::Player* player = mapTraverse->GetUnit();
    QString line = player->GetInfo();
    return line;
}

void Facade::SpawnEnemies(){
    Hero::Enemy<State,Fight>* enemy = Hero::Enemy<State,Fight>::GetInstance(1, 1, this->scene, main_map->GetTile(1,1));
    enemies.push_back(enemy);
}

void Facade::Clashed(){
    Hero::Player* player = mapTraverse->GetUnit();
    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
        if((!(*it)->IsKilled()) && (!(player)->IsKilled())){
            if(((*it)->GetCurX() == (*it)->GetPlayerX()) && ((*it)->GetCurY() == (*it)->GetPlayerY())){
                Hero::Enemy<State,Fight>* enemy = (*it);
                *player -= enemy;
                *enemy -= player;
            }
        }
    }
}

void Facade::SetPlayerPosition(){
    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
        (*it)->SetPlayerCoord(mapTraverse->GetUnit()->GetCurX(), mapTraverse->GetUnit()->GetCurY());
    }
}

void Facade::ChangeCondition(Condition *cond){
    if(this->condition){
        delete this->condition;
    }
    this->condition = cond;
    this->condition->setFacade(this);
}

void Facade::Request(){
    this->condition->Handle();
}

void Facade::SetEnemyStrategies(){
    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
        if (!(*it)->IsKilled()){
            (*it)->DefineBehaviour();
        }
    }
    Hero::Player* player = mapTraverse->GetUnit();
    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
        if (!(*it)->IsKilled()){

            if((*it)->Fire()){
                std::cout<<"FIRE"<< std::endl;
                *(*it) -= player;
            } else if ((*it)->MoveCond()) {
                std::pair<int,int> pair = (*it)->MoveAI();
                //cout << pair.first << " " << pair.second;
                if ((pair.first > 0 && (unsigned int)pair.first < main_map->width) && (pair.second > 0 && (unsigned int)pair.second < main_map->height)){
                    Board::Tile& tile = main_map->GetTile(pair.first, pair.second);
                    if(tile.IsPassable()){
                        (*it)->SetCurX(pair.first);
                        (*it)->SetCurY(pair.second);
                        (*it)->Move();
                    }
                }
                std::cout<<"ATTACK" << std::endl;
            }
        }
    }
}
Facade::FacadeMemento* Facade::Save(){
    return new FacadeMemento(*this);
}

void Facade::Restore(FacadeMemento *mem){

    if(!((mem->enemyX.size() == mem->enemyY.size()) == mem->healthEnemy.size())){
        throw FileException("Invalid enemies' settings!");
    }
    mapTemplate = mem->mapTemplate;
    Repaint(mapTemplate);
    StartGame();
    Hero::Player* player = mapTraverse->GetUnit();
    player->SetCurX(mem->playerX);
    player->SetCurY(mem->playerY);
    player->SetCurTile(main_map->GetTile(mem->playerX,mem->playerY));
    player->SetDefenseBonus(mem->bonusDefense);
    player->SetAttackBonus(mem->bonusAttack);
    player->AddCoins(mem->coins);
    player->SetHealth(mem->health);
    player->Move();

    //cout << mem->playerX << endl;
    //cout << player->GetCurX() << endl;
    mapTraverse->widthIndex = player->GetCurX();
    mapTraverse->heightIndex = player->GetCurY();
    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
                scene->removeItem(((*it)->enemyUnit));
    }
    enemies.clear();

    for(int i = 0; i < (int)mem->enemyX.size(); i++){
        Hero::Enemy<State,Fight>* enemy = Hero::Enemy<State,Fight>::GetInstance(1, 1, this->scene, main_map->GetTile(1,1));

        enemy->SetCurX(mem->enemyX[i]);
        enemy->SetCurY(mem->enemyY[i]);
        enemy->SetHealth(mem->healthEnemy[i]);
        enemies.push_back(enemy);
    }


    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = enemies.begin(); it != enemies.end(); it++){
        (*it)->Move();
    }
}

Facade::~Facade(){
    mapTraverse->GetUnit() -> Unsubscribe(abstraction);
    delete main_map;
    delete mapTraverse;
    delete playerMoveObserver;
    delete abstraction;
}
void PlayerMove::Handle(){
    cout << "Player move" << endl;
    facade->SetPlayerPosition();
    facade->Clashed();
    this->facade->ChangeCondition(new EnemyMove);
}

Facade::FacadeMemento::FacadeMemento(Facade& facade){
    scene = facade.scene;
    mapTemplate = facade.mapTemplate;
    Hero::Player* player = facade.mapTraverse->GetUnit();
    playerX = player->GetCurX();
    playerY = player->GetCurY();
    bonusDefense = player->GetDefenseBonus();
    bonusAttack = player->GetAttackBonus();
    coins = player->GetCoins();
    health = player->GetHealth();

    for(std::vector<Hero::Enemy<State,Fight>*>::iterator it = facade.enemies.begin(); it != facade.enemies.end(); it++){
        enemyX.push_back( (*it)->GetCurX());
        enemyY.push_back( (*it)->GetCurY());
        healthEnemy.push_back( (*it)->GetHealth());
        attackState.push_back((*it)->attackState);
        moveState.push_back( (*it)->moveState);
    }
    std::time_t now = std::time(0);
    date = std::ctime(&now);
    date.pop_back();
    std::string filename =  date + ".txt";
    std::cout << filename << std::endl;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app );
    if (!fs){
        throw FileException("Invalid file");
    }
    else{
        SaveToFile();
    }
}

Facade::FacadeMemento::FacadeMemento(std::string& filename){
    fs.open(filename, std::fstream::in | std::fstream::out  | std::fstream::app);
    if(!fs){
        throw FileException("Invalid file");
    }
    else{
        LoadFromFile();
    }
}

std::string Facade::FacadeMemento::Date(){
    return this->date;
}

void Facade::FacadeMemento::LoadFromFile(){
    cout << "Restored" << endl;
    fs >> mapTemplate;
    if (!fs)
        throw FileException("Unable to load data");
    fs >> playerX;
    if (!fs)
        throw FileException("Unable to load data");
    fs >> playerY;
    if (!fs)
        throw FileException("Unable to load data");
    fs >> bonusDefense;
    if (!fs)
        throw FileException("Unable to load data");
    fs >> bonusAttack;
    if (!fs)
        throw FileException("Unable to load data");
    fs >> coins;
    if (!fs)
        throw FileException("Unable to load data");
    fs >> health;
    if (!fs)
        throw FileException("Unable to load data");
    std::string line;
    while(getline(fs, line)){
        QString qs = QString::fromLocal8Bit(line.c_str());
        QStringList list  = qs.split(",");
            cout << line << endl;

            cout << "LENGTH:" << endl;
            cout << list.length() << endl;
            if(list.length() == 3){
                enemyX.push_back(list[0].toInt());
                enemyY.push_back(list[1].toInt());
                healthEnemy.push_back(list[2].toInt());
            } else {
                cout << "Can't read" << endl;
            }

    }

}

void Facade::FacadeMemento::SaveToFile(){
    cout << "Saved" << endl;
    cout << date << endl;


    fs << mapTemplate << endl;
    if (!fs)
        throw FileException("Unable to write data");
    fs << playerX << endl;
    if (!fs)
        throw FileException("Unable to write data");
    fs << playerY << endl;
    if (!fs)
        throw FileException("Unable to write data");
    fs << bonusDefense << endl;
    if (!fs)
        throw FileException("Unable to write data");
    fs << bonusAttack << endl;
    if (!fs)
        throw FileException("Unable to write data");
    fs << coins << endl;
    if (!fs)
        throw FileException("Unable to write data");
    fs << health << endl;
    if (!fs)
        throw FileException("Unable to write data");

    for (int i = 0; i < (int)enemyX.size(); i++){
        fs << enemyX[i] << ",";
        if (!fs)
            throw FileException("Unable to write data");
        fs << enemyY[i] << ",";
        if (!fs)
            throw FileException("Unable to write data");
        fs << healthEnemy[i] << endl;
        if (!fs)
            throw FileException("Unable to write data");
    }


}

Facade::FacadeMemento::~FacadeMemento(){
     fs.close();
}

FacadeCaretaker::FacadeCaretaker(Facade* facade){
    this->facade = facade;
}

void FacadeCaretaker::BackUp(){
    mementos.push_back(facade->Save());
}

void FacadeCaretaker::Undo(){
    facade->Restore(mementos.back());
    mementos.pop_back();
}
Memento* FacadeCaretaker::GetMemento(){
    return mementos.back();
}

void FacadeCaretaker::SetMemento(Facade::FacadeMemento *mem){
    mementos.push_back(mem);
}

