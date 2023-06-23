#ifndef EDITORWIDGET_H
#define EDITORWIDGET_H

#include <QWidget>
#include <QMdiArea>
#include <QMdiSubWindow>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QList>
#include "sourcefilewidget.h"
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>


class EditorWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *mainLayout;
    QMdiArea *mdiArea;

public:
    explicit EditorWidget(QWidget *parent = nullptr);
    void on_actionNSrcCode();   // 新建源文件
    void on_actionOpen();       // 打开文件
    bool on_actionSave();       // 保存文件
    bool on_actionSavaAS();     // 文件另存为
    void on_actionSaveAll();    // 全部保存
    void on_actionClose();      // 关闭当前文件
    void on_actionCloseAll();   // 关闭所有文件
    void showFile(QTreeWidgetItem *a,QString b);//显示当前文件所在文件夹下的所有文件
    void onSelectedItem(QTreeWidgetItem *item, int column);//点击切换文件
    void on_2NextTab();         // 到下一个标签
    void on_2PriorTab();        // 到上一个标签
    void on_actionAbout();      // 关于
    void on_actionCut();        // 剪切
    void on_actionCopy();       // 复制
    void on_actionPaste();      // 粘贴
    void on_activeUndo();       //撤销
    void on_activeRedo();       //重做
    void on_activeSelectAll();  //全选
    void on_activeInsertFor();  //插入FOR
    void on_activeInsertWhile();//插入While
    void on_activeInsertDoWhile();//插入DoWhile
    void on_activeInsertIf();   //插入If
    void on_activeInsertSwitch();//插入Switch
    void on_activeInsertClass();//插入Class
    void on_activeInsertIfdef();//插入Ifdef
    void on_activeInsertIfndef();//插入Ifndef
    void on_activeInsertIfdefE();//插入IfdefE
    void on_activeInsertIfndefE();//插入IfndefE
    void on_activeComment();
    void on_activeUncomment();
    void on_activeIndent();
    void on_activeUnindent();
    void on_activeFoldAll();
    void on_activeExpandall();
    void on_font_change(const QFont c_font);
public slots:
    void on_receivePath(QString a);
signals:
    void sendFilePath(QString a);
};

#endif // EDITORWIDGET_H
