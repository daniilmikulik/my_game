#ifndef MAP_H
#define MAP_H
//#include "tile.h"
#include "player.h"
#include "abstractfactory.h"


namespace Board{
    class Map{
    protected:
        Board::Tile** map_array;
        static Board::Map *map_;
        Map(unsigned int height_, unsigned int width_, int** arr, QGraphicsScene* scene); // protected constructor
    public:
         // an array of tiles
        unsigned int height; // total height of the map (in tiles)
        unsigned int width; // total width of the map (in tiles)
         //a unique Map instance



        Map(Map const& map_elem) = delete; // a copying conctructor
        Map& operator=(Map const& map_elem) = delete; //operator = (assignment and as a result copying is forbidden)

        Map(Map&& map_elem) = delete; //moving constructor
        Map& operator=(Map&& map_elem) = delete; //operator of move

        static Map *GetInstance(unsigned int height_, unsigned int width_, int** arr, QGraphicsScene* scene); //creating a unique Map instance
        static Map *GetMap();

        Tile& GetTile(int x, int y);
        void Clear(QGraphicsScene* scene);
        void Repaint(unsigned int height_, unsigned int width_, int** arr, QGraphicsScene* scene);
        ~Map();
        friend class MapIterator;
        friend class Hero::Enemy<State,Fight>;
    };


    class MapIterator{
    private:
        Hero::Player* unit;//QGraphicsPixmapItem* unit;
    public:

        MapIterator(Board::Map* map);
        void SpawnMainUnit(QGraphicsScene* scene);
        void NextLeft();
        void NextRight();
        void NextUp();
        void NextDown();
        Hero::Player* GetUnit();
        bool IsDone();
        Board::Tile& GetCurrent();
        unsigned int heightIndex;
        unsigned int widthIndex;
        ~MapIterator();
    };
}

#endif // MAP_H
