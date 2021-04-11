#ifndef START_H
#define START_H

#include "abstracttile.h"

namespace Board{
class Start : public AbstractTile{
    int x;
    int y;
    bool used;

    int id = 9;
public:
    QGraphicsPixmapItem* tile_pixmap_item;
    QGraphicsPixmapItem* flag_item;
    void SetTileGraphics(QGraphicsScene* scene) override;
    Start(int x, int y) : x(x), y(y), used(false) {}
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

#endif // START_H
