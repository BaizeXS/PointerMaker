#ifndef SOURCEFILEWIDGET_H
#define SOURCEFILEWIDGET_H

#include <QApplication>
#include <QWidget>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QString>
#include <QFile>
#include <QFileInfo>
#include <QFileDialog>
#include <QTextStream>
#include <QSettings>
#include <QCloseEvent>
#include <QSize>
#include <QPoint>
#include <QDebug>
#include "Qsci/qsciscintilla.h"
#include "Qsci/qscilexercpp.h"
#include "Qsci/qsciapis.h"

class SourceFileWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *mainTabLayout;
    QsciScintilla *textEdit;
    bool mFileOpened;
    QString mCurrentFile;

public:
    explicit SourceFileWidget(QWidget *parent = nullptr);

public:
    QString currentFileName();                              // 获取当前文件名
    bool isFileOpened();                                    // 查看文件是否打开
    void readSettings();                                    // 读取设置
    void writeSettings();                                   // 写入设置
    bool maybeSave();                                       // 修改询问
    void loadFile(const QString &fileName);                 // 加载文件
    bool saveFile(const QString &fileName);                 // 存入文件
    QString setCurrentFile(const QString &fileName);        // 设置当前文件
    QString strippedName(const QString &fullFileName);      // 提取文件名
    bool save();
    bool saveAs();

protected:
    void closeEvent(QCloseEvent *event);

public slots:
    void documentWasModified();                             // 文件已被修改
};

#endif // SOURCEFILEWIDGET_H
