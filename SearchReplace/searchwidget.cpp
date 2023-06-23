#include "searchwidget.h"
#include <QMainWindow>
#include <qdebug.h>

SearchWidget::SearchWidget(QWidget *parent) : QWidget(parent)
{
    ui=new Ui::Form();
    ui->setupUi(this);
}

void SearchWidget:: setCursor(int posCursor,int posAnchor){
    editor->SendScintilla(QsciScintilla::SCI_SETCURRENTPOS,posCursor);
    editor->SendScintilla(QsciScintilla::SCI_SETANCHOR,posAnchor);
}

void SearchWidget::scroll(){
    editor->SendScintilla(QsciScintilla::SCI_SCROLLCARET);
}


void SearchWidget::setCursor(int pos){
    setCursor(pos,pos);
}

int SearchWidget::searchNext(char *str,int l){
         int s;
         editor->SendScintilla(QsciScintilla::SCI_SETSEARCHFLAGS,QsciScintilla::SCFIND_MATCHCASE);
         s= editor->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS);
         editor->SendScintilla(QsciScintilla::SCI_SETTARGETSTART,s);
         s= editor->SendScintilla(QsciScintilla::SCI_GETLENGTH);
         editor->SendScintilla(QsciScintilla::SCI_SETTARGETEND,s);
         s=  editor-> SendScintilla(QsciScintilla::SCI_SEARCHINTARGET,l,str);
         return s;
}


void SearchWidget::on_pushButton_clicked()  //查找下一个
{
    emit updateEditor();
//获取查找字段
    QString pattern = ui->textEdit->document()->toPlainText();
    int length = pattern.length();
    sLength=length;
    if(length==0){
        message("查找字段不可为空！");
        return ;
    }

//Qstring转char*
    QByteArray ba;
    ba.append(pattern);
    char *str= ba.data();


    int isFound= searchNext(str,length); //查找

//选中
     if(isFound!=-1)  {
         setCursor(isFound+length,isFound);
         scroll();
     }
     else   setCursor(0,0);
     emit onFocus(); //编辑器聚焦

//查找信息反馈
    if(isFound==-1) message("Not Found!");

    else this->raise();  //聚焦
}



void SearchWidget::on_pushButton_2_clicked()
{   emit updateEditor();
    result.clear();
    QString pattern = ui->textEdit->document()->toPlainText();
    int length = pattern.length();
    sLength=length;

    QByteArray ba;
    ba.append(pattern);
    char *str= ba.data();

    int isFound;
    if(length==0){
        message("查找字段不可为空！");
        return;
    }

    setCursor(0,0);
    scroll();  //光标复位

    while(1){
        isFound= searchNext(str,length);
        result.append(isFound);
        if(isFound==-1) break;
        setCursor(isFound+length);

    }

    findAll();


}


//停止恢复
void SearchWidget::on_pushButton_5_clicked()
{       emit tableClose();
        this->close();
}


//替换
void SearchWidget::on_pushButton_3_clicked()
{   emit updateEditor();
    QString toReplace = ui->textEdit_2->toPlainText();
    rLength=toReplace.length();
    int start=editor->SendScintilla(QsciScintilla::SCI_GETSELECTIONNSTART);
    int end=editor->SendScintilla(QsciScintilla::SCI_GETSELECTIONNEND);
    emit onFocus();
    this->raise();
    if(start==end) return;

    int pos= editor->SendScintilla(QsciScintilla::SCI_GETCURRENTPOS);
    editor->replaceSelectedText(toReplace);
    adjustPos(pos);

}





void SearchWidget:: adjustPos(int pos){
   if (result.empty()) return;
    for(int i=0; i<result.length();i++){
        if(result[i]>pos){
            result[i]+=rLength-sLength;
        }
    }
 }



void SearchWidget::selectFound(int row,int col){
    setCursor(result[row]+sLength,result[row]);
    scroll();
    emit onFocus();
}


//表格填充
void SearchWidget::findAll(){
    connect(resultTable,&QTableWidget::cellDoubleClicked,this,&SearchWidget::selectFound);

    resultTable->setRowCount(0);
    for(int i=0;i<result.size()-1;i++){

        setCursor(result[i]);
        resultTable->setRowCount(resultTable->rowCount()+1);
        char str[500];      //预留行上限500字符

     //获取光标位置
        int line,index;
        editor->getCursorPosition(&line,&index);

     // 表格填充
        QTableWidgetItem * qw=new QTableWidgetItem();
        QString s;
        s = QString::number(line+1);
        qw=new QTableWidgetItem(s);
        resultTable->setItem(resultTable->rowCount()-1,0,qw);

        s = QString::number(index+1);
        qw=new QTableWidgetItem(s);
        resultTable->setItem(resultTable->rowCount()-1,1,qw);

        editor->SendScintilla(QsciScintilla::SCI_GETLINE,line,str);
        int length=editor->SendScintilla(QsciScintilla::SCI_LINELENGTH,line);

        if(str[length-1]=='\n')   str[length-1]='\0';
        qw=new QTableWidgetItem(str);

        resultTable->setItem(resultTable->rowCount()-1,2,qw);

       }
    emit tableShow();
}

int SearchWidget::replaceAll(){
    int i;
    for(i=1;i<result.length();i++){
        selectFound(result.length()-i-1,0);
        on_pushButton_3_clicked();
    }
    return i-1;
}


//全部替换
void SearchWidget::on_pushButton_4_clicked()
{   emit updateEditor();
    on_pushButton_2_clicked();
    int count= replaceAll();

    message("Replace  "+QString::number(count)+ "  records");

 }

//messageBox 封装
void SearchWidget::message(QString s){
    QMessageBox * msg =new QMessageBox();
    msg->setText(s);
    msg->show();
    this->raise();
    msg->raise();
    connect(msg,&QMessageBox::buttonClicked,this,[=](){
        this->raise();
    });
}

//跳转
void SearchWidget::on_pushButton_6_clicked()
{   emit updateEditor();
    QString s= ui->textEdit_3->document()->toPlainText();
    int i= s.toInt();
    int count = editor->SendScintilla(QsciScintilla::SCI_GETLINECOUNT);
    if(i>0&&i<=count) {
        editor->SendScintilla(QsciScintilla::SCI_GOTOLINE,i-1);
         emit onFocus();
        this->raise();
    }
    else message("不存在该行");
}
