#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSplitter>
#include <QSettings>
#include <QSizePolicy>
#include "managerwidget.h"
#include "editorwidget.h"
#include "bottomwidget.h"

class MainWidget : public QWidget
{
    Q_OBJECT
public:
    QVBoxLayout *mainLayout;
    QSplitter *hSplitter;
    QSplitter *vSplitter;
    QSettings originSettings;
    ManagerWidget *managerWin;
    EditorWidget *editorWin;
    BottomWidget *bottomWin;

public:
    explicit MainWidget(QWidget *parent = nullptr);

signals:

public slots:
};

#endif // MAINWIDGET_H
