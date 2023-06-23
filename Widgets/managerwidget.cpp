#include "managerwidget.h"

ManagerWidget::ManagerWidget(QWidget *parent) : QWidget(parent)
{
    mainLayout = new QVBoxLayout(this);
    ProjMan = new QTabWidget(this);
    treeWidget = new QTreeWidget();
    treeWidget->setHeaderLabel("文件管理");//设置名称
    treeWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);
    mainLayout->addWidget(treeWidget);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    this->setLayout(mainLayout);
}
