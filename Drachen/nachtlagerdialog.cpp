#include "nachtlagerdialog.h"
#include "nachtlager.h"
#include "ui_nachtlagerdialog.h"
#include<QDialogButtonBox>

NachtlagerDialog::NachtlagerDialog(Nachtlager *nacht, QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::NachtlagerDialog),nachtlager(nacht)
{
    ui->setupUi(this);


setWindowTitle("Nachtlager bearbeiten");



// Verbinde OK/Cancel


}

NachtlagerDialog::~NachtlagerDialog()
{
    delete ui;
}


void NachtlagerDialog::ladeDaten()
{
    if (!nachtlager) return;

    // Felder mit bestehenden Werten füllen
    ui->labelOrt->setText(QString::fromStdString(nachtlager->getLagerOrt()));
    ui->lineEditAbfahrt->setText(QString::fromStdString(nachtlager->getAbfahrt()));
    ui->lineEditAnkunft->setText(QString::fromStdString(nachtlager->getAnkunft()));
    ui->doubleSpinBoxPreis->setValue(nachtlager->getPreis());
    ui->doubleSpinBoxRuhelevel->setValue(nachtlager->getRuheLevel());

    // Unterkunftstyp vorauswählen
    QString unterkunft = QString::fromStdString(nachtlager->getUnterkunftsTyp());
    int index = ui->comboBoxUnterkunft->findText(unterkunft);
    if (index >= 0)
        ui->comboBoxUnterkunft->setCurrentIndex(index);

}


void NachtlagerDialog::speichereDaten()
{
    if (!nachtlager) return;

    // Änderungen ins Originalobjekt zurückschreiben
    nachtlager->setLagerOrt(ui->lineEditOrt->text().toStdString());
    nachtlager->setAbfahrt(ui->labelAbfahrt->text().toStdString());
    nachtlager->setAnkunft(ui->labelAnkunft->text().toStdString());
    nachtlager->setPreis(ui->doubleSpinBoxRuhelevel->value());
    nachtlager->setRuheLevel(ui->doubleSpinBoxRuhelevel->value());
    nachtlager->setUnterkunftsTyp(ui->comboBoxUnterkunft->currentText().toStdString());
}


// Diese Methode wird im accept()-Slot aufgerufen
void NachtlagerDialog::accept()
{
    speichereDaten();
    QDialog::accept();
}

void NachtlagerDialog::on_buttonBox_accepted()
{
    accept();
}


void NachtlagerDialog::on_buttonBox_rejected()
{
    reject();
}

