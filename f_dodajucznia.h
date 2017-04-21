#ifndef F_DODAJUCZNIA_H
#define F_DODAJUCZNIA_H

#include <QDialog>
#include <QMessageBox>

#include <QSqlQuery>
#include <QSqlQueryModel>

#include "querybank.h"

namespace Ui {
class F_DodajUcznia;
}

class F_DodajUcznia : public QDialog
{
    Q_OBJECT

public:
    explicit F_DodajUcznia(QWidget *parent = 0);
    ~F_DodajUcznia();
signals:
    void send(QSqlQuery);

private slots:
    void on_pushButton_clicked();
    void czyPelne();

private:
    Ui::F_DodajUcznia *ui;
    QSqlQuery *qr;
    QSqlQueryModel *mdl;
};

#endif // F_DODAJUCZNIA_H
