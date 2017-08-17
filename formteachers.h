#ifndef FORMTEACHERS_H
#define FORMTEACHERS_H

#include <QDialog>
#include <QMessageBox>

#include "querybank.h"

namespace Ui {
class FormTeachers;
}

class FormTeachers : public QDialog
{
    Q_OBJECT

public:
    explicit FormTeachers(QWidget *parent = 0);
    ~FormTeachers();
private slots:
    void recordSelected();

    void on_button_Add_clicked();

    void on_button_Edit_clicked();

    void on_button_Delete_clicked();

    void on_button_Confirm_clicked();

    void on_button_Update_clicked();

    void on_button_Canel_clicked();

    void on_button_ShowPassword_pressed();

    void on_button_ShowPassword_released();

private:
    Ui::FormTeachers *ui;

    QueryBank *wskQb;
    QSqlQueryModel *qmodel;

    QModelIndex index;

    void refreshTable();

//--- Private variables for Line_Edit formular

    QString username = NULL;
    QString password = NULL;
    QString email = NULL;
    QString name = NULL;
    QString surname = NULL;
    int idS = -1;  //-- ID Specialization

    void setVariablesF();
    void loadCombobox();

//--- Line Edit management

    void clearLE();
    void enableLE();
    void disableLE();
};

#endif // FORMTEACHERS_H
