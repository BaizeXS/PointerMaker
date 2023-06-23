#include "sourcefilewidget.h"

SourceFileWidget::SourceFileWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化
    mainTabLayout = new QVBoxLayout(this);
    textEdit = new QsciScintilla(this);
    mFileOpened = false;
    setCurrentFile("");
//    textEdit->setColor(QColor("b2def0"));
    // 设置UFT-8
    textEdit->setUtf8(true);
    // 设置词法分析器
    textLexer = new QsciLexerCPP();
    textLexer->setDefaultPaper(QColor("#c0d9d9"));
    textLexer->setColor(QColor("#057200"),QsciLexerCPP::Comment);
    textLexer->setColor(QColor("#057200"),QsciLexerCPP::CommentLine);
    textLexer->setColor(QColor("#057200"),QsciLexerCPP::CommentLineDoc);
    textLexer->setColor(QColor("#00215b"),QsciLexerCPP::Number);
    textLexer->setColor(QColor("#7c0173"),QsciLexerCPP::Keyword);
    textLexer->setColor(QColor(65,105,225),QsciLexerCPP::DoubleQuotedString);
    textLexer->setColor(QColor("#7a0108"),QsciLexerCPP::SingleQuotedString);
    textLexer->setColor(QColor("#00586a"),QsciLexerCPP::PreProcessor);
    textLexer->setColor(QColor("#6f7700"),QsciLexerCPP::Operator);
    textLexer->setColor(QColor("#001e4d"),QsciLexerCPP::Identifier);
    textLexer->setColor(QColor("#86ef28"),QsciLexerCPP::RawString);
    textEdit->setLexer(textLexer);
    // 代码提示与补全
    QsciAPIs *apis;
    apis = new QsciAPIs(textLexer);
    // 添加补全内容
    apis->add(QString("asm"));apis->add(QString("auto"));apis->add(QString("bool"));apis->add(QString("break"));apis->add(QString("case"));apis->add(QString("catch"));apis->add(QString("char"));
    apis->add(QString("class"));apis->add(QString("const"));apis->add(QString("const_cast"));apis->add(QString("continue"));apis->add(QString("default"));apis->add(QString("delete"));apis->add(QString("do"));
    apis->add(QString("double"));apis->add(QString("dynamic_cast"));apis->add(QString("else"));apis->add(QString("enum"));apis->add(QString("explicit"));apis->add(QString("export"));apis->add(QString("extern"));
    apis->add(QString("false"));apis->add(QString("float"));apis->add(QString("for"));apis->add(QString("friend"));apis->add(QString("goto"));apis->add(QString("if"));apis->add(QString("inline"));
    apis->add(QString("int"));apis->add(QString("long"));apis->add(QString("mutable"));apis->add(QString("namespace"));apis->add(QString("new"));apis->add(QString("operator"));apis->add(QString("private"));
    apis->add(QString("protected"));apis->add(QString("public"));apis->add(QString("register"));apis->add(QString("reinterpret_cast"));apis->add(QString("return"));apis->add(QString("signed"));apis->add(QString("sizeof"));apis->add(QString("slots"));
    apis->add(QString("static"));apis->add(QString("static_cast"));apis->add(QString("struct"));apis->add(QString("switch"));apis->add(QString("template"));apis->add(QString("this"));apis->add(QString("throw"));apis->add(QString("true"));
    apis->add(QString("try"));apis->add(QString("typedef"));apis->add(QString("typeid"));apis->add(QString("typename"));apis->add(QString("union"));apis->add(QString("unsigned"));apis->add(QString("using"));apis->add(QString("virtual"));apis->add(QString("void"));
    apis->add(QString("volatile"));apis->add(QString("wchar_t"));apis->add(QString("while"));apis->add(QString("include"));apis->add(QString("printf"));apis->add(QString("main"));apis->add(QString("scanf"));

