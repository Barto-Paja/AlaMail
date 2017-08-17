#ifndef FORMGROUPS_H
#define FORMGROUPS_H

#include <QDialog>
#include <QSqlQueryModel>
#include <QMessageBox>

#include "querybank.h"

namespace Ui {
class FormGroups;
}

class FormGroups : public QDialog
{
    Q_OBJECT

public:
    explicit FormGroups(QWidget *parent = 0);
    ~FormGroups();
private slots:

    void recordSelected();

    void on_button_edit_clicked();

    void on_button_del_clicked();

    void on_button_confirm_clicked();

    void on_button_canel_clicked();

    void on_button_update_clicked();

    void on_button_add_clicked();

private:
    Ui::FormGroups *ui;

    QueryBank *wskQb;
    QSqlQueryModel *qmodel;

    QModelIndex index;

    bool formularControl();
    void loadCombobox();

    QString date = NULL;
    QString nameGroup = NULL;
    int idW =  -1;

    void setVariableF();
    void convertDate();
    void refreshTable();
};

#endif // FORMGROUPS_H
