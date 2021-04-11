#include "Headers/rock.h"

void Board::Rock::SetTileGraphics(QGraphicsScene* scene){
    tile_pixmap_item = scene->addPixmap(QPixmap(":/Resource/Images/rock.jpg"));
    tile_pixmap_item -> setOffset(x*110, y*110);
    tile_pixmap_item->setFlag(QGraphicsItem::ItemIsSelectable);
}
