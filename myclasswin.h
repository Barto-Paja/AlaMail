#ifndef MYCLASSWIN_H
#define MYCLASSWIN_H

#include <QMainWindow>

namespace Ui {
class MyClassWin;
}

class MyClassWin : public QMainWindow
{
    Q_OBJECT

public:
    explicit MyClassWin(QWidget *parent = 0);
    ~MyClassWin();

private:
    Ui::MyClassWin *ui;
};

#endif // MYCLASSWIN_H
