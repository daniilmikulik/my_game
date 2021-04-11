#ifndef GAMEPARAM_H
#define GAMEPARAM_H

#include "libs.h"

class GameParam : public QDialog{
    Q_OBJECT
private:
    QListWidget* mapList;
    QLabel* listLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;
    int mapIndex;
public:
    GameParam(QWidget* parent = nullptr);
    int GetMapIndex();
    ~GameParam();
public slots:
    void SetMapIndex(const QModelIndex& index);
};

#endif // GAMEPARAM_H
