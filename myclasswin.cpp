#include "myclasswin.h"
#include "ui_myclasswin.h"

MyClassWin::MyClassWin(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MyClassWin)
{
    ui->setupUi(this);
    wskQb = new QueryBank;
    Qmodel = new QSqlQueryModel;

    LoadClass();

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
}

MyClassWin::~MyClassWin()
{
    delete ui;
}

void MyClassWin::LoadClass()
{
    wskQb->isOpen();
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
    wskQb->isOpen();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),2).data().toInt();

    ui->label_surname->setText(wskQb->selectedRecord(i,1));
    ui->label_name->setText(wskQb->selectedRecord(i,2));
    ui->label_city->setText(wskQb->selectedRecord(i,3));
    ui->label_street->setText(wskQb->selectedRecord(i,4));
    ui->label_postcode->setText(wskQb->selectedRecord(i,5));
    ui->label_mothername->setText(wskQb->selectedRecord(i,6));
    ui->label_phoneM->setText(wskQb->selectedRecord(i,7));
    ui->label_fathername->setText(wskQb->selectedRecord(i,8));
    ui->label_phoneF->setText(wskQb->selectedRecord(i,9));

}

void MyClassWin::on_actionUczniowie_triggered()
{
    wskQb->closeDB();
    formFS = new FormStudents;
    formFS->show();
}
