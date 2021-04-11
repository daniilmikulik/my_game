#ifndef FORTRESS_H
#define FORTRESS_H

#include "abstracttile.h"
namespace Board{
    class Fortress : public AbstractTile{
        int x;
        int y;
        bool used;
        int id = 5;
    public:
        QGraphicsPixmapItem* tile_pixmap_item;
        void SetTileGraphics(QGraphicsScene* scene) override;
        Fortress(int x, int y) : x(x), y(y), used(false) {}
        int GetTileId() override{
            return this->id;
        }
        void SetUsed() override{
            used = true;
        }
        bool IsUsed() override {
            return used == true;
        }
        void Clear(QGraphicsScene* scene) override{
            scene->removeItem(tile_pixmap_item);
        }
    };
}

#endif // FORTRESS_H
