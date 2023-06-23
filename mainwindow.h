#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLayout>
#include <QComboBox>
#include <QTextCodec>
#include <QString>
#include <QFile>
#include <QFileDialog>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QFontComboBox>
#include <QSizePolicy>
#include "mainwidget.h"
#include "cmdpart.h"
extern MainWidget *mainWindow;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    // Toolbar Extra Components

    QWidget *fWidget;
    QHBoxLayout *fontlyt;
    QLabel *font;
    QFontComboBox *fonts;

    // Main Widget
    //MainWidget *mainWindow;
    // File Operation
    QString filePath;
    QString newPath;
    // Compile Part
    CmdPart *commandPart;

    //查找替换部分
    int flagSearch=0;
    SearchWidget * searchWidget;

    SourceFileWidget * sf;

    QLineEdit * gotoLineEdit;

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

signals:
    // Compile Part
    void mainwindowRun();
    void mainwindowCompile();
    void mainWindowCplandRun();

public slots:
    // File Operation
    void on_actionExit_triggered();
    void on_receiveFilePath(QString a);
    // Compile Part
    void on_actionCompile_triggered();
    void on_actionRun_triggered();
    void on_actionCompRun_triggered();

    //查找替换部分
    int initSearch();
    void focus();
    void updateEditor();

private slots:
    void on_actionSearch_triggered();

    void on_action_gotoLine_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
