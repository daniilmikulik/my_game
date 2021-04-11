#include "Headers/map.h"


Board::Map* Board::Map::map_ = nullptr;;

Board::Map::Map(unsigned int height_, unsigned int width_, int** arr, QGraphicsScene* scene){
    this -> map_array = new Tile*[height_];
    Strategy::TileObserver* tileObserver = new Strategy::TileObserver();
    Strategy::Abstraction* abstraction = new Strategy::Abstraction(tileObserver);
    for (unsigned int i = 0; i < height_; i++){
        map_array[i] = new Tile[width_];
    }
    for (unsigned int i = 0; i < height_; i++){
        for (unsigned int j = 0; j < width_; j++){
                map_array[i][j] = Tile();
                int val = arr[i][j];
                Factory::ConcreteFactory factory;
                switch (val){
                case 1:
                    map_array[i][j].AddTile(factory.CreateFieldTile(j, i));
                    break;
                case 2:
                    map_array[i][j].AddTile(factory.CreateLakeTile(j, i));
                    break;
                case 3:
                    map_array[i][j].AddTile(factory.CreateRockTile(j, i));
                    break;
                case 4:
                    map_array[i][j].AddTile(factory.CreateForestTile(j, i));
                    break;
                case 5:
                    map_array[i][j].AddTile(factory.CreateFortressTile(j, i));
                    break;
                case 6:
                    map_array[i][j].AddTile(factory.CreateMillTile(j, i));
                    break;
                case 7:
                    map_array[i][j].AddTile(factory.CreateTowerTile(j, i));
                    break;
                case 8:
                    map_array[i][j].AddTile(factory.CreateVillageTile(j, i));
                    break;
                case 9:
                    map_array[i][j].AddTile(factory.CreateStartTile(j, i));
                    break;
                case 10:
                    map_array[i][j].AddTile(factory.CreateStopTile(j, i));
                    break;
                }

            map_array[i][j].Subscribe(abstraction);
            map_array[i][j].object->SetTileGraphics(scene);
            map_array[i][j].Notify();
            map_array[i][j].Unsubscribe(abstraction);
        }
    }
    this -> height = height_;
    this -> width = width_;
    delete tileObserver;
    delete abstraction;
}


Board::Map *Board::Map::GetInstance(unsigned int height_, unsigned int width_, int** arr, QGraphicsScene* scene){
    if (map_ == nullptr){
        map_ = new Map(height_, width_, arr, scene);
    }
    return map_;
}

Board::Map *Board::Map::GetMap(){
    return map_;
}

Board::Tile& Board::Map::GetTile(int x, int y){
    return map_array[y][x];
}

void Board::Map::Repaint(unsigned int height_, unsigned int width_, int** arr, QGraphicsScene* scene){
    this -> map_array = new Tile*[height_];
    Strategy::TileObserver* tileObserver = new Strategy::TileObserver();
    Strategy::Abstraction* abstraction = new Strategy::Abstraction(tileObserver);
    for (unsigned int i = 0; i < height_; i++){
        map_array[i] = new Tile[width_];
    }
    for (unsigned int i = 0; i < height_; i++){
        for (unsigned int j = 0; j < width_; j++){
                map_array[i][j] = Tile();
                int val = arr[i][j];
                Factory::ConcreteFactory factory;
                switch (val){
                case 1:
                    map_array[i][j].AddTile(factory.CreateFieldTile(j, i));
                    break;
                case 2:
                    map_array[i][j].AddTile(factory.CreateLakeTile(j, i));
                    break;
                case 3:
                    map_array[i][j].AddTile(factory.CreateRockTile(j, i));
                    break;
                case 4:
                    map_array[i][j].AddTile(factory.CreateForestTile(j, i));
                    break;
                case 5:
                    map_array[i][j].AddTile(factory.CreateFortressTile(j, i));
                    break;
                case 6:
                    map_array[i][j].AddTile(factory.CreateMillTile(j, i));
                    break;
                case 7:
                    map_array[i][j].AddTile(factory.CreateTowerTile(j, i));
                    break;
                case 8:
                    map_array[i][j].AddTile(factory.CreateVillageTile(j, i));
                    break;
                case 9:
                    map_array[i][j].AddTile(factory.CreateStartTile(j, i));
                    break;
                case 10:
                    map_array[i][j].AddTile(factory.CreateStopTile(j, i));
                    break;
                }

            map_array[i][j].Subscribe(abstraction);
            map_array[i][j].object->SetTileGraphics(scene);
            map_array[i][j].Notify();
            map_array[i][j].Unsubscribe(abstraction);
        }
    }
    this -> height = height_;
    this -> width = width_;
    delete tileObserver;
    delete abstraction;
}

