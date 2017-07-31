#include "formstudents.h"
#include "ui_formstudents.h"

FormStudents::FormStudents(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormStudents)
{
    ui->setupUi(this);
    wskQb = new QueryBank;
    qmodel = new QSqlQueryModel;

    wskQb->isOpen();
    wskQb->loadStudents();
    wskQb->setQModel(*qmodel);

    qmodel->setHeaderData(0,Qt::Horizontal,("Imię"));
    qmodel->setHeaderData(1,Qt::Horizontal,("Nazwisko"));
    qmodel->setHeaderData(2,Qt::Horizontal,("Miasto"));
    qmodel->setHeaderData(3,Qt::Horizontal,("Ulica"));
    qmodel->setHeaderData(4,Qt::Horizontal,("Kod pocztowy"));
    qmodel->setHeaderData(5,Qt::Horizontal,("Imię Matki"));
    qmodel->setHeaderData(6,Qt::Horizontal,("Tel. Matki"));
    qmodel->setHeaderData(7,Qt::Horizontal,("Imię Ojca"));
    qmodel->setHeaderData(8,Qt::Horizontal,("Tel. Ojca"));
    qmodel->setHeaderData(9,Qt::Horizontal,("Grupa"));

    ui->tableView->setModel(qmodel);
    ui->tableView->sortByColumn(10);
    ui->tableView->setColumnHidden(10,true);
    ui->tableView->setColumnHidden(11,true);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
}

FormStudents::~FormStudents()
{
    wskQb->closeDB();
    delete ui;
}

void FormStudents::recordSelected()
{
    wskQb->isOpen();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),10).data().toInt();

    ui->lE_surname->setText(wskQb->selectedRecord(i,1));
    ui->lE_name->setText(wskQb->selectedRecord(i,2));
    ui->lE_city->setText(wskQb->selectedRecord(i,3));
    ui->lE_street->setText(wskQb->selectedRecord(i,4));
    ui->lE_postcode->setText(wskQb->selectedRecord(i,5));
    ui->lE_snameM->setText(wskQb->selectedRecord(i,6));
    ui->lE_phoneM->setText(wskQb->selectedRecord(i,7));
    ui->lE_snameF->setText(wskQb->selectedRecord(i,8));
    ui->lE_phoneF->setText(wskQb->selectedRecord(i,9));

// ----------------------------------------- do poprawek
    wskQb->groupNames();
    QString stream;
    while (wskQb->getGroupName(stream)) {
        ui->comboBox->addItem(stream);
    }

    ui->comboBox->setCurrentIndex((wskQb->selectedRecord(i,11).toInt()-1));
//---------------------------------------------
    ui->button_editStudent->setEnabled(true);
    ui->button_deleteStudent->setEnabled(true);
}

void FormStudents::on_button_editStudent_clicked()
{
    ui->lE_surname->setEnabled(true);
    ui->lE_name->setEnabled(true);
    ui->lE_city->setEnabled(true);
    ui->lE_street->setEnabled(true);
    ui->lE_postcode->setEnabled(true);
    ui->lE_snameM->setEnabled(true);
    ui->lE_phoneM->setEnabled(true);
    ui->lE_snameF->setEnabled(true);
    ui->lE_phoneF->setEnabled(true);
    ui->button_Confirm->setEnabled(true);
    ui->button_Canel->setEnabled(true);
}
