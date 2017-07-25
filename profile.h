#ifndef PROFILE_H
#define PROFILE_H

#include <QWidget>

#include "querybank.h"

namespace Ui {
class Profile;
}

class Profile : public QWidget
{
    Q_OBJECT

public:
    explicit Profile(QWidget *parent = 0, QString vLogin = NULL);
    ~Profile();

    void LoadProfile();

private:
    Ui::Profile *ui;
    QString vLogin;
    QueryBank *wskQb;
};

#endif // PROFILE_H
