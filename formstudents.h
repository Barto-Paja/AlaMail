#ifndef FORMSTUDENTS_H
#define FORMSTUDENTS_H

#include <QDialog>

#include "querybank.h"

namespace Ui {
class FormStudents;
}

class FormStudents : public QDialog
{
    Q_OBJECT

public:
    explicit FormStudents(QWidget *parent = 0);
    ~FormStudents();

private slots:
    void recordSelected();

    void on_button_editStudent_clicked();

private:
    Ui::FormStudents *ui;

    QueryBank *wskQb;
    QSqlQueryModel *qmodel;

    QModelIndex index;
};

#endif // FORMSTUDENTS_H
