#include "Headers/tile.h"

Board::Tile::Tile(){
    isPassable = true;

}

void Board::Tile::AddTile(Board::AbstractTile* tile){
    object = tile;
    int id = tile->GetTileId();
    if ( id == 2 || id == 4 )
        isPassable = false;
}

bool Board::Tile::IsPassable(){
    return this->isPassable;
}

void Board::Tile::Subscribe(Strategy::Abstraction* abstraction) {
    this->observerList.push_back(abstraction);
}

void Board::Tile::Unsubscribe(Strategy::Abstraction* abstraction) {
    this->observerList.remove(abstraction);
}

void Board::Tile::Notify() {
    std::list<Strategy::Abstraction *>::iterator iterator = observerList.begin();
        while (iterator != observerList.end()) {
          //std::cout << this;
          (*iterator)->Operation(this);
          ++iterator;
    }
}

int Board::Tile::GetTileInfo(){
    return object->GetTileId();
}

