#include "editorwidget.h"
#include"mainwidget.h"

extern MainWidget *mainWindow;
QString globalFilePath;

EditorWidget::EditorWidget(QWidget *parent) : QWidget(parent)
{
    // 总体布局
    mainLayout = new QVBoxLayout();
    // 多窗体组件
    mdiArea = new QMdiArea();
    // 多窗体组件设置：Tab多页显示模式
    mdiArea->setViewMode(QMdiArea::TabbedView);
    // 多窗体组件设置：页面可关闭
    mdiArea->setTabsClosable(true);
    // 多窗体组件设置：设置是否可移动
    mdiArea->setTabsMovable(true);
    // 设置Tab的形状，默认长方形，这里设置为梯形
    mdiArea->setTabShape(QTabWidget::Triangular);

    // 设置布局
    mainLayout->addWidget(mdiArea);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainLayout);
    this->setWindowState(Qt::WindowMaximized);


}

// 新建源文件
void EditorWidget::on_actionNSrcCode()
{
    SourceFileWidget *sourceFile = new SourceFileWidget(this);          // 创建文档窗口对象
    if (sourceFile->maybeSave())
    {
        sourceFile->textEdit->clear();
        sourceFile->setCurrentFile("");
    }
    mdiArea->addSubWindow(sourceFile);                                  // 将文档窗口添加到MDI中
    sourceFile->show();                                                 // 显示MDI窗体
}
// 打开文件
void EditorWidget::on_actionOpen()
{

//    SourceFileWidget *sourceFile;
//    // 新建标识符
//    bool needNew = false;
//    // 检查是否需要新建子窗口，是否需要新建子窗口，若文件已经打开，则不需要重复打开
//    if(mdiArea->subWindowList().count() > 0)
//    {   // 如果 mdiArea 组件中已经有窗口
//        // 获取当前鼠标所选中的窗口对象
//        sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
//        // needNew为false，表示不需要新建子窗口
//        needNew = sourceFile->isFileOpened();
//    } else {
//        // mdiArea组件中还没有窗口，需要新建
//        needNew = true;
//    }
//    if(needNew)
//    {   // 如果需要新建窗口，则新建窗口
//        SourceFileWidget *sourceFile = new SourceFileWidget(this);
//        // 将新建的窗口变为当前的操作窗口
//        mdiArea->addSubWindow(sourceFile);
//    }
    // 打开一个文件

       SourceFileWidget * sourceFile = new SourceFileWidget(this);
        // 将新建的窗口变为当前的操作窗口

    if (sourceFile->maybeSave()) {
        QString curPath = QDir::currentPath();
        QString fileName = QFileDialog::getOpenFileName(this,
             QStringLiteral("打开一个文件"),curPath,
             QStringLiteral("C程序文件(*.h *.c *.cpp);;所有文件(*.*)"));
        //qDebug()<<"curPath:"<<curPath;
       // qDebug()<<"fileName:"<<fileName;

        if(fileName=="") return;  //未选择路经则退出

        globalFilePath = fileName;
        emit sendFilePath(globalFilePath);
        if (!fileName.isEmpty())
        {
            sourceFile->loadFile(fileName);

        //显示当前文件所在文件夹 
        QDir *dir1 = new QDir(fileName);
        dir1->cdUp();
        QString upFilePath = dir1->path();//获取上级名称

        QTreeWidgetItem * rootFile = new QTreeWidgetItem(QStringList()<<upFilePath);//根目录

        mainWindow->managerWin->treeWidget->addTopLevelItem(rootFile);//将根目录加入
        connect(mainWindow->managerWin->treeWidget,&QTreeWidget::itemDoubleClicked,this,&EditorWidget::onSelectedItem);

        rootFile->setCheckState(1,Qt::Checked);//设置复选框状态

        showFile(rootFile,upFilePath);
        mdiArea->addSubWindow(sourceFile);  //加入新窗体
        }
    // 显示窗口
    sourceFile->show();
 //        actCut->setEnabled(true);
 //        actCopy->setEnabled(true);
 //        actPaste->setEnabled(true);
 //        actFont->setEnabled(true);
}
}
// 保存文件
bool EditorWidget::on_actionSave()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    connect(sourceFile,&SourceFileWidget::sendPath,this,&EditorWidget::on_receivePath);
    bool a = sourceFile->save();
    emit sendFilePath(globalFilePath);
    return a;
}
// 文件另存为...
bool EditorWidget::on_actionSavaAS()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    connect(sourceFile,&SourceFileWidget::sendPath,this,&EditorWidget::on_receivePath);
    bool a = sourceFile->saveAs();
    emit sendFilePath(globalFilePath);
    return a;
}
// 关闭当前窗口
void EditorWidget::on_actionClose()
{
    globalFilePath = "";
    mdiArea->closeActiveSubWindow();
}
// 关闭所有窗口
void EditorWidget::on_actionCloseAll()
{
    globalFilePath = "";
    //关闭全部子窗口
    mdiArea->closeAllSubWindows();
}
//展示当前文件下的文件夹
void EditorWidget::showFile(QTreeWidgetItem *rootFile, QString upFilePath)
{
    //第一步，将upFilePath路径下的文件添加
    QDir dir(upFilePath);//
    QDir dirFile(upFilePath);
    dirFile.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//设置过滤器
    dirFile.setSorting(QDir::Name);//按名字排序
    QFileInfoList listFile = dirFile.entryInfoList();//将遍历的文件存入list中
    for(int i = 0; i< listFile.size() ; i++)
    {
        QFileInfo fileInfo = listFile.at(i);
        QString childname = fileInfo.fileName();
        QTreeWidgetItem * child = new QTreeWidgetItem(QStringList()<<childname);//加入子文件
        child->setCheckState(1,Qt::Checked);
        rootFile->addChild(child);
    }

    //第二步，将upFilePath路径下的子文件夹添加。
    QFileInfoList fileList = dir.entryInfoList(QDir::Files | QDir::Hidden | QDir::NoSymLinks);//
    QFileInfoList folderList = dir.entryInfoList(QDir::Dirs | QDir::NoDotAndDotDot); //获取当前所有的目录，不列出特殊条目“.”和 ”..”

    for(int i=0; i <folderList.size();i++)
    {
        QString namepath = folderList.at(i).absoluteFilePath();    //获取路径
        QFileInfo folderInfo= folderList.at(i);
        QString childRootName=folderInfo.fileName();      //获取目录名
        QTreeWidgetItem* childRoot = new QTreeWidgetItem(QStringList()<<childRootName);
        childRoot->setCheckState(1, Qt::Checked);
        rootFile->addChild(childRoot);       //添加当前目录为子项
        showFile(childRoot,namepath);          //进行递归
    }
}
//点击侧边栏切换文件
void EditorWidget::onSelectedItem(QTreeWidgetItem *item, int column)
{
    QString m_sceneName = item->text(column);
    if(m_sceneName.endsWith(".cpp")||m_sceneName.endsWith(".h")||m_sceneName.endsWith(".c")){
        EditorWidget::on_actionSave();
        QStringList filepath;
             while(item!=NULL)
             {
                 filepath<<item->text(0); //获取itemfile名称
                 item=item->parent(); //将itemfile指向父item
             }
             QString strpath;
             for(int i=(filepath.size()-1);i>=0;i--) //QStringlist类filepath反向存着初始item的路径
             { //将filepath反向输出，相应的加入’/‘
                 strpath+=filepath.at(i);
                 if(i!=0)
                     strpath+="/";
             }
        //qDebug()<<strpath;
        globalFilePath = strpath;
        emit sendFilePath(globalFilePath);
        SourceFileWidget *sourceFile;
        sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
        QString fileName = strpath;
        if (!fileName.isEmpty())
                sourceFile->loadFile(fileName);
        // 显示窗口
        sourceFile->show();
     //        actCut->setEnabled(true);
     //        actCopy->setEnabled(true);
     //        actPaste->setEnabled(true);
     //        actFont->setEnabled(true);
    }
    else {
        m_sceneName = "";
    }

}
// 到下一个标签
void EditorWidget::on_2NextTab()
{
    mdiArea->activateNextSubWindow();
}
// 到上一个标签
void EditorWidget::on_2PriorTab()
{
    mdiArea->activatePreviousSubWindow();
}
// 关于
void EditorWidget::on_actionAbout()
{
    QMessageBox::about(this, tr("About Pointer Maker"),
             tr("The <b>Pointer Maker</b> example demonstrates how to "
                "write modern GUI applications using Qt, with a menu bar, "
                "toolbars, and a status bar."));
}
// 全部保存
void EditorWidget::on_actionSaveAll()
{
    QList<QMdiSubWindow*> subWins = mdiArea->subWindowList();
    for (QMdiSubWindow *tmp:subWins)
    {
        SourceFileWidget *sourceFile = (SourceFileWidget*)tmp->widget();
        sourceFile->save();
    }
}

