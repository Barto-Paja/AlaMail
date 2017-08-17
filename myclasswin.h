#ifndef MYCLASSWIN_H
#define MYCLASSWIN_H

#include <QMainWindow>
#include <QInputDialog>

#include "querybank.h"

#include "formstudents.h"
#include "formgroups.h"
#include "formteachers.h"
#include "formsubjects.h"

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

    void on_actionGrupy_triggered();

    void on_actionNauczyciele_triggered();

    void on_actionPrzedmioty_triggered();

    void on_actionNadawanie_uprawnie_triggered();

private:
    Ui::MyClassWin *ui;
    QueryBank *wskQb;
    QSqlQueryModel *Qmodel;

    FormStudents *formFS;
    FormGroups *formFG;
    FormTeachers *formTG;
    FormSubjects *formSbG;

    QModelIndex index;

    void LoadClass();
};

#endif // MYCLASSWIN_H
