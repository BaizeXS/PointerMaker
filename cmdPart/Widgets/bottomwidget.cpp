#include "bottomwidget.h"

BottomWidget::BottomWidget(QWidget *parent) : QWidget(parent)
{
    // Main Layout
    mainLayout = new QVBoxLayout();
    // Button Init
    btnLayout = new QHBoxLayout();
    compileTab = new QPushButton("编译器");
    resourcesTab = new QPushButton("资源");
    compLogTab = new QPushButton("编译日志");
    debugTab = new QPushButton("调试");
    searchResTab = new QPushButton("搜索结果");
    closeTab = new QPushButton("关闭");
    // Button Settings
    compileTab->setIcon(QIcon(":/Newlook/Newlook/compile.bmp"));
    resourcesTab->setIcon(QIcon(":/Newlook/Newlook/resrc.bmp"));
    compLogTab->setIcon(QIcon(":/Newlook/Newlook/compres.bmp"));
    debugTab->setIcon(QIcon(":/Newlook/Newlook/debug.bmp"));
    searchResTab->setIcon(QIcon(":/Newlook/Newlook/search.bmp"));
    closeTab->setIcon(QIcon(":/Newlook/Newlook/closefl.bmp"));
    closeTab->setVisible(false);
    // Button Layout
    btnLayout->addWidget(compileTab);
    btnLayout->addWidget(resourcesTab);
    btnLayout->addWidget(compLogTab);
    btnLayout->addWidget(debugTab);
    btnLayout->addWidget(searchResTab);
    btnLayout->addWidget(closeTab);
    btnLayout->setAlignment(Qt::AlignLeft | Qt::AlignTop);
    btnLayout->setMargin(0);
    btnLayout->setSpacing(0);
    btnLayout->setContentsMargins(0, 0, 0, 0);
    // Tab Init
    tabLayout = new QHBoxLayout();
    compileTabWin = new QTableWidget();
    resourcesTabWin = new QTableWidget();
    compLogTabWin = new QWidget();
    debugTabWin = new QWidget();
    searchResTabWin = new QTableWidget();
    // Tab Settings
    compileTabWin->setVisible(false);
    compLogTabWin->setVisible(false);
    debugTabWin->setVisible(false);
    resourcesTabWin->setVisible(false);
    searchResTabWin->setVisible(false);
    // Compile Tab Settings
    compileTabWin->setColumnCount(4);
    compileTabWin->setRowCount(6);
    compileTabWin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    compileTabWin->setSelectionBehavior(QAbstractItemView::SelectRows);
    compileTabWin->setHorizontalHeaderLabels(QStringList() << "行" << "列" << "单元" << "信息");
    compileTabWin->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    compileTabWin->verticalHeader()->setDefaultSectionSize(20);
    compileTabWin->verticalHeader()->setVisible(false);
    compileTabWin->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    compileTabWin->horizontalHeader()->setStretchLastSection(true);
    compileTabWin->setColumnWidth(0,45);
    compileTabWin->setColumnWidth(1,45);
    compileTabWin->setColumnWidth(2,320);
    // Resources Tab Settings
    resourcesTabWin->setColumnCount(4);
    resourcesTabWin->setRowCount(6);
    resourcesTabWin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    resourcesTabWin->setSelectionBehavior(QAbstractItemView::SelectRows);
    resourcesTabWin->setHorizontalHeaderLabels(QStringList() << "行" << "列" << "单元" << "信息");
    resourcesTabWin->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    resourcesTabWin->verticalHeader()->setDefaultSectionSize(20);
    resourcesTabWin->verticalHeader()->setVisible(false);
    resourcesTabWin->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    resourcesTabWin->horizontalHeader()->setStretchLastSection(true);
    resourcesTabWin->setColumnWidth(0,45);
    resourcesTabWin->setColumnWidth(1,45);
    resourcesTabWin->setColumnWidth(2,320);
    // Search Results Settings
    searchResTabWin->setColumnCount(4);
    searchResTabWin->setRowCount(6);
    searchResTabWin->setEditTriggers(QAbstractItemView::NoEditTriggers);
    searchResTabWin->setSelectionBehavior(QAbstractItemView::SelectRows);
    searchResTabWin->setHorizontalHeaderLabels(QStringList() << "行" << "列" << "单元" << "信息");
    searchResTabWin->verticalHeader()->setSectionResizeMode(QHeaderView::ResizeToContents);
    searchResTabWin->verticalHeader()->setDefaultSectionSize(20);
    searchResTabWin->horizontalHeader()->setSectionResizeMode(QHeaderView::Interactive);
    searchResTabWin->horizontalHeader()->setStretchLastSection(true);
    searchResTabWin->setColumnWidth(0,45);
    searchResTabWin->setColumnWidth(1,45);
    searchResTabWin->setColumnWidth(2,320);

    // Tab Layout
    tabLayout->addWidget(compileTabWin);
    tabLayout->addWidget(resourcesTabWin);
    tabLayout->addWidget(compLogTabWin);
    tabLayout->addWidget(debugTabWin);
    tabLayout->addWidget(searchResTabWin);
    // Main Layout And Settings
    mainLayout->addLayout(btnLayout);
    mainLayout->addLayout(tabLayout);
    mainLayout->setMargin(0);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    // Connections
    connect(compileTab, &QPushButton::clicked, this, &BottomWidget::on_btnCompile_clicked);
    connect(resourcesTab, &QPushButton::clicked, this, &BottomWidget::on_btnResources_clicked);
    connect(compLogTab, &QPushButton::clicked, this, &BottomWidget::on_btnCompLog_clicked);
    connect(debugTab, &QPushButton::clicked, this, &BottomWidget::on_btnDebug_clicked);
    connect(searchResTab, &QPushButton::clicked, this, &BottomWidget::on_btnSearchRes_clicked);
    connect(closeTab, &QPushButton::clicked, this, &BottomWidget::on_btnClose_clicked);
    // Main Widget Settings
    this->setMaximumHeight(200);
    this->setLayout(mainLayout);


//************************************查找替换框初始化************************

     searchResTabWin->setColumnCount(1);
     searchResTabWin->setColumnWidth(0,this->width());
     QStringList header;
     header<<"查找结果";
     searchResTabWin->setHorizontalHeaderLabels(header);
     searchResTabWin->horizontalHeader()->setFixedHeight(30);
     searchResTabWin->setEditTriggers(QAbstractItemView::NoEditTriggers);
     searchResTabWin->setRowCount(1);

//*********************************END*****************************************
}

