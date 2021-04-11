#include "Headers/fortress.h"

void Board::Fortress::SetTileGraphics(QGraphicsScene* scene){
    tile_pixmap_item = scene->addPixmap(QPixmap(":/Resource/Images/fortress.jpg"));
    tile_pixmap_item -> setOffset(x*110, y*110);
    tile_pixmap_item->setFlag(QGraphicsItem::ItemIsSelectable);
}
