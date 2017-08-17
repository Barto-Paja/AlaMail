#include "formsubjects.h"
#include "ui_formsubjects.h"

FormSubjects::FormSubjects(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormSubjects)
{
    ui->setupUi(this);
    wskQb = new QueryBank;
    qmodel = new QSqlQueryModel;

    wskQb->isOpen();
    wskQb->loadSubjects();
    wskQb->setQModel(*qmodel);

    qmodel->setHeaderData(0,Qt::Horizontal,("ID"));
    qmodel->setHeaderData(1,Qt::Horizontal,("Nazwa specjalizacji"));

    ui->tableView->setModel(qmodel);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
}

FormSubjects::~FormSubjects()
{
    delete ui;
}

void FormSubjects::recordSelected()
{
    wskQb->isOpen();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),0).data().toInt();

    ui->label_2->setText(wskQb->selectedRecord(i,0,"sb"));
    ui->lineEdit->setText(wskQb->selectedRecord(i,1,"sb"));

    ui->button_Edit->setEnabled(true);
    ui->button_Delete->setEnabled(true);
}

void FormSubjects::on_button_Add_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->button_Confirm->setEnabled(true);
    ui->button_Canel->setEnabled(true);
}

void FormSubjects::on_button_Edit_clicked()
{
    ui->lineEdit->setEnabled(true);
    ui->button_Update->setEnabled(true);
    ui->button_Canel->setEnabled(true);
}

void FormSubjects::on_button_Delete_clicked()
{
    ui->lineEdit->clear();
    refreshTable();
}

void FormSubjects::on_button_Confirm_clicked()
{
    ui->lineEdit->setEnabled(false);
    wskQb->addSubject(ui->lineEdit->text());
    refreshTable();
}

void FormSubjects::on_button_Update_clicked()
{

    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),0).data().toInt();
    ui->lineEdit->setEnabled(false);
    wskQb->updSubject(ui->lineEdit->text(),wskQb->selectedRecord(i,0,"sb").toInt());
    refreshTable();
}

void FormSubjects::on_button_Canel_clicked()
{
    ui->lineEdit->setEnabled(false);
    ui->lineEdit->clear();
}

void FormSubjects::refreshTable()
{
    wskQb->loadSubjects();
    wskQb->setQModel(*qmodel);
    ui->tableView->setModel(qmodel);
}
