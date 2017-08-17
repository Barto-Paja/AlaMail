#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    wskQb = new QueryBank;

    wskQb->isOpen();
    LoadProfile();
}

Profile::~Profile()
{
    delete ui;
}

void Profile::LoadProfile()
{
    ui->lE_username->setText(wskQb->userInfo(1));
    ui->lE_surname->setText(wskQb->userInfo(4));
    ui->lE_name->setText(wskQb->userInfo(5));
    ui->lE_email->setText(wskQb->userInfo(3));
    loadCombobox();
    int ind = ui->comboBox->findData(wskQb->userInfo(6).toInt());

    if(ind != -1)
    {
        ui->comboBox->setCurrentIndex(ind);
    }
}

void Profile::on_Edit_clicked()
{
    ui->lE_email->setEnabled(true);
    ui->lE_name->setEnabled(true);
    ui->lE_surname->setEnabled(true);
    ui->lE_username->setEnabled(true);
    ui->Save->setEnabled(true);
    ui->comboBox->setEnabled(true);
}

void Profile::on_Save_clicked()
{
    if(formControl())
    {
        wskQb->updateUser(ui->lE_email->text(),ui->lE_username->text(),ui->lE_name->text(),ui->lE_surname->text(),ui->comboBox->currentData().toInt());
        QMessageBox::information(0,"Zmiana danych w profilu","Zmiana informacji przebiegła pomyślnie");
        ui->lE_email->setEnabled(false);
        ui->lE_name->setEnabled(false);
        ui->lE_surname->setEnabled(false);
        ui->lE_username->setEnabled(false);
        ui->Save->setEnabled(false);
            ui->comboBox->setEnabled(false);
        LoadProfile();
    }
    else
    {
        QMessageBox::information(0,"Zmiana danych w profilu","Zmiana informacji nie przebiegła pomyślnie");
    }
}

bool Profile::formControl()
{

    QRegExp mail("\\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\\.[A-Z]{2,4}\\b");
    mail.setCaseSensitivity(Qt::CaseInsensitive);
    mail.setPatternSyntax(QRegExp::RegExp);

    if(ui->lE_username->text().length()<6)
    {
        QMessageBox::warning(0,"Błąd formularza","Nazwa użytkownika musi mieć conajmniej 6 znaków!");
        return false;
    }
    else if(wskQb->isUserExist(ui->lE_username->text()))
    {
        QMessageBox::warning(0,"Błąd formularza","Użytkownik o takiej nazwie już istnieje");
        return false;
    }                
    else if(!mail.exactMatch(ui->lE_email->text()))
    {
        QMessageBox::warning(0,"Błąd formularza","Niepoprawny adres email");
        return false;
    }
    else if(ui->lE_surname->text().length()<4)
    {
        QMessageBox::warning(0,"Błąd formularza","Podaj swoje imię");
        return false;
    }
    else if(ui->lE_name->text().length()<=0)
    {
        QMessageBox::warning(0,"Błąd formularza","Podaj swoje nazwisko");
        return false;
    }
    return true;

}

void Profile::loadCombobox()
{
    wskQb->subjectsNames();
    ui->comboBox->clear();
    QString stream;
    int i=0;
    while (wskQb->getsubjectsNames(stream,i)) {
        ui->comboBox->addItem(stream,i);

    }
}

void Profile::on_Close_clicked()
{
    ui->lE_email->setEnabled(false);
    ui->lE_name->setEnabled(false);
    ui->lE_surname->setEnabled(false);
    ui->lE_username->setEnabled(false);
    ui->Save->setEnabled(false);
    ui->comboBox->setEnabled(false);
    LoadProfile();
    this->close();
}
