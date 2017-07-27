#include "myclasswin.h"
#include "ui_myclasswin.h"

MyClassWin::MyClassWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyClassWin)
{
    ui->setupUi(this);
}

MyClassWin::~MyClassWin()
{
    delete ui;
}
