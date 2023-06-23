#ifndef DRAWERWIDGET_H
#define DRAWERWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QTableWidget>
#include <QIcon>

class DrawerWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *mainLayout;
    QHBoxLayout *btnLayout;
    QPushButton *compileTab;
    QPushButton *resourcesTab;
    QPushButton *compLogTab;
    QPushButton *debugTab;
    QPushButton *searchResTab;
    QPushButton *closeTab;

    QHBoxLayout *tabLayout;
    QTableWidget *compileTabWin;
    QWidget *compLogTabWin;
    QWidget *debugTabWin;
    QTableWidget *resourcesTabWin;
    QTableWidget *searchResTabWin;

public:
    explicit DrawerWidget(QWidget *parent = nullptr);

signals:

public slots:
    void on_btnCompile_clicked();
    void on_btnResources_clicked();
    void on_btnCompLog_clicked();
    void on_btnDebug_clicked();
    void on_btnSearchRes_clicked();
    void on_btnClose_clicked();
};

#endif // DRAWERWIDGET_H
