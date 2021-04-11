#ifndef MILL_H
#define MILL_H

#include "abstracttile.h"
namespace Board{
    class Mill : public AbstractTile{
        int x;
        int y;
        bool used;

        int id = 6;
    public:
        QGraphicsPixmapItem* tile_pixmap_item;
        void SetTileGraphics(QGraphicsScene* scene) override;
        Mill(int x, int y) : x(x), y(y) {}
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
#endif // MILL_H
