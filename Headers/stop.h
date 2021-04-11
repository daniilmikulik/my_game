#ifndef STOP_H
#define STOP_H

#include "abstracttile.h"

namespace Board{
class Stop : public AbstractTile{
    int x;
    int y;
    bool used;
    int id = 10;
public:
    QGraphicsPixmapItem* tile_pixmap_item;
    QGraphicsPixmapItem* flag_item;
    void SetTileGraphics(QGraphicsScene* scene) override;
    Stop(int x, int y) : x(x), y(y), used(false) {}
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
        scene->removeItem(flag_item);
    }
};
}

#endif // STOP_H
