#include "cmdpart.h"

CmdPart::CmdPart(QWidget *parent) : QWidget(parent)
{
    //窗口设计部分
//    myWidget = new QWidget(parent);

    complitionInfor = new QTextEdit(parent);

//    complitionInfor->resize(1000,300);
//    myWidget->resize(1000)
//    parent->setCentralWidget(myWidget);
//    runBtn = new QPushButton(myWidget);
//    complitionBtn = new QPushButton(myWidget);
//    runBtn->setText("run");
//    complitionBtn->setText("complition");
//    btnLayout = new QHBoxLayout();
//    allLayout = new QVBoxLayout();

//    btnLayout->addWidget(runBtn);
//    btnLayout->addWidget(complitionBtn);
//    allLayout->addWidget(complitionInfor);
//    allLayout->addLayout(btnLayout);

//    myWidget->setLayout(allLayout);
//    parent->setCentralWidget(myWidget);

    filecodec = QTextCodec::codecForName("GBK");
    //运行cmd进程进行编译部分
    p = new QProcess();
    p->start("cmd.exe");
    fileName = "helloWorld.cpp"; //

//    Arguments << "/c" <<
//    p->setArguments("")
//    p->start("cmd.exe",QStringList()<< "/c" << "ping baidu.com");

    connect(p,SIGNAL(readyRead()),this,SLOT(read_data()));
//    connect(runBtn,SIGNAL(clicked(bool)),this,SLOT(onRunBtnClicked()));
//    connect(complitionBtn,SIGNAL(clicked(bool)),this,SLOT(onComplitionBtnClicked()));


}

//void CmdPart::WindowDesign(QWidget *parent){
//    myWidget = new QWidget(parent);
//    complitionInfor = new QTextEdit(myWidget);
//    myWidget->resize(1000,300);
//    complitionInfor->resize(1000,300);
//    myWidget->show();
//}
void CmdPart::onRunBtnClicked(){
    if((int)bytes_error[0]==0){
        QString systemString = QString("cmd /k %1.exe").arg(fileExeName);
        qDebug()<<systemString;
        QByteArray systemCmdBytes = systemString.toLatin1();
        system(filecodec->fromUnicode(systemString).data());
    }
}

void CmdPart::onComplitionBtnClicked(){
    complitionInfor->clear();
    qDebug()<<cmdFilepath<<"filepath";
    QStringList fileNameList = cmdFilepath.split(".");
    fileExeName.clear();
    for(int i=0;i<fileNameList.length()-1;i++){
        fileExeName += fileNameList[i];
    }
    qDebug()<<fileExeName<<"fileExeName";
    CmdString =QString("cmd/c g++ -o %1.exe " + cmdFilepath).arg(fileExeName);
    qDebug()<<CmdString;
    StartCmd();
}

void CmdPart::StartCmd(){

    CmdString += "\r\n";
    qDebug()<<CmdString<<"cmdstring";
    QByteArray qbyteCmd = CmdString.toLatin1();
    char* charCmd = qbyteCmd.data();
    int len = CmdString.length();
    p->write(filecodec->fromUnicode(CmdString).data(),len);
    QByteArray qbyteCompile = CmdString.toLatin1();
    char * compileCmd = qbyteCompile.data();
    returnInt = system(filecodec->fromUnicode(CmdString).data());
    qDebug()<<returnInt<<"return int";
    if(returnInt!=0){
        complitionInfor->append("failed");
    }else{
        complitionInfor->append("compile successfully");
        complitionInfor->append("path:"+fileExeName+".exe");
    }
    complitionInfor->update();
}

void CmdPart::read_data()
{
    cmdState=0;
    /* 接收数据 */
//    textEditError->clear();
//    textEdit->clear();
    bytes_error.clear();
    QByteArray bytes = p->readAll();
    bytes_error = p->readAllStandardError();
    if(bytes_error[0]){
        QString errorString = bytes_error;
        QStringList errorLine = errorString.split("\r\n");
        cmdState=1;

        complitionInfor->append("complite failed");

        foreach(QString errorMsg ,errorLine){
            complitionInfor->append(errorMsg);
        }

        errorString = errorLine[1];
//        int cppPostion = errorString.indexOf(".cpp");
//        qDebug()<<cppPostion;
//        errorString.mid(10,5);
//        qDebug()<<errorString;
        QStringList errorLineInt = errorString.split(":");
        //出现错误的行数

        qDebug()<<errorString<<"errorString"<<errorLineInt[1]<<errorLineInt[2];
    }
    qDebug()<<bytes<<"qbytes";
    qDebug()<<bytes_error<<"qbytes";
    /* 显示 */

    QString msg = QString::fromLocal8Bit(bytes);
    QString msg_1 = QString::fromLocal8Bit(bytes_error);
//    complitionInfor->append(msg);
//    if(bytes_error[0]){
//        complitionInfor->append("complite failed");
//    }
//    complitionInfor->append(msg_1);
//    qDebug()<<textEditError<<"error";
//    complitionInfor->update();
//    /* 信息输出 */
    qDebug() << "Success:read_data:" << msg << endl;
}

void CmdPart::onMainWindowRun(){
    qDebug()<<"onMainWindowRun";
    emit onRunBtnClicked();
}

void CmdPart::onMainWindowCompile(){
    emit onComplitionBtnClicked();
    qDebug()<<"onMainWindowCompile";
}

void CmdPart::onMainWindowCompileandRun(){
    qDebug()<<"onMainWindowCompileandRun";

    emit onComplitionBtnClicked();
    if(returnInt==0)
        emit onRunBtnClicked();

}

void CmdPart::setPath(QString filePath2Cmd){
    cmdFilepath = filePath2Cmd;
    QFileInfo fileInfo(cmdFilepath);
    strFn = fileInfo.fileName();
    fileName=strFn;//新的名字
}
