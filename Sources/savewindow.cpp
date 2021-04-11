#include "Headers/savewindow.h"

SaveWindow::SaveWindow(QWidget* parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint)
{
    listLabel = new QLabel("Do you really want to save game?");
    //lineEdit = new QLineEdit;

    okButton = new QPushButton("&Ok");
    cancelButton = new QPushButton("&Cancel");
    okButton->setEnabled(true);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
    //connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(Enable()));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listLabel);
    //mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}

void LoadWindow::Enable(){
    okButton->setEnabled(true);
}

SaveWindow::~SaveWindow(){

}

LoadWindow::LoadWindow(QWidget* parent)
    : QDialog(parent, Qt::WindowTitleHint | Qt::WindowSystemMenuHint){
    listLabel = new QLabel("Choose a file to load:");
    lineEdit = new QLineEdit;
    okButton = new QPushButton("&Ok");
    cancelButton = new QPushButton("&Cancel");
    okButton->setEnabled(false);

    QHBoxLayout* buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(okButton);
    buttonLayout->addWidget(cancelButton);

    connect(okButton, SIGNAL(clicked()), SLOT(accept()));
    connect(cancelButton, SIGNAL(clicked()), SLOT(reject()));
    connect(lineEdit, SIGNAL(textChanged(const QString&)), this, SLOT(Enable()));
    QVBoxLayout* mainLayout = new QVBoxLayout;
    mainLayout->addWidget(listLabel);
    mainLayout->addWidget(lineEdit);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);

}

std::string LoadWindow::GetName(){
    return lineEdit->text().toStdString();
}
