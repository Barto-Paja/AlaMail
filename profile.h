#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>
#include <QMessageBox>

#include "querybank.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = 0);
    ~Profile();

    void LoadProfile();

private slots:
    void on_Edit_clicked();

    void on_Save_clicked();

private:

    Ui::Profile *ui;
    QString vLogin;
    QueryBank *wskQb;

    bool formularControl();
};

#endif // PROFILE_H
