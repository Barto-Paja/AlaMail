#ifndef MYCLASSWIN_H
#define MYCLASSWIN_H

#include <QMainWindow>

#include "querybank.h"
#include "formstudents.h"

namespace Ui {
class MyClassWin;
}

class MyClassWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyClassWin(QWidget *parent = 0);
    ~MyClassWin();

private slots:

    void recordSelected();

    void on_actionUczniowie_triggered();

private:
    Ui::MyClassWin *ui;
    QueryBank *wskQb;
    QSqlQueryModel *Qmodel;

    FormStudents *formFS;

    QModelIndex index;

    void LoadClass();
};

#endif // MYCLASSWIN_H
