#include "formteachers.h"
#include "ui_formteachers.h"

FormTeachers::FormTeachers(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormTeachers)
{
    ui->setupUi(this);
    wskQb = new QueryBank;
    qmodel = new QSqlQueryModel;

    wskQb->isOpen();
    wskQb->loadTeachers();
    wskQb->setQModel(*qmodel);

    qmodel->setHeaderData(1,Qt::Horizontal,("Nazwa użytkownika"));
    qmodel->setHeaderData(3,Qt::Horizontal,("E-mail"));
    qmodel->setHeaderData(4,Qt::Horizontal,("Imię"));
    qmodel->setHeaderData(5,Qt::Horizontal,("Nazwisko"));
    qmodel->setHeaderData(8,Qt::Horizontal,("Specjalizacja"));

    ui->tableView->setModel(qmodel);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(2,true);
    ui->tableView->setColumnHidden(6,true);
    ui->tableView->setColumnHidden(7,true);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
}

FormTeachers::~FormTeachers()
{
    delete ui;
}

void FormTeachers::recordSelected()
{
    wskQb->isOpen();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),0).data().toInt();

    ui->lE_UserName->setText(wskQb->selectedRecord(i,1,"t"));
    ui->lE_Password->setText(wskQb->selectedRecord(i,2,"t"));
    ui->lE_Email->setText(wskQb->selectedRecord(i,3,"t"));
    ui->lE_Surname->setText(wskQb->selectedRecord(i,4,"t"));
    ui->lE_Name->setText(wskQb->selectedRecord(i,5,"t"));

    loadCombobox();
    int ind = ui->comboBox->findData(wskQb->selectedRecord(i,6,"t").toInt());

    if(ind != -1)
    {
        ui->comboBox->setCurrentIndex(ind);
    }


    ui->button_Edit->setEnabled(true);
    ui->button_Delete->setEnabled(true);
}

void FormTeachers::on_button_Add_clicked()
{
    clearLE();
    enableLE();
    ui->button_Confirm->setEnabled(true);
    ui->button_Canel->setEnabled(true);
    loadCombobox();
}

void FormTeachers::on_button_Edit_clicked()
{
    enableLE();
    ui->button_Update->setEnabled(true);
    ui->button_Canel->setEnabled(true);
}

void FormTeachers::on_button_Delete_clicked()
{
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),0).data().toInt();
    wskQb->delTeacher(wskQb->selectedRecord(i,0,"t").toInt());
    refreshTable();
    clearLE();
}

void FormTeachers::on_button_Confirm_clicked()
{
    disableLE();
    ui->button_Confirm->setEnabled(false);
    ui->button_Canel->setEnabled(false);
    setVariablesF();
    wskQb->addTeacher(username,password,email,surname,name,idS);
    QMessageBox::information(0,"",wskQb->lastError());
    refreshTable();
}

void FormTeachers::on_button_Update_clicked()
{
    disableLE();
    ui->button_Canel->setEnabled(false);
    ui->button_Update->setEnabled(false);
    setVariablesF();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),0).data().toInt();
    int id = wskQb->selectedRecord(i,0,"t").toInt();
    wskQb->updTeacher(username,password,email,surname,name,idS,id);
    refreshTable();
}

void FormTeachers::on_button_Canel_clicked()
{
    clearLE();
    disableLE();
}

void FormTeachers::on_button_ShowPassword_pressed()
{
    ui->lE_Password->setEchoMode(QLineEdit::Normal);
}

void FormTeachers::on_button_ShowPassword_released()
{
    ui->lE_Password->setEchoMode(QLineEdit::Password);
}

void FormTeachers::refreshTable()
{
    wskQb->loadTeachers();
    wskQb->setQModel(*qmodel);
    ui->tableView->setModel(qmodel);
}

void FormTeachers::setVariablesF()
{
    name = ui->lE_Name->text();
    surname = ui->lE_Surname->text();
    email = ui->lE_Email->text();
    password = ui->lE_Password->text();
    username = ui->lE_UserName->text();

    idS = ui->comboBox->currentData().toInt();
}

void FormTeachers::loadCombobox()
{
    wskQb->subjectsNames();
    ui->comboBox->clear();
    QString stream;
    int i=0;
    while (wskQb->getsubjectsNames(stream,i)) {
        ui->comboBox->addItem(stream,i);

    }
}

void FormTeachers::clearLE()
{
    ui->lE_Email->clear();
    ui->lE_Name->clear();
    ui->lE_Password->clear();
    ui->lE_Surname->clear();
    ui->lE_UserName->clear();
}

void FormTeachers::enableLE()
{
    ui->lE_Email->setEnabled(true);
    ui->lE_Name->setEnabled(true);
    ui->lE_Surname->setEnabled(true);
    ui->lE_UserName->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->lE_Password->setEnabled(true);
}

void FormTeachers::disableLE()
{
    ui->lE_Email->setEnabled(false);
    ui->lE_Name->setEnabled(false);
    ui->lE_Password->setEnabled(false);
    ui->lE_Surname->setEnabled(false);
    ui->lE_UserName->setEnabled(false);
    ui->comboBox->setEnabled(false);
}
