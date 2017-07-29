#ifndef MYCLASSWIN_H
#define MYCLASSWIN_H

#include <QMainWindow>

#include "querybank.h"

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

private:
    Ui::MyClassWin *ui;
    QueryBank *wskQb;
    QSqlQueryModel *Qmodel;

    QModelIndex index;

    void LoadClass();
};

#endif // MYCLASSWIN_H
