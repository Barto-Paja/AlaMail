#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "mainwindow.h"
#include "querybank.h"
#include "profile.h"
#include "myclasswin.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_pushButton_clicked();
    void on_Profile_clicked();

    void on_My_class_clicked();

private:
    Ui::MainWindow *ui;

    QueryBank *wskQb;
    Profile *form;
    MyClassWin *form2;
};

#endif // MAINWINDOW_H