//    if(apis->load(QString(":/word/Others/CKeyWords")))
//        qDebug()<<"读取成功";
//    else
//        qDebug()<<"读取失败";
    // 加载补全项目
    apis->prepare();
    // 自动补全设置：自动补全的源——所有可用的资源都要自动补全提示，包括当前文档中出现的名称和使用QsciAPIs类加入的名称
    textEdit->setAutoCompletionSource(QsciScintilla::AcsAll);
    // 自动补全设置：自动补全大小写敏感
    textEdit->setAutoCompletionCaseSensitivity(true);
    // 自动补全设置：1个字符开始补全
    textEdit->setAutoCompletionThreshold(1);
    // 设置字体
    QFont font("Consolas", 13, QFont::Normal);
    textEdit->setFont(font);
    textEdit->setMarginsFont(font);
    QFontMetrics fontmetrics = QFontMetrics(font);
    // 设置边栏
    textEdit->setMargins(3);
    textEdit->setMarginsBackgroundColor(QColor("#b2def0"));
    // 设置行号
    textEdit->setMarginType(0, QsciScintilla::NumberMargin);
    textEdit->setMarginWidth(0, fontmetrics.width("0000"));
    textEdit->setMarginLineNumbers(0, true);
    textEdit->setTabWidth(4);
    // 设置断点
    textEdit->setMarginType(1, QsciScintilla::SymbolMargin);
    textEdit->setMarginLineNumbers(1, false);
    textEdit->setMarginWidth(1,20);
    textEdit->setMarginSensitivity(1, true);
    textEdit->setMarginMarkerMask(1, 0x02);
//    connect(textEdit, SIGNAL(marginClicked(int, int, Qt::KeyboardModifiers)),this,
//            SLOT(on_margin_clicked(int, int, Qt::KeyboardModifiers)));
    textEdit->markerDefine(QsciScintilla::Circle, 1);
    textEdit->setMarkerBackgroundColor(QColor("#ee1111"), 1);
    textEdit->SendScintilla(textEdit->SCI_SETMARGINSENSITIVEN,1,true); //设置1号页边可以点击
     connect(textEdit,SIGNAL(marginClicked(int,int,Qt::KeyboardModifiers)),this,SLOT(addMarker(int,int,Qt::KeyboardModifiers)));
    // 设置折叠区域
    textEdit->setMarginType(2, QsciScintilla::SymbolMargin);
    textEdit->setMarginLineNumbers(2, false);
    textEdit->setMarginWidth(2, 15);
    textEdit->setFolding(QsciScintilla::BoxedTreeFoldStyle);
    textEdit->setFoldMarginColors(QColor("#98d3eb"), QColor("#98d3eb"));     //折叠栏颜色
    // 设置当前行显示
    textEdit->setCaretWidth(2);                                 // 光标宽度
    textEdit->setCaretForegroundColor(QColor("#158ab6"));       // 光标颜色
    textEdit->setCaretLineVisible(true);                        // 当前行显示
    textEdit->setCaretLineBackgroundColor(QColor(211,211,211));   // 当前行显示背景色
    // 设置选中区域颜色
    textEdit->setSelectionBackgroundColor(QColor("#a79ce8"));   //选中文本背景色
    textEdit->setSelectionForegroundColor(QColor("#9ce8e5"));   //选中文本前景色
    // 设置文字环绕
    textEdit->setWrapMode(QsciScintilla::WrapNone);
    textEdit->setWrapVisualFlags(QsciScintilla::WrapFlagInMargin);
    textEdit->setWrapIndentMode(QsciScintilla::WrapIndentFixed);
    // 设置缩进
    textEdit->setIndentationsUseTabs(true);
    textEdit->setIndentationGuides(true);
    textEdit->setTabWidth(4);
    textEdit->setAutoIndent(true);
    // 设置括号匹配
    textEdit->setBraceMatching(QsciScintilla::SloppyBraceMatch);
    // 设置布局
    mainTabLayout->addWidget(textEdit);
    mainTabLayout->setMargin(0);
    mainTabLayout->setSpacing(0);
    mainTabLayout->setContentsMargins(0,0,0,0);
    this->setLayout(mainTabLayout);
    // 设置监听槽函数
    connect(textEdit, &QsciScintilla::textChanged, this, &SourceFileWidget::documentWasModified);
    this->setAttribute(Qt::WA_DeleteOnClose);
}

