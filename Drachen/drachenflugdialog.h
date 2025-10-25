#ifndef DRACHENFLUGDIALOG_H
#define DRACHENFLUGDIALOG_H

#include "drachenflug.h"
#include <QDialog>

namespace Ui {
class DrachenflugDialog;
}

class DrachenflugDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrachenflugDialog(Drachenflug* f,QWidget *parent = nullptr);
    ~DrachenflugDialog();

private slots:
    void accept() override;
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::DrachenflugDialog *ui;
    Drachenflug* flug;

    void ladeDaten();
    void speichereDaten();
};

#endif // DRACHENFLUGDIALOG_H
