#ifndef BOTTOMWIDGET_H
#define BOTTOMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QTableView>
#include <QHeaderView>
#include <QIcon>
#include<QHeaderView>

class BottomWidget : public QWidget
{
    Q_OBJECT
public:
    // Main Layout
    QVBoxLayout *mainLayout;
    // Button Domain
    QHBoxLayout *btnLayout;
    QPushButton *compileTab;
    QPushButton *resourcesTab;
    QPushButton *compLogTab;
    QPushButton *debugTab;
    QPushButton *searchResTab;
    QPushButton *closeTab;
    // Tab Domain
    QHBoxLayout *tabLayout;
    QTableWidget *compileTabWin;
    QTableWidget *resourcesTabWin;
    QWidget *compLogTabWin;
    QWidget *debugTabWin;
    QTableWidget *searchResTabWin;

public:
    explicit BottomWidget(QWidget *parent = nullptr);

signals:

public slots:
    void on_btnCompile_clicked();
    void on_btnResources_clicked();
    void on_btnCompLog_clicked();
    void on_btnDebug_clicked();
    void on_btnSearchRes_clicked();
    void on_btnClose_clicked();
};

#endif // BOTTOMWIDGET_H
