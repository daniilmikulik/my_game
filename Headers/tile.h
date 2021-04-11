#ifndef TILE_H
#define TILE_H
#include "abstracttile.h"

#include <iostream>

#include "Headers/field.h"
#include "Headers/tower.h"
#include "Headers/rock.h"
#include "Headers/lake.h"
#include "Headers/forest.h"
#include "Headers/fortress.h"
#include "Headers/start.h"
#include "Headers/stop.h"
#include "Headers/mill.h"
#include "Headers/village.h"
#include "Headers/publisher.h"
#include "Headers/observer.h"

#define FILE_NAME "tile.txt"

namespace Board{
    class Tile : public Publisher{
    private:
        bool isPassable;
        //std::list<AbstractObserver*> observerList;
        std::list<Strategy::Abstraction*> observerList;
    public:
        AbstractTile* object;
        Tile();
        void AddTile(AbstractTile* tile);
        bool IsPassable();
        void SetStartPoint();
        void SetEndPoint();
        int GetTileInfo();
        void Subscribe(Strategy::Abstraction* abstraction) override;
        void Unsubscribe(Strategy::Abstraction* abstraction) override;
        void Notify() override;
        friend std::ostream& operator<<(std::ostream &out, Tile* unit){
            out << "TILE: its id is: " << unit->object->GetTileId() << "\n";
            return out;
        }
    };
}

namespace Strategy{
    class TileObserver : public Strategy::AbstractObserver{
        std::fstream file;
    public:
        TileObserver(){
            file.open(FILE_NAME, std::fstream::in | std::fstream::out | std::fstream::app );
        }
        void Update(Publisher* unit) override{
            std::cout << dynamic_cast<Board::Tile*>(unit);
            file << dynamic_cast<Board::Tile*>(unit);
        }
        virtual ~TileObserver(){
            file.close();
        }
    };
}

#endif // TILE_H
