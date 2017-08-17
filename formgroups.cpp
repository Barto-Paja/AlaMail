#include "formgroups.h"
#include "ui_formgroups.h"

FormGroups::FormGroups(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::FormGroups)
{
    ui->setupUi(this);
    wskQb = new QueryBank;
    qmodel = new QSqlQueryModel;

    wskQb->isOpen();
    wskQb->loadGroups();
    wskQb->setQModel(*qmodel);

    qmodel->setHeaderData(1,Qt::Horizontal,("Data założenia"));
    qmodel->setHeaderData(2,Qt::Horizontal,("Nazwa"));
    qmodel->setHeaderData(3,Qt::Horizontal,("Imię"));
    qmodel->setHeaderData(4,Qt::Horizontal,("Nazwisko"));

    ui->tableView->setModel(qmodel);
    ui->tableView->setColumnHidden(0,true);
    ui->tableView->setColumnHidden(5,true);

    connect(ui->tableView, SIGNAL(clicked(const QModelIndex&)), this, SLOT(recordSelected()));
}

FormGroups::~FormGroups()
{
    delete ui;
}

void FormGroups::recordSelected()
{
    wskQb->isOpen();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),0).data().toInt();

    ui->lE_nameG->setText(wskQb->selectedRecord(i,2,"g"));
    ui->lE_date->setText(wskQb->selectedRecord(i,1,"g"));

    loadCombobox();
    int ind = ui->comboBox->findData(wskQb->selectedRecord(i,3,"g").toInt());

    if(ind != -1)
    {
        ui->comboBox->setCurrentIndex(ind);
    }

    ui->button_del->setEnabled(true);
    ui->button_edit->setEnabled(true);
}

void FormGroups::on_button_edit_clicked()
{
    ui->button_update->setEnabled(true);
    ui->button_canel->setEnabled(true);
    ui->lE_date->setEnabled(true);
    ui->lE_nameG->setEnabled(true);
    ui->comboBox->setEnabled(true);
}

void FormGroups::on_button_del_clicked()
{
    int idG = wskQb->selectedRecord(index.sibling(index.row(),0).data().toInt(),0,"g").toInt();
    wskQb->delGroup(idG);
    QMessageBox::information(0,"Aktualizacja","Usuwanie rekordu powiodło się \n");
    refreshTable();
}

void FormGroups::on_button_confirm_clicked()
{
    if(formularControl())
    {
        setVariableF();
        convertDate();

        idW = ui->comboBox->currentData().toInt();
        wskQb->addGroup(date,nameGroup,idW);

        QMessageBox::information(0,"Aktualizacja","Dodawanie rekordu powiodło się \n");

        refreshTable();

        ui->lE_date->setEnabled(false);
        ui->lE_nameG->setEnabled(false);
        ui->button_confirm->setEnabled(false);
        ui->button_canel->setEnabled(false);
        ui->button_confirm->setEnabled(false);
        ui->comboBox->setEnabled(false);
    }

}

void FormGroups::on_button_canel_clicked()
{
    ui->lE_date->setEnabled(false);
    ui->lE_nameG->setEnabled(false);
    ui->button_confirm->setEnabled(false);
    ui->button_canel->setEnabled(false);
    ui->button_update->setEnabled(false);
    ui->comboBox->setEnabled(false);
    ui->lE_date->clear();
    ui->lE_nameG->clear();
}

void FormGroups::on_button_update_clicked()
{
    if(formularControl())
    {
        int i = index.sibling(index.row(),0).data().toInt();
        setVariableF();

        convertDate();

        wskQb->updGroup(date,nameGroup,idW,wskQb->selectedRecord(i,0,"g").toInt());
        QMessageBox::information(0,"Aktualizacja","Aktualizowanie rekordu powiodło się ");
    }
    else
        QMessageBox::information(0,"Aktualizacja","Aktualizowanie rekordu niepowiodło się \n\n Błąd: " + wskQb->lastError());

    refreshTable();
}

void FormGroups::on_button_add_clicked()
{
    ui->lE_date->setEnabled(true);
    ui->lE_nameG->setEnabled(true);
    ui->button_confirm->setEnabled(true);
    ui->button_canel->setEnabled(true);
    ui->comboBox->setEnabled(true);
    ui->lE_date->clear();
    ui->lE_nameG->clear();
    loadCombobox();
}

bool FormGroups::formularControl()
{
    QRegExp datef("\\d{4}-\\d{2}");
    datef.setCaseSensitivity(Qt::CaseInsensitive);
    datef.setPatternSyntax(QRegExp::RegExp);

    QRegExp datev("\\d{4}-[0-1][0-9]");
    datev.setCaseSensitivity(Qt::CaseInsensitive);
    datev.setPatternSyntax(QRegExp::RegExp);

    QString stream = ui->lE_date->text();

    if(!datef.exactMatch(ui->lE_date->text()))
    {
        QMessageBox::information(0,"Błąd formularza","Niepoprawny format daty. \n Prawidłowy format daty to YYYY-MM");
        return false;
    }
    else if(!datev.exactMatch(ui->lE_date->text()) || (stream[5] == '0' && stream[6] == '0') || (stream[5] == '1' && !(stream[6] == '0' || stream[6] == '1' || stream[6] == '2')))
    {
        QMessageBox::information(0,"Błąd formularza","Niepoprawny format daty. Wartość miesiaca nie mieści się w przedziale 01-12");
        return false;
    }
    else if(wskQb->isNameExist(ui->lE_nameG->text()))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Zbieżność nazw grup","W bazie danych istnieje już grupa o takiej nazwie, kontynuować?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            QMessageBox::information(0,"Potwierdzono","Zawartość formularza zatwierdzona");
            return true;
        }
        else
        {
            QMessageBox::information(0,"Anulowano","Pomyślnie wstrzymano dodwania grupy");
            return false;
        }
    };


}

void FormGroups::loadCombobox()
{
    wskQb->workersNames();
    ui->comboBox->clear();
    QString stream;
    int i=0;
    while (wskQb->getworkersNames(stream,i)) {
        ui->comboBox->addItem(stream,i);

    }
}

void FormGroups::setVariableF()
{
    date = ui->lE_date->text();
    nameGroup = ui->lE_nameG->text();
    idW = ui->comboBox->currentData().toInt();
}

void FormGroups::convertDate()
{
    date.replace("-","/");
}

void FormGroups::refreshTable()
{
    wskQb->loadGroups();
    wskQb->setQModel(*qmodel);
    ui->tableView->setModel(qmodel);
}
