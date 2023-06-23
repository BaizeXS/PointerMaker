#ifndef SEARCHWIDGET_H
#define SEARCHWIDGET_H

#include <QWidget>
#include <ui_search.h>
#include <qstring.h>
#include <qlist.h>
#include <editorwidget.h>
#include <qmessagebox.h>
#include <bottomwidget.h>
#include "sourcefilewidget.h"
#include <qdialog.h>
namespace Ui {
class SearchWidget;
}

class SearchWidget : public QWidget
{
    Q_OBJECT

public:
    QsciScintilla * editor;
    QTableWidget * resultTable;
    QList <int> result; //结果
    int sLength,rLength;

    explicit SearchWidget(QWidget *parent = nullptr);

    void search( );

    int searchNext(char * str,int l);



    void found(int position,int length); //选中

    void findAll();  //找到全部

    int replaceAll();      //全部替换

    void adjustPos(int pos); //替换后调整链接

    void message(QString s);

    void scroll();

signals:
    void onFocus();   //编辑器聚焦

    void tableShow(); //查找结果显示

    void tableClose(); //关闭

    void updateEditor();






public slots:
   void selectFound(int row,int col);

   void setCursor(int posCursor,int posAnchor);

   void setCursor(int pos);

private slots:

   void on_pushButton_clicked(); //查找按钮

   virtual void on_pushButton_2_clicked();   //替换按钮

   void on_pushButton_5_clicked();

   void on_pushButton_3_clicked();


   void on_pushButton_4_clicked();

   void on_pushButton_6_clicked();

private:
    Ui::Form * ui;
};

#endif // SEARCHWIDGET_H
