#ifndef CMDPART_H
#define CMDPART_H

#include <QObject>
#include <QWidget>
#include <QtGui>
#include <QMessageBox>
#include <QLineEdit>
#include <QPushButton>
#include <QDebug>
#include <QTextEdit>
#include <QBoxLayout>
#include <QMainWindow>
#include <QTextCodec>
class CmdPart : public QWidget
{
    Q_OBJECT
public:
    explicit CmdPart(QWidget *parent = nullptr);
    //控件变量
    QWidget *myWidget;
    QPushButton *complitionBtn;
    QTextEdit *complitionInfor;
    QPushButton *CompilationBtn;
    QPushButton *runBtn;
    QHBoxLayout *btnLayout;
    QVBoxLayout *allLayout;

    //cmd进程相关变量
    QProcess *p;
    QString path;
    QString fileName;
    QString CmdString;
    QString Compilation;
    QStringList Arguments;
    QLineEdit *myLineEdit;
    QByteArray bytes_error;
    QTextEdit *textEditError;
    QTextCodec *filecodec;

    //文件类
    QString strFn;
    QString strFIleName;//文件纯名字
    QString cmdFilepath; //传入文件路径
    QString fileExeName; //文件除.exe后路径
    int returnInt; //编译后返回值

    int cmdState=0;
    //func
//    void WindowDesign(QWidget *parent);
    void StartCmd();
    void setPath(QString filePath2cmd);

signals:
    void doCompilation();
    void boxShow();
public slots:
    void read_data();
    void onRunBtnClicked();
    void onComplitionBtnClicked();
    void onMainWindowCompile();
    void onMainWindowRun();
    void onMainWindowCompileandRun();
};

#endif // CMDPART_H
