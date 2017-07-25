#include "profile.h"
#include "ui_profile.h"

Profile::Profile(QWidget *parent, QString vLogin) :
    QWidget(parent),
    ui(new Ui::Profile)
{
    ui->setupUi(this);
    wskQb = new QueryBank;

    wskQb->setLogin(vLogin);
    LoadProfile();

    wskQb->isOpen();
    ui->lE_surname->setText(wskQb->userInfo(4));
}

Profile::~Profile()
{
    delete ui;
}

void Profile::LoadProfile()
{
//    QString stream = wskQb->userInfo(1);
//    ui->lE_username->setText(stream);
//    ui->lE_surname->setText(wskQb->userInfo(2));
//    ui->lE_name->setText(wskQb->userInfo(3));
//    ui->lE_email->setText(wskQb->userInfo(4));
}
