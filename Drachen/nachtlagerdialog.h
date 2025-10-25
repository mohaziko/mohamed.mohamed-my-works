#ifndef NACHTLAGERDIALOG_H
#define NACHTLAGERDIALOG_H

#include "nachtlager.h"
#include <QDialog>

namespace Ui {
class NachtlagerDialog;
}

class NachtlagerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit NachtlagerDialog(Nachtlager* nacht,QWidget *parent = nullptr);
    ~NachtlagerDialog();

private:
    Ui::NachtlagerDialog *ui;
    Nachtlager* nachtlager;

    void ladeDaten();
    void speichereDaten();

private slots:
    void accept() override;  // Wird bei OK gedrückt aufgerufen
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
};

#endif // NACHTLAGERDIALOG_H