// 剪切
void EditorWidget::on_actionCut()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->cut();
}
// 复制
void EditorWidget::on_actionCopy()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->copy();
}
// 粘贴
void EditorWidget::on_actionPaste()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->paste();
}
// 撤回
void EditorWidget::on_activeUndo()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->undo();
}
// 重做
void EditorWidget::on_activeRedo()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->redo();
}
// 全部选择
void EditorWidget::on_activeSelectAll()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->selectAll();
}

void EditorWidget::on_activeInsertFor()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("for(;;) {}");
}
void EditorWidget::on_activeInsertWhile()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("while() {}");
}
void EditorWidget::on_activeInsertDoWhile()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("do {} while();");
}
void EditorWidget::on_activeInsertIf()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("if() {}");
}
void EditorWidget::on_activeInsertSwitch()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("switch() {default:}");
}
void EditorWidget::on_activeInsertClass()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("class {};");
}
void EditorWidget::on_activeInsertIfdef()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("#ifdef #endif");
}
void EditorWidget::on_activeInsertIfndef()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("#ifndef #endif");
}
void EditorWidget::on_activeInsertIfdefE()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("#ifdef #elif #endif");
}
void EditorWidget::on_activeInsertIfndefE()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->insert("#ifndef #elif #endif");
}
void EditorWidget::on_activeComment(){}
void EditorWidget::on_activeUncomment(){}
void EditorWidget::on_activeIndent(){}
void EditorWidget::on_activeUnindent(){}
void EditorWidget::on_activeFoldAll()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->foldAll();
}
void EditorWidget::on_activeExpandall()
{
    SourceFileWidget *sourceFile = (SourceFileWidget*)mdiArea->activeSubWindow()->widget();
    sourceFile->textEdit->foldAll();
}

void EditorWidget::on_receivePath(QString a)
{
    globalFilePath = a;
   //qDebug()<<"globalFilePath2:"<<globalFilePath;
}

void EditorWidget::on_font_change(const QFont c_font)
{
    SourceFileWidget *sourceFile;
    for (QMdiSubWindow *submdi : mdiArea->subWindowList())
    {
        sourceFile = (SourceFileWidget*)submdi->widget();
        sourceFile->textLexer->setFont(c_font);
    }
}
