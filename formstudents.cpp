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

    qmodel->setHeaderData(1,Qt::Horizontal,("Imię"));
    qmodel->setHeaderData(2,Qt::Horizontal,("Nazwisko"));
    qmodel->setHeaderData(3,Qt::Horizontal,("Miasto"));
    qmodel->setHeaderData(4,Qt::Horizontal,("Ulica"));
    qmodel->setHeaderData(5,Qt::Horizontal,("Kod pocztowy"));
    qmodel->setHeaderData(6,Qt::Horizontal,("Imię Matki"));
    qmodel->setHeaderData(7,Qt::Horizontal,("Tel. Matki"));
    qmodel->setHeaderData(8,Qt::Horizontal,("Imię Ojca"));
    qmodel->setHeaderData(9,Qt::Horizontal,("Tel. Ojca"));
    qmodel->setHeaderData(10,Qt::Horizontal,("Grupa"));

    ui->tableView->setModel(qmodel);
    ui->tableView->sortByColumn(10);
    ui->tableView->setColumnHidden(0,true);
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
    int i = index.sibling(index.row(),0).data().toInt();

    ui->lE_surname->setText(wskQb->selectedRecord(i,1,"s"));
    ui->lE_name->setText(wskQb->selectedRecord(i,2,"s"));
    ui->lE_city->setText(wskQb->selectedRecord(i,3,"s"));
    ui->lE_street->setText(wskQb->selectedRecord(i,4,"s"));
    ui->lE_postcode->setText(wskQb->selectedRecord(i,5,"s"));
    ui->lE_snameM->setText(wskQb->selectedRecord(i,6,"s"));
    ui->lE_phoneM->setText(wskQb->selectedRecord(i,7,"s"));
    ui->lE_snameF->setText(wskQb->selectedRecord(i,8,"s"));
    ui->lE_phoneF->setText(wskQb->selectedRecord(i,9,"s"));

    loadCombobox();
    int ind = ui->comboBox->findData(wskQb->selectedRecord(i,10,"s").toInt());

    if(ind != -1)
    {
        ui->comboBox->setCurrentIndex(ind);
    }

    ui->button_editStudent->setEnabled(true);
    ui->button_deleteStudent->setEnabled(true);
}

void FormStudents::on_button_editStudent_clicked()
{
    enableAlllE();
    ui->button_Update->setEnabled(true);
    ui->button_Canel->setEnabled(true);
}

void FormStudents::on_button_Confirm_clicked()
{    
    if(formControl())
    {
        setVariablesF();

        groupIndex = ui->comboBox->currentData().toInt();

        if(wskQb->addStudent(surname,name,city,street,postcode,snameM,phoneM,snameF,phoneF,groupIndex))
        {
            QMessageBox::information(0,"Dodawanie ucznia","Dodano ucznia pomyślnie!");
            refreshTable();
            disableAlllE();
            ui->button_Canel->setEnabled(false);
            ui->button_Confirm->setEnabled(false);
        }
        else
        {
            QMessageBox::information(0,"Dodawanie ucznia","Dodawnie ucznia niepowiodło się \n Błąd: " + wskQb->lastError());
        }
    }

}

bool FormStudents::formControl()
{
    QRegExp postc("\\d{2}-\\d{3}");
    postc.setCaseSensitivity(Qt::CaseInsensitive);
    postc.setPatternSyntax(QRegExp::RegExp);

    QRegExp phone("\\d{9}");
    phone.setCaseSensitivity(Qt::CaseInsensitive);
    phone.setPatternSyntax(QRegExp::RegExp);

    if(ui->lE_surname->text().length()<4)
    {
        QMessageBox::information(0,"Błąd formularza","Podaj imię (Co najmniej 4 znaki)");
        return false;
    }
    else if(ui->lE_surname->text().length()<=0)
    {
        QMessageBox::information(0,"Błąd formularza","Podaj nazwisko");
    }
    else if(ui->lE_city->text().length()<=0)
    {
        QMessageBox::information(0,"Błąd formularza","Podaj miasto");
        return false;
    }
    else if(ui->lE_street->text().length()<=0)
    {
        QMessageBox::information(0,"Błąd formularza","Podaj ulicę lub numer budynku");
        return false;
    }
    else if(!postc.exactMatch(ui->lE_postcode->text()))
    {
        QMessageBox::information(0,"Błąd formularza","Podaj kod pocztowy w formacie 'XX-XXX'");
        return false;
    }
    else if(ui->lE_snameM->text().length()<4)
    {
        QMessageBox::information(0,"Błąd formularza","Podaj imię matki ucznia (Co najmniej 4 znaki)");
        return false;
    }
    else if(!phone.exactMatch(ui->lE_phoneM->text()))
    {
        QMessageBox::information(0,"Błąd formularza","Podaj numer telefonu \n\n dla stacjonarnych np.: 236701122 \n dla komórkowych 999888777");
        return false;
    }
    else if(ui->lE_snameF->text().length()<4)
    {
        QMessageBox::information(0,"Błąd formularza","Podaj imię ojca ucznia (Co najmniej 4 znaki)");
        return false;
    }
    else if(!phone.exactMatch(ui->lE_phoneF->text()))
    {
        QMessageBox::information(0,"Błąd formularza","Podaj numer telefonu \n\n dla stacjonarnych np.: 236701122 \n dla komórkowych 999888777");
        return false;
    }
    else if(ui->comboBox->currentIndex()==(-1))
    {
        QMessageBox::StandardButton reply = QMessageBox::question(this,"Formularz","Uczeń nie został przydzielony do żadnej grupy kontynuować dodwanie ucznia?",QMessageBox::Yes|QMessageBox::No);
        if(reply==QMessageBox::Yes)
        {
            QMessageBox::information(0,"Potwierdzono","Zawartość formularza zatwierdzona");
            return true;
        }
        else
        {
            QMessageBox::information(0,"Anulowano","Pomyślnie wstrzymano dodwania ucznia");
            return false;
        }
    }
    else
        return true;

    return false;
}

