#ifndef SAVEWINDOW_H
#define SAVEWINDOW_H

#include "libs.h"

class SaveWindow : public QDialog{
    Q_OBJECT
private:
    //QListWidget* mapList;
    QLabel* listLabel;
    //QLineEdit* lineEdit;
    QPushButton* okButton;
    QPushButton* cancelButton;
    int mapIndex;
public:
    SaveWindow(QWidget* parent = nullptr);
    ~SaveWindow();

};

class LoadWindow : public QDialog{
    Q_OBJECT
private:
    //QListWidget* mapList;
    QLineEdit* lineEdit;
    QLabel* listLabel;
    QPushButton* okButton;
    QPushButton* cancelButton;

public:
    std::string GetName();
    LoadWindow(QWidget* parent = nullptr);
    ~LoadWindow(){}
public slots:
    void Enable();
};

#endif // SAVEWINDOW_H