// Compile Tab
void BottomWidget::on_btnCompile_clicked()
{   // 设置可见性
    closeTab->setVisible(true);
    compileTabWin->setVisible(true);
    resourcesTabWin->setVisible(false);
    compLogTabWin->setVisible(false);
    debugTabWin->setVisible(false);
    searchResTabWin->setVisible(false);
    // 其他功能
    // ...
}
// Resources Tab
void BottomWidget::on_btnResources_clicked()
{   // 设置可见性
    closeTab->setVisible(true);
    compileTabWin->setVisible(false);
    resourcesTabWin->setVisible(true);
    compLogTabWin->setVisible(false);
    debugTabWin->setVisible(false);
    searchResTabWin->setVisible(false);
    // 其他功能
    // ...
}
// CompileAndLog Tab
void BottomWidget::on_btnCompLog_clicked()
{   // 设置可见性
    closeTab->setVisible(true);
    compileTabWin->setVisible(false);
    resourcesTabWin->setVisible(false);
    compLogTabWin->setVisible(true);
    debugTabWin->setVisible(false);
    searchResTabWin->setVisible(false);
    // 其他功能
    // ...
}
// Debug Tab
void BottomWidget::on_btnDebug_clicked()
{   // 设置可见性
    closeTab->setVisible(true);
    compileTabWin->setVisible(false);
    resourcesTabWin->setVisible(false);
    compLogTabWin->setVisible(false);
    debugTabWin->setVisible(true);
    searchResTabWin->setVisible(false);
    // 其他功能
    // ...
}
// Search Result Tab
void BottomWidget::on_btnSearchRes_clicked()
{   // 设置可见性
    closeTab->setVisible(true);
    compileTabWin->setVisible(false);
    resourcesTabWin->setVisible(false);
    compLogTabWin->setVisible(false);
    debugTabWin->setVisible(false);
    searchResTabWin->setVisible(true);
    // 其他功能
    // ...
}
// Close Tab
void BottomWidget::on_btnClose_clicked()
{   // 设置可见性
    closeTab->setVisible(false);
    compileTabWin->setVisible(false);
    resourcesTabWin->setVisible(false);
    compLogTabWin->setVisible(false);
    debugTabWin->setVisible(false);
    searchResTabWin->setVisible(false);
    // 其他功能
    // 清除缓存等...
}
