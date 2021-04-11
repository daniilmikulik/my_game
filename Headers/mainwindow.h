#ifndef MAINWINDOW_H
#define MAINWINDOW_H


#include "savewindow.h"
#include "gameparam.h"
#include "facade.h"


class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    explicit MainWindow(QWidget* parent = nullptr);
    ~MainWindow();

    void InitToolBar();
    void InitMenuBar();
    void InitStatusBar();
    void InitScene();
    void CreateMap(int val);

public slots:
    void LoadSlot();
    void SaveSlot();
    void DialogSlot();
private slots:
    void keyPressEvent( QKeyEvent * event);
private:
    QWidget *central_widget;
    QToolBar *main_bar;
    QMenuBar *main_menu;
    QGraphicsScene *scene;
    QGraphicsView *view;
    Facade* facade = nullptr;
    Strategy::LeftCommand* lCommand;
    Strategy::RightCommand* rCommand;
    Strategy::UpCommand* upCommand;
    Strategy::DownCommand* downCommand;
    FacadeCaretaker* caretaker;
};

#endif //MAINWINDOW_H
