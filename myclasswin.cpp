#include "myclasswin.h"
#include "ui_myclasswin.h"

MyClassWin::MyClassWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyClassWin)
{
    ui->setupUi(this);
    wskQb = new QueryBank;
    Qmodel = new QSqlQueryModel;

    wskQb->isOpen();
    LoadClass();

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
}

MyClassWin::~MyClassWin()
{
    delete ui;
}

void MyClassWin::LoadClass()
{
    wskQb->loadMyClass();
    wskQb->setQModel(*Qmodel);

    Qmodel->setHeaderData(0,Qt::Horizontal,("Nazwisko"));
    Qmodel->setHeaderData(1,Qt::Horizontal,("Imię"));

    ui->tableView->setModel(Qmodel);
    ui->tableView->sortByColumn(0);
    ui->tableView->setColumnHidden(2,true);
}

void MyClassWin::recordSelected()
{
    index = ui->tableView->currentIndex();
    int i = index.row();
    ui->label_3->setText(QString::number(i)+" "+index.sibling(i,0).data().toString());
}
