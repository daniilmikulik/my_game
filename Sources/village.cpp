#include "Headers/village.h"


void Board::Village::SetTileGraphics(QGraphicsScene* scene){
    tile_pixmap_item = scene->addPixmap(QPixmap(":/Resource/Images/village.jpg"));
    tile_pixmap_item -> setOffset(x*110, y*110);
    tile_pixmap_item->setFlag(QGraphicsItem::ItemIsSelectable);
}
