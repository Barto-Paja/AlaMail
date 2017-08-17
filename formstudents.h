#ifndef FORMSTUDENTS_H
#define FORMSTUDENTS_H

#include <QDialog>
#include <QMessageBox>

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

    void on_button_Confirm_clicked();

    void on_button_addStudent_clicked();

    void on_button_Canel_clicked();

    void on_button_deleteStudent_clicked();

    void on_button_Update_clicked();

private:
    Ui::FormStudents *ui;

    QueryBank *wskQb;
    QSqlQueryModel *qmodel;

    QModelIndex index;

    bool formControl();
    void loadCombobox();
    void clearLE();
    void enableAlllE();
    void disableAlllE();

    bool anyChanges();
    void refreshTable();

    //Private variables for Line_Edit formular

    QString surname = NULL;
    QString name = NULL;
    QString city = NULL;
    QString street = NULL;
    QString postcode = NULL;
    QString snameM = NULL;
    QString phoneM = NULL;
    QString snameF = NULL;
    QString phoneF = NULL;
    int groupIndex = -1;

    void setVariablesF();

};

#endif // FORMSTUDENTS_H
