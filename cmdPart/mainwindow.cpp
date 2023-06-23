#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWidget *mainWindow;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    /***************************************Window Design Begin**********************************************/
    ui->setupUi(this);
    // Menubar Settings
    ui->menuBar->setNativeMenuBar(false);
    // Toolbar Settings
    ui->mainToolBar->setMovable(false);
    ui->mainToolBar->layout()->setMargin(0);
    ui->mainToolBar->layout()->setSpacing(0);
    ui->mainToolBar->layout()->setContentsMargins(5,2,5,2);
    ui->mainToolBar->layout()->setAlignment(Qt::AlignLeft);
    // Toolbar Extra Components: Compiler Selector
    compilerBox = new QComboBox();
    ui->mainToolBar->addWidget(compilerBox);
    // MainWidget
    mainWindow = new MainWidget(this);
    this->setCentralWidget(mainWindow);
    /****************************************Window Design End***********************************************/

    /****************************************Editor Slots Begin***********************************************/
    connect(ui->actionNSrcCode, &QAction::triggered, this, [=](){
        mainWindow->editorWin->on_actionNSrcCode();
    });
    connect(ui->actionOpen, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionOpen();
    });
    connect(ui->actionSave, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionSave();
    });
    connect(ui->actionSaveAs, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionSavaAS();
    });
    connect(ui->actionClose, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionClose();
    });
    connect(ui->actionCloseAll, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionCloseAll();
    });
    connect(ui->actionUndo, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeUndo();
    });
    connect(ui->actionRedo, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeRedo();
    });
    connect(ui->actionSelectAll, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeSelectAll();
    });
    connect(ui->actionFOR, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertFor();
    });
    connect(ui->actionWHILE, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertWhile();
    });
    connect(ui->actionDO_WHILE, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertDoWhile();
    });
    connect(ui->actionIF, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertIf();
    });
    connect(ui->actionSWITCH, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertSwitch();
    });
    connect(ui->actionCLASS, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertClass();
    });
    connect(ui->actionIFDEF, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertIfdef();
    });
    connect(ui->actionIFNDEF, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertIfndef();
    });
    connect(ui->actionIFDEF_ELSE, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertIfdefE();
    });
    connect(ui->actionIFNDEF_ELSE, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_activeInsertIfndefE();
    });
    connect(ui->actionCut, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionCut();
    });
    connect(ui->actionCopy, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionCopy();
    });
    connect(ui->actionPaste, &QAction::triggered, this,[=](){
        mainWindow->editorWin->on_actionPaste();
    });

    /****************************************Editor Slots End***********************************************/

    /****************************************Compile Part Begin***********************************************/
    commandPart = new CmdPart(mainWindow->bottomWin->compLogTabWin);
    connect(this,SIGNAL(mainwindowRun()),commandPart,SLOT(onMainWindowRun()));
    connect(this,SIGNAL(mainwindowCompile()),commandPart,SLOT(onMainWindowCompile()));
    connect(this,SIGNAL(mainWindowCplandRun()),commandPart,SLOT(onMainWindowCompileandRun()));
    QTextEdit *textEdit = new QTextEdit();
    QHBoxLayout *hLayout = new QHBoxLayout();
    hLayout->addWidget(commandPart->complitionInfor);
    hLayout->setMargin(0);
    hLayout->setSpacing(0);
    hLayout->setContentsMargins(5,2,5,2);
    mainWindow->bottomWin->compLogTabWin->setLayout(hLayout);
    /****************************************Compile Part End***********************************************/

}

MainWindow::~MainWindow()
{
    delete ui;
}

/* File Operation Begin */
void MainWindow::on_actionExit_triggered()
{
        exit(0);
}
/* File Operation End */

/* Compile Part Begin */
// 编译
//void MainWindow::on_actionCompile_triggered()
//{
//    on_actionSave_triggered();
//    QFileInfo fileInfo(filePath);
//    QString strFn = fileInfo.fileName();
//    QString strFIleName=strFn;//新的名字
//    commandPart->setPath(filePath);
//    qDebug()<<"compile";
//    emit mainwindowCompile();
//}
// // 运行
//void MainWindow::on_actionRun_triggered()
//{
//    emit mainwindowRun();
//}
// // 编译运行
//void MainWindow::on_actionCompRun_triggered()
//{
//    on_actionSave_triggered();
//    QFileInfo fileInfo(filePath);
//    QString strFn = fileInfo.fileName();
//    QString strFIleName=strFn;//新的名字
//    commandPart->setPath(filePath);
//    emit mainWindowCplandRun();

//}
/* Compile Part End */