void FormStudents::loadCombobox()
{
    wskQb->groupNames();
    ui->comboBox->clear();
    QString stream;
    int i=0;
    while (wskQb->getGroupName(stream,i)) {
        ui->comboBox->addItem(stream,i);

    }
}

void FormStudents::clearLE()
{
    ui->lE_surname->clear();
    ui->lE_name->clear();
    ui->lE_city->clear();
    ui->lE_street->clear();
    ui->lE_postcode->clear();
    ui->lE_snameM->clear();
    ui->lE_phoneM->clear();
    ui->lE_snameF->clear();
    ui->lE_phoneF->clear();
}

void FormStudents::enableAlllE()
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
    ui->comboBox->setEnabled(true);
}

void FormStudents::disableAlllE()
{
    ui->lE_surname->setEnabled(false);
    ui->lE_name->setEnabled(false);
    ui->lE_city->setEnabled(false);
    ui->lE_street->setEnabled(false);
    ui->lE_postcode->setEnabled(false);
    ui->lE_snameM->setEnabled(false);
    ui->lE_phoneM->setEnabled(false);
    ui->lE_snameF->setEnabled(false);
    ui->lE_phoneF->setEnabled(false);
    ui->comboBox->setEnabled(false);
}

bool FormStudents::anyChanges()
{
    setVariablesF();
    int idU = wskQb->selectedRecord(index.sibling(index.row(),0).data().toInt(),0,"s").toInt();
    int idG = ui->comboBox->currentData().toInt();

    if(wskQb->updStudent(surname,name,city,street,postcode,snameM,phoneM,snameF,phoneF,idG,idU))
    {
        QMessageBox::information(0,"Aktualizacja","Zaaktualizowano rekord pomyślnie");
    }
    else
    {
        QMessageBox::information(0,"Aktualizacja","Aktualizowanie rekordu niepowiodło się \n\n Błąd: " + wskQb->lastError());
    }

    return false;
}

void FormStudents::refreshTable()
{
    wskQb->loadStudents();
    wskQb->setQModel(*qmodel);
    ui->tableView->setModel(qmodel);
}

void FormStudents::setVariablesF()
{
    surname = ui->lE_surname->text();
    name = ui->lE_name->text();
    city = ui->lE_city->text();
    street = ui->lE_street->text();
    postcode = ui->lE_postcode->text();
    snameM = ui->lE_snameM->text();
    phoneM = ui->lE_phoneM->text();
    snameF = ui->lE_snameF->text();
    phoneF = ui->lE_phoneF->text();
}

void FormStudents::on_button_addStudent_clicked()
{
    enableAlllE();
    ui->button_Confirm->setEnabled(true);
    ui->button_Canel->setEnabled(true);
    loadCombobox();
    clearLE();
}

void FormStudents::on_button_Canel_clicked()
{
    disableAlllE();
    ui->button_Confirm->setEnabled(false);
    ui->button_Canel->setEnabled(false);
    clearLE();
}

void FormStudents::on_button_deleteStudent_clicked()
{
    int idU = wskQb->selectedRecord(index.sibling(index.row(),0).data().toInt(),0,"s").toInt();
    ui->label_10->setText(QString::number(idU));
    if(wskQb->delStudent(idU))
    {
        QMessageBox::information(0,"Usuwanie ucznia","Usunięto ucznia");
        refreshTable();
    }
    else
    {
        QMessageBox::information(0,"Dodawanie ucznia","Dodawnie ucznia niepowiodło się \n Błąd: " + wskQb->lastError());
    }
}

void FormStudents::on_button_Update_clicked()
{
    if(formControl())
    {
        anyChanges();
        disableAlllE();
        ui->button_Update->setEnabled(false);
        refreshTable();
    }
}