// 关闭事件
void SourceFileWidget::closeEvent(QCloseEvent *event)
{
    if (maybeSave()) {
        writeSettings();
        event->accept();
    } else {
        event->ignore();
    }
}
// 读取设置
void SourceFileWidget::readSettings()
{
    QSettings settings("摸鱼不会被抓组", "Pointer Maker");
    QPoint pos = settings.value("pos", QPoint(200, 200)).toPoint();
    QSize size = settings.value("size", QSize(400, 400)).toSize();
    resize(size);
    move(pos);
}
// 写入设置
void SourceFileWidget::writeSettings()
{
    QSettings settings("摸鱼不会被抓组", "Pointer Maker");
    settings.setValue("pos", pos());
    settings.setValue("size", size());
}
// 获取当前文件名
QString SourceFileWidget::currentFileName()
{
    return mCurrentFile;
}
// 查看文件是否打开
bool SourceFileWidget::isFileOpened()
{
    return mFileOpened;
}
// 是否存储
bool SourceFileWidget::maybeSave()
{
    if (textEdit->isModified()) {
        int ret = QMessageBox::warning(this, tr("Pointer Maker"),
                     tr("当前文件已被修改.\n"
                        "您是否想要保存这些修改?"),
                     QMessageBox::Yes | QMessageBox::Default,
                     QMessageBox::No,
                     QMessageBox::Cancel | QMessageBox::Escape);
        if (ret == QMessageBox::Yes)
            return save();
        else if (ret == QMessageBox::Cancel)
            return false;
    }
    return true;
}
// 打开并读取文件
void SourceFileWidget::loadFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly)) {
        QMessageBox::warning(this, tr("Pointer Maker"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return;
    }
    // 读取文件并将内容放入textEdit
    QTextStream in(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    textEdit->clear();
    textEdit->setText(in.readAll());
    QApplication::restoreOverrideCursor();
    file.close();
    // 根据文件名获取文件信息，将文件名设置MDI窗体的标题
    QString showName;
    showName = setCurrentFile(fileName);
    this->setWindowTitle(showName);
    mFileOpened=true;
//    // 状态栏更新信息
//    statusBar()->showMessage(tr("File loaded"), 2000);
}
// 保存文件
bool SourceFileWidget::saveFile(const QString &fileName)
{
    QFile file(fileName);
    if (!file.open(QFile::WriteOnly)) {
        QMessageBox::warning(this, tr("Pointer Maker"),
                             tr("Cannot read file %1:\n%2.")
                             .arg(fileName)
                             .arg(file.errorString()));
        return false;
    }
    QDir *dir = new QDir(fileName);
    QString filePath = dir->absoluteFilePath(fileName);
    emit sendPath(filePath);
    //qDebug()<<"filePath"<<filePath;

    QTextStream out(&file);
    QApplication::setOverrideCursor(Qt::WaitCursor);
    out << textEdit->text();
    QApplication::restoreOverrideCursor();
    setCurrentFile(fileName);
    QString showName;
    showName = setCurrentFile(fileName);
    this->setWindowTitle(showName);
    //    // 状态栏更新信息
    //    statusBar()->showMessage(tr("File saved"), 2000);
    return true;
}
// 设置当前文件
QString SourceFileWidget::setCurrentFile(const QString &fileName)
{
    mCurrentFile = fileName;
    textEdit->setModified(false);
    setWindowModified(false);
    // 设置MDI窗体的标题
    QString shownName;
    if (mCurrentFile.isEmpty())
        shownName = "untitled";
    else
        shownName = strippedName(mCurrentFile);
//    // 显示标题
//    setWindowTitle(tr("%1[*] - %2").arg(shownName).arg(tr("Pointer Maker")));
    return shownName;
}
// 获取文件名
QString SourceFileWidget::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}
// 文件已修改槽函数
void SourceFileWidget::documentWasModified()
{
    this->setWindowModified(textEdit->isModified());
}
// 保存
bool SourceFileWidget::save()
{
    if (mCurrentFile.isEmpty()) {
        return saveAs();
    } else {
        return saveFile(mCurrentFile);
    }
}
// 另存为
bool SourceFileWidget::saveAs()
{
    QString fileName = QFileDialog::getSaveFileName(this);
    if (fileName.isEmpty())
        return false;
    return saveFile(fileName);
}


void SourceFileWidget::addMarker(int m, int n, Qt::KeyboardModifiers)
{
    //m为被点击的页边的编号（列），n为行
    int maskn=textEdit->SendScintilla(QsciScintilla::SCI_MARKERGET,n);
    //返回添加或消除断点的行数
    //qDebug()<<n<<endl;
    if(maskn == 0)
    {
        textEdit->SendScintilla(QsciScintilla::SCI_MARKERADD,n,m);
        QString str = "break "+QString::number(n+1)+"\r\n";
        //qDebug()<<str;
        //cmd->write(str.toStdString().c_str());
    }
    else
    {
        textEdit->SendScintilla(QsciScintilla::SCI_MARKERDELETE,n,m);
    }
}

