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

    // Toolbar Extra Components: gotoLine

    gotoLineEdit=new QLineEdit();
    gotoLineEdit->setFixedWidth(80);

    gotoLineEdit->setPlaceholderText("转到行...");

      QIntValidator *pIntValidator = new QIntValidator(this);
      pIntValidator->setRange(1, 1000000);
      gotoLineEdit->setValidator(pIntValidator);
    ui->mainToolBar->addWidget(gotoLineEdit);
        //此处调整单行输入框位置

    searchWidget = new SearchWidget();

  //  ui->mainToolBar->addWidget(gotoLineEdit);

    // Toolbar Extra Components: Compiler Selector
    fWidget = new QWidget();
    fontlyt = new QHBoxLayout();
    font = new QLabel("字体");
    font->setMargin(3);
    fonts = new QFontComboBox();
    fonts->setEditable(true);
    fonts->setFixedWidth(120);
    fontlyt->addWidget(font);
    fontlyt->addWidget(fonts);
    fontlyt->setMargin(0);
    fontlyt->setSpacing(0);
    fontlyt->setContentsMargins(0,0,0,0);
    fWidget->setLayout(fontlyt);

    ui->mainToolBar->addWidget(fWidget);

    // MainWidget
    mainWindow = new MainWidget(this);
    this->setCentralWidget(mainWindow);
    /****************************************Window Design End***********************************************/

    /****************************************Editor Slots Begin***********************************************/
    connect(mainWindow->editorWin,&EditorWidget::sendFilePath,this,&MainWindow::on_receiveFilePath);

    connect(ui->actionNSrcCode, &QAction::triggered, this, [=](){
        mainWindow->editorWin->on_actionNSrcCode();
    });
    connect(ui->actionOpen, &QAction::triggered, this,[=](){

        mainWindow->editorWin->on_actionOpen();
    });
    connect(ui->actionSave, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionSave();
    });
    connect(ui->actionSaveAs, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionSavaAS();
    });
    connect(ui->actionClose, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionClose();
    });
    connect(ui->actionCloseAll, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionCloseAll();
    });
    connect(ui->actionUndo, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeUndo();
    });
    connect(ui->actionRedo, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeRedo();
    });
    connect(ui->actionSelectAll, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeSelectAll();
    });
    connect(ui->actionFOR, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertFor();
    });
    connect(ui->actionWHILE, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertWhile();
    });
    connect(ui->actionDO_WHILE, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertDoWhile();
    });
    connect(ui->actionIF, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertIf();
    });
    connect(ui->actionSWITCH, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertSwitch();
    });
    connect(ui->actionCLASS, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertClass();
    });
    connect(ui->actionIFDEF, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertIfdef();
    });
    connect(ui->actionIFNDEF, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertIfndef();
    });
    connect(ui->actionIFDEF_ELSE, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertIfdefE();
    });
    connect(ui->actionIFNDEF_ELSE, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeInsertIfndefE();
    });
    connect(ui->actionCut, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionCut();
    });
    connect(ui->actionCopy, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionCopy();
    });
    connect(ui->actionPaste, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionPaste();
    });
    connect(ui->actionCollectAll, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeFoldAll();
    });
    connect(ui->actionExpandall, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_activeExpandall();
    });
    connect(ui->actionAbout, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionAbout();
    });
    connect(ui->actionSaveAll, &QAction::triggered, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_actionSaveAll();
    });
    connect(fonts, &QFontComboBox::currentFontChanged, this,[=](){
        if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
            return;
        mainWindow->editorWin->on_font_change(fonts->currentFont());
    });
    /****************************************Editor Slots End***********************************************/

    /****************************************Compile Part Begin***********************************************/
    commandPart = new CmdPart(mainWindow->bottomWin->compLogTabWin);
    connect(this,SIGNAL(mainwindowRun()),commandPart,SLOT(onMainWindowRun()));
    connect(this,SIGNAL(mainwindowCompile()),commandPart,SLOT(onMainWindowCompile()));
    connect(this,SIGNAL(mainWindowCplandRun()),commandPart,SLOT(onMainWindowCompileandRun()));
    connect(commandPart,&CmdPart::boxShow,mainWindow->bottomWin,&BottomWidget::on_btnCompLog_clicked);
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
void MainWindow::on_receiveFilePath(QString a)
{
    filePath = a;

}

/* File Operation End */

/* Compile Part Begin */
//编译
void MainWindow::on_actionCompile_triggered()
{
    if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
        return;
    mainWindow->editorWin->on_actionSave();
    commandPart->setPath(filePath);
    emit mainwindowCompile();
}
 // 运行
void MainWindow::on_actionRun_triggered()
{   if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
        return;
    emit mainwindowRun();
}
 // 编译运行
void MainWindow::on_actionCompRun_triggered()
{
    if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())
        return;
    mainWindow->editorWin->on_actionSave();
    commandPart->setPath(filePath);
    emit mainWindowCplandRun();

}
/* Compile Part End */



/*******************************************************查找替换部分 Start*******************************************************/

int MainWindow::initSearch(){
    if(mainWindow->editorWin->mdiArea->subWindowList().isEmpty()) return -1;
        //初始化
        searchWidget->resultTable=mainWindow->bottomWin->searchResTabWin;
        //信号绑定
        connect(searchWidget,&SearchWidget::onFocus,this,&MainWindow::focus); //焦点
        connect(searchWidget,&SearchWidget::tableShow,mainWindow->bottomWin,&BottomWidget::on_btnSearchRes_clicked); //结果显示
        connect(searchWidget,&SearchWidget::tableClose,mainWindow->bottomWin,&BottomWidget::on_btnClose_clicked);
        connect(searchWidget,&SearchWidget::updateEditor,this,&MainWindow::updateEditor);
     return 1;
}

void MainWindow::on_actionSearch_triggered()
{
    if(flagSearch!=1) flagSearch =initSearch();
    if(flagSearch==-1) return;
    updateEditor();

     if(searchWidget->isMinimized()) searchWidget->showNormal();
            searchWidget->show();

     focus();
    searchWidget->raise();
}

void MainWindow::focus(){

    activateWindow();
    sf->textEdit->setFocus();

}

void MainWindow::updateEditor(){
       sf = (SourceFileWidget*)mainWindow->editorWin->mdiArea->activeSubWindow()->widget();
       searchWidget->editor=sf->textEdit;
}



//转到行
void MainWindow::on_action_gotoLine_triggered()
{
    if (mainWindow->editorWin->mdiArea->subWindowList().isEmpty())     return;

    sf = (SourceFileWidget*)mainWindow->editorWin->mdiArea->activeSubWindow()->widget();
    QString s= gotoLineEdit->text();
    int i= s.toInt();
    int count = sf->textEdit->SendScintilla(QsciScintilla::SCI_GETLINECOUNT);
    if(i>0&&i<=count) {
        sf->textEdit->SendScintilla(QsciScintilla::SCI_GOTOLINE,i-1);
    }
    else{
        QMessageBox * msg =new QMessageBox();
        msg->setText("不存在该行！");
        msg->show();
    }
    focus();
}
/********************************************查找替换部分 END***********************************************************/






