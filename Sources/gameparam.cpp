#include "Headers/gameparam.h"

GameParam::GameParam(QWidget* parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    listLabel = new QLabel("Your list of maps:");

    mapList = new QListWidget(this);
    QListWidgetItem* firstItem = new QListWidgetItem;
    firstItem->setText("The first map");
    mapList->insertItem(1, firstItem);
    QListWidgetItem* secondItem = new QListWidgetItem;
    secondItem->setText("The second map");
    mapList->insertItem(2, secondItem);
    QListWidgetItem* thirdItem = new QListWidgetItem;
    thirdItem->setText("The third map");
    mapList->insertItem(3, thirdItem);

    connect(mapList, SIGNAL(doubleClicked( QModelIndex)), this, SLOT(SetMapIndex(QModelIndex)));

    okButton = new QPushButton("&Ok");
    cancelButton = new QPushButton("&Cancel");
    okButton -> setEnabled(false);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout -> addWidget(okButton);
    buttonLayout -> addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));

    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout -> addWidget(listLabel);
    mainLayout -> addWidget(mapList);
    mainLayout -> addLayout(buttonLayout);
    setLayout(mainLayout);
}

int GameParam::GetMapIndex(){
    return mapIndex;
}

void GameParam::SetMapIndex(const QModelIndex& index){
    if( !index.isValid() ) {
                return;
    }
    this -> mapIndex = index.row() + 1;
    this -> okButton -> setEnabled(true);
}

GameParam::~GameParam(){

}
