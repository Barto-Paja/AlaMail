#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QString>
#include <QSqlQueryModel>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);

    QSqlDatabase db;

    QSqlQueryModel *model;
    QSqlQuery *trzymacz;

    void refreshStatus();

    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_actionLista_Pracownik_w_triggered();
    void on_actionLista_Uczni_w_triggered();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
