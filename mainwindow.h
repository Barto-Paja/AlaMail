#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>

#include "mainwindow.h"
#include "querybank.h"
#include "profile.h"

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

private:
    Ui::MainWindow *ui;

    QueryBank *wskQb;
    Profile *form;
};

#endif // MAINWINDOW_H
