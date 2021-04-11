#ifndef ABSTRACTTILE_H
#define ABSTRACTTILE_H

#include "libs.h"
namespace Board{
    class AbstractTile
    {
    public:
        virtual ~AbstractTile() {};
        void virtual SetTileGraphics(QGraphicsScene* scene)=0;
        int virtual GetTileId()=0;
        void virtual SetUsed() = 0;
        bool virtual IsUsed() = 0;
        void virtual Clear(QGraphicsScene* scene) = 0;
    };
}
#endif // ABSTRACTTILE_H
