#include "Headers/mainwindow.h"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent){
    InitScene();
    InitToolBar();
    InitMenuBar();
    InitStatusBar();


    QHBoxLayout *main_layout = new QHBoxLayout;
    main_layout -> addWidget(view);

    central_widget = new QWidget(this);
    central_widget -> setLayout(main_layout);
    this -> setCentralWidget(central_widget);
    this->setStyleSheet("background-color: #86B549;");
    this->resize(1200, 700);
    this->setWindowTitle("My first game");
    this->setWindowIcon(QIcon(":/Resource/Images/new_game.png"));
}

void MainWindow::InitToolBar(){
    main_bar = new QToolBar("Game options:");
    main_bar->addAction(QIcon(":/Resource/Images/new_game.png"), "New Game", this, SLOT(DialogSlot()));
    main_bar->addAction(QIcon(":/Resource/Images/save.png"), "Save Game", this, SLOT(SaveSlot()));
    main_bar->addAction(QIcon(":/Resource/Images/load.png"), "Load Game", this, SLOT(LoadSlot()));
    main_bar->addAction(QIcon(":/Resource/Images/info.png"), "Info");
    main_bar->addAction(QIcon(":/Resource/Images/exit.png"), "Exit", this, SLOT(close()));
    addToolBar(Qt::RightToolBarArea, main_bar);
    main_bar->setIconSize(QSize(100, 100));


}

void MainWindow::LoadSlot()
{
    LoadWindow* loadWindow = new LoadWindow();
    if (loadWindow->exec() == QDialog::Accepted && facade) {
        std::string line = loadWindow->GetName();
        Facade::FacadeMemento* mem = new Facade::FacadeMemento(line);
        caretaker->SetMemento(mem);
        caretaker->Undo();
    }
    delete loadWindow;
}

void MainWindow::SaveSlot()
{
    SaveWindow* saveWindow = new SaveWindow();
    if (saveWindow->exec() == QDialog::Accepted && facade) {
        cout << "Used!" << endl;
        caretaker->BackUp();
    }
    delete saveWindow;
}

void MainWindow::DialogSlot()
{
    GameParam* paramWindow = new GameParam();
    if (paramWindow->exec() == QDialog::Accepted) {
        CreateMap(paramWindow -> GetMapIndex());
    }
    delete paramWindow;
}

void MainWindow::InitMenuBar(){
    main_menu = new QMenuBar();
    QMenu* game;
    game = main_menu -> addMenu("&New Game");
    QAction *start = new QAction("&New Game");
    QAction *exit = new QAction("&Exit Game");
    game -> addAction(start);
    game -> addAction(exit);
    QMenu* file;
    file = main_menu -> addMenu("&Your Game");
    QAction *load = new QAction("&Load", this);
    QAction *save = new QAction("&Save", this);
    file -> addAction(load);
    file -> addAction(save);
    QMenu* help;
    help = main_menu -> addMenu("&Help");
    QAction *info = new QAction("&Info");
    help -> addAction(info);
    this -> setMenuBar(main_menu);
}

void MainWindow::InitStatusBar(){
    this->statusBar() -> showMessage("Status bar!");
}

void MainWindow::InitScene(){
    scene = new QGraphicsScene();

    view = new QGraphicsView(scene);
    view->setRenderHint(QPainter::Antialiasing);
    view->setBackgroundBrush(QPixmap(":/Resource/Images/grass.jpg"));


}

void MainWindow::CreateMap(int val){
    if(facade == nullptr){
        facade = new Facade(this->scene, val);
        caretaker = new FacadeCaretaker(facade);
        lCommand = new Strategy::LeftCommand;
        rCommand = new Strategy::RightCommand;
        upCommand = new Strategy::UpCommand;
        downCommand = new Strategy::DownCommand;
    } else {
        //delete facade;
        facade->Repaint(val);
    }
    facade->StartGame();
}



void MainWindow::keyPressEvent( QKeyEvent * event )
{
    if (facade->IteratorConsists()){
    if (facade->IsGameEnded()){
        return;
    }
    if( event->key() == Qt::Key_W )
    {       
        facade->SetCommand(upCommand);
        QString line = facade->Execute();
        facade->Request();
        facade->Request();
        this->statusBar() -> showMessage(line);
    }
    if( event->key() == Qt::Key_S )
    {
        facade->SetCommand(downCommand);
        QString line = facade->Execute();
        facade->Request();
        facade->Request();
        this->statusBar() -> showMessage(line);
    }
    if( event->key() == Qt::Key_A )
    {
        facade->SetCommand(lCommand);
        QString line = facade->Execute();
        facade->Request();
        facade->Request();
        this->statusBar() -> showMessage(line);
    }
    if( event->key() == Qt::Key_D )
    {
       facade->SetCommand(rCommand);
       QString line = facade->Execute();
       facade->Request();
       facade->Request();
       this->statusBar() -> showMessage(line);
    }
    if (event->key() == Qt::Key_I){
        QString line = facade->Info();
        //facade->Request();
        this->statusBar() -> showMessage(line);
    }

    if (facade->IsGameEnded()){
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setText("Game is over:");
        msgBox->setWindowModality(Qt::NonModal);
        if (facade->IsPlayerKilled()){
            msgBox->setInformativeText("You lost!");
        } else {
            msgBox->setInformativeText("You have won!");
        }
        msgBox -> exec();
        return;
    }
    }
}



MainWindow::~MainWindow() {
    delete facade;
    delete lCommand;
    delete rCommand;
    delete upCommand;
    delete downCommand;
}