void Board::Map::Clear(QGraphicsScene* scene){
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int j = 0; j < width; j++){
            map_array[i][j].object->Clear(scene);
            delete map_array[i][j].object;
        }
    }
    for (unsigned int i = 0; i < height; i++){
        delete [] map_array[i];
    }
    delete [] map_array;
}

Board::Map::~Map(){
    for (unsigned int i = 0; i < height; i++){
        for (unsigned int j = 0; j < width; j++){
            delete map_array[i][j].object;
        }
    }
    for (unsigned int i = 0; i < height; i++){
        delete [] map_array[i];
    }
    delete [] map_array;
}

Board::MapIterator::MapIterator(Map* map){
    //ptrMap = Map::GetMap();
    heightIndex = map->height - 1;
    widthIndex = 0;
}

Board::Tile& Board::MapIterator::GetCurrent(){
    return Map::map_->GetTile(widthIndex, heightIndex);
}

void Board::MapIterator::NextRight(){
    if ((widthIndex + 1) == Map::map_->width){
        return;
    }
    Tile& nextTile = Map::map_->GetTile(widthIndex+1, heightIndex);
    if (!nextTile.IsPassable())
        return;
    widthIndex++;
    unit -> SetCurTile(this->GetCurrent());
    unit -> SetCurX(widthIndex);
    unit -> SetCurY(heightIndex);
    unit -> Move();//setOffset(110*widthIndex, 110*heightIndex);

}
void Board::MapIterator::NextLeft(){
    if ((widthIndex) < 1){
        return;
    }
    Tile& nextTile = Map::map_->GetTile(widthIndex-1, heightIndex);
    if (!nextTile.IsPassable())
        return;
     widthIndex--;
     unit -> SetCurTile(this->GetCurrent());
     unit -> SetCurX(widthIndex);
     unit -> SetCurY(heightIndex);
     unit -> Move();//unit -> setOffset(110*widthIndex, 110*heightIndex);
}
void Board::MapIterator::NextUp(){
    if ((heightIndex) < 1){
        return;
    }
    Tile& nextTile = Map::map_->GetTile(widthIndex, heightIndex-1);
    if (!nextTile.IsPassable())
        return;
    heightIndex--;
    unit -> SetCurTile(this->GetCurrent());
    unit -> SetCurX(widthIndex);
    unit -> SetCurY(heightIndex);
    unit -> Move();//unit -> setOffset(110*widthIndex, 110*heightIndex);
}
void Board::MapIterator::NextDown(){
    if ((heightIndex + 1) == Map::map_->height){
        return;
    }
    Tile& nextTile = Map::map_->GetTile(widthIndex, heightIndex+1);
    if (!nextTile.IsPassable())
        return;
    heightIndex++;
    unit -> SetCurTile(this->GetCurrent());
    unit -> SetCurX(widthIndex);
    unit -> SetCurY(heightIndex);
    unit -> Move();//unit -> setOffset(110*widthIndex, 110*heightIndex);
}

void Board::MapIterator::SpawnMainUnit(QGraphicsScene* scene){
    for (unsigned int i = 0; i < Map::map_->height; i++){
        for (unsigned int j = 0; j < Map::map_->width; j++){
            Tile& tile = Map::map_->GetTile(j, i);
            if(tile.GetTileInfo() == 9){
                widthIndex = j;
                heightIndex = i;
                break;
            }
        }
    }

    unit = new Hero::Player(widthIndex, heightIndex, scene, this->GetCurrent());
}

bool Board::MapIterator::IsDone(){
    //return ((heightIndex == 0) && (widthIndex == (Map::map_->width - 1)));
    return ((this->GetCurrent().GetTileInfo() == 10) || (unit->IsKilled()));
}

Hero::Player* Board::MapIterator::GetUnit(){
    return unit;
}

Board::MapIterator::~MapIterator(){
    delete unit;
}


