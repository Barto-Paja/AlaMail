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

    if(wskQb->isAdmin())
    {
        ui->actionNauczyciele->setEnabled(true);
        ui->actionNadawanie_uprawnie->setEnabled(true);
    }
    else if(wskQb->isModer())
    {
        ui->actionNauczyciele->setEnabled(true);
    }
    else
    {
        ui->actionNauczyciele->setEnabled(false);
    }
}

void MyClassWin::recordSelected()
{
    wskQb->isOpen();
    index = ui->tableView->currentIndex();
    int i = index.sibling(index.row(),2).data().toInt();

    ui->label_surname->setText(wskQb->selectedRecord(i,1,"s"));
    ui->label_name->setText(wskQb->selectedRecord(i,2,"s"));
    ui->label_city->setText(wskQb->selectedRecord(i,3,"s"));
    ui->label_street->setText(wskQb->selectedRecord(i,4,"s"));
    ui->label_postcode->setText(wskQb->selectedRecord(i,5,"s"));
    ui->label_mothername->setText(wskQb->selectedRecord(i,6,"s"));
    ui->label_phoneM->setText(wskQb->selectedRecord(i,7,"s"));
    ui->label_fathername->setText(wskQb->selectedRecord(i,8,"s"));
    ui->label_phoneF->setText(wskQb->selectedRecord(i,9,"s"));

}

void MyClassWin::on_actionUczniowie_triggered()
{
    wskQb->closeDB();
    formFS = new FormStudents;
    formFS->show();
}

void MyClassWin::on_actionGrupy_triggered()
{
    wskQb->closeDB();
    formFG = new FormGroups;
    formFG->show();
}

void MyClassWin::on_actionNauczyciele_triggered()
{
    wskQb->closeDB();
    formTG = new FormTeachers;
    formTG->show();
}

void MyClassWin::on_actionPrzedmioty_triggered()
{
    wskQb->closeDB();
    formSbG = new FormSubjects;
    formSbG->show();
}

void MyClassWin::on_actionNadawanie_uprawnie_triggered()
{
    bool ok;
    QString username = QInputDialog::getText(this,tr("Nadawanie uprawnień: Nazwa użytkownika"),tr("Podaj nazwę użytkownika:"),QLineEdit::Normal,"DefaultTxt",&ok);
    QString flag = NULL;

    if(ok && !username.isEmpty())
    {
        if(wskQb->isUserExs(username))
        {
            flag = QInputDialog::getText(this,tr("Nadawanie uprawnień: Poziom"),tr("Podaj wartość flagi:"),QLineEdit::Normal,"3",&ok);
            if(ok && !flag.isEmpty())
            {
                if(wskQb->isFlagExist(flag))
                {
                    wskQb->updateLvlUser(username,flag);
                    QMessageBox::information(0,"Nadawanie uprawnień: Sukces","Uprawnienia zostały zmienione");
                }
                else
                {
                    QMessageBox::critical(0,"Błąd","Taki poziom nie istnieje!");
                }
            }
            else
            {
                QMessageBox::critical(0,"Błąd","Nie podano poziomu uprawnień");
            }
        }
        else
        {
            QMessageBox::warning(0,"Błąd","Użytkownik o podanej nazwie nie istnieje w bazie.");
        }
    }
    else
    {
        QMessageBox::critical(0,"Błąd","Nie podano nazwy użytkownika!");
    }
}
