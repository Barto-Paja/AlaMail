#ifndef F_DODAJNAUCZYCIELA_H
#define F_DODAJNAUCZYCIELA_H

#include <QDialog>

namespace Ui {
class F_DodajNauczyciela;
}

class F_DodajNauczyciela : public QDialog
{
    Q_OBJECT

public:
    explicit F_DodajNauczyciela(QWidget *parent = 0);
    ~F_DodajNauczyciela();

private:
    Ui::F_DodajNauczyciela *ui;
};

#endif // F_DODAJNAUCZYCIELA_H
