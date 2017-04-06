#ifndef PODGLAD_H
#define PODGLAD_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlQueryModel>

namespace Ui {
class Podglad;
}

class Podglad : public QMainWindow
{
    Q_OBJECT

public:
    explicit Podglad(QWidget *parent = 0);


    ~Podglad();

private:
    Ui::Podglad *ui;
};

#endif // PODGLAD_H
