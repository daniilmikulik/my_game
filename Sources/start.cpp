#include "Headers/start.h"

void Board::Start::SetTileGraphics(QGraphicsScene* scene){
    tile_pixmap_item = scene->addPixmap(QPixmap(":/Resource/Images/field.jpg"));
    tile_pixmap_item -> setOffset(x*110, y*110);
    tile_pixmap_item->setFlag(QGraphicsItem::ItemIsSelectable);
    flag_item = scene->addPixmap(QPixmap(":/Resource/Images/finish_flag.png"));
    flag_item -> setOffset(x*110, y*110);

}
