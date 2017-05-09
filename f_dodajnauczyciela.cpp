#include "f_dodajnauczyciela.h"
#include "ui_f_dodajnauczyciela.h"

F_DodajNauczyciela::F_DodajNauczyciela(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::F_DodajNauczyciela)
{
    ui->setupUi(this);
}

F_DodajNauczyciela::~F_DodajNauczyciela()
{
    delete ui;
}
