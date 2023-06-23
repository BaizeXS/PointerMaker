#include "mainwidget.h"

MainWidget::MainWidget(QWidget *parent) : QWidget(parent)
{
    // 初始化变量
    mainLayout = new QVBoxLayout();
    hSplitter = new QSplitter(Qt::Horizontal);
    vSplitter = new QSplitter(Qt::Vertical);
    managerWin = new ManagerWidget();
    editorWin = new EditorWidget();
    bottomWin = new BottomWidget();
    // 设置布局
    hSplitter->addWidget(managerWin);
    hSplitter->addWidget(editorWin);
    hSplitter->setHandleWidth(0);
    hSplitter->setChildrenCollapsible(false);
    hSplitter->setStretchFactor(0,1);
    hSplitter->setStretchFactor(1,8);
    hSplitter->setContentsMargins(0,0,0,0);
    vSplitter->addWidget(hSplitter);
    vSplitter->addWidget(bottomWin);
    vSplitter->setHandleWidth(0);
    vSplitter->setChildrenCollapsible(false);
    vSplitter->setStretchFactor(0,9);
    vSplitter->setStretchFactor(1,1);
    vSplitter->handle(1)->setDisabled(true);
    // 组件设置
    bottomWin->setSizePolicy(QSizePolicy::Minimum,QSizePolicy::MinimumExpanding);
    // 总体布局
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->addWidget(vSplitter);

//    // 记录初始布局
//    originSettings.setValue("OriginalState", vSplitter->saveState());
//    // 恢复初始布局
//    connect(bottomWin->closeTab, &QPushButton::clicked, this, [=](){
//        vSplitter->restoreState(originSettings.value("OriginalState").toByteArray());
//        vSplitter->moveSplitter(4000,1);
//    });
    this->setLayout(mainLayout);
}
