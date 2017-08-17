#ifndef FORMSUBJECTS_H
#define FORMSUBJECTS_H

#include <QDialog>
#include <QMessageBox>

#include "querybank.h"

namespace Ui {
class FormSubjects;
}

class FormSubjects : public QDialog
{
    Q_OBJECT

public:
    explicit FormSubjects(QWidget *parent = 0);
    ~FormSubjects();

private slots:
    void recordSelected();

    void on_button_Add_clicked();

    void on_button_Edit_clicked();

    void on_button_Delete_clicked();

    void on_button_Confirm_clicked();

    void on_button_Update_clicked();

    void on_button_Canel_clicked();

private:
    Ui::FormSubjects *ui;

    QueryBank *wskQb;
    QSqlQueryModel *qmodel;
    QModelIndex index;

    void refreshTable();
};

#endif // FORMSUBJECTS_H
