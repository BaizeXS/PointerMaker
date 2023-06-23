#ifndef MANAGERWIDGET_H
#define MANAGERWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include <QTreeWidget>
#include <QTreeWidgetItem>
#include <QDir>
#include <QTextEdit>
#include <QVBoxLayout>


class ManagerWidget : public QWidget
{
    Q_OBJECT
public:
    QTabWidget *ProjMan;
    QVBoxLayout *mainLayout;
    QTreeWidget * treeWidget;



public:
    explicit ManagerWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MANAGERWIDGET_H
