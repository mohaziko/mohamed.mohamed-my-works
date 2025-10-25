#include "drachenflugdialog.h"
#include "ui_drachenflugdialog.h"

DrachenflugDialog::DrachenflugDialog(Drachenflug *f, QWidget *parent)
    : QDialog(parent),ui(new Ui::DrachenflugDialog)
    , flug(f)
{
    ui->setupUi(this);
    setWindowTitle("DrachenFlug bearbeiten");
}

DrachenflugDialog::~DrachenflugDialog()
{
    delete ui;
}

void DrachenflugDialog::accept()
{
    speichereDaten();
    QDialog::accept();
}

void DrachenflugDialog::on_buttonBox_accepted()
{
    accept();
}


void DrachenflugDialog::on_buttonBox_rejected()
{
    reject();
}

void DrachenflugDialog::ladeDaten()
{
    if (!flug) return;

    // Felder mit bestehenden Werten füllen
    ui->label_ziel->setText(QString::fromStdString(flug->getZiel()));
    QDate abfahrt = QDate::fromString(QString::fromStdString(flug->getAbfahrt()), "dd.MM.yyyy");
    ui->dateEdit->setDate(abfahrt);
    QDate ankunft = QDate::fromString(QString::fromStdString(flug->getAnkunft()), "dd.MM.yyyy");
    ui->dateEdit->setDate(ankunft);

    ui->spinBox->setValue(flug->getPreis());
    ui->spinBox_2->setValue(flug->getEntfernung());



}

void DrachenflugDialog::speichereDaten()
{
    if (!flug) return;

    // Änderungen ins Originalobjekt zurückschreiben
    flug->setZiel(ui->lineEdit->text().toStdString());
    flug->setAbfahrt(ui->dateEdit->date().toString("dd.MM.yyyy").toStdString());
   flug->setAnkunft(ui->dateEdit_2->date().toString("dd.MM.yyyy").toStdString());
    flug->setPreis(ui->spinBox->value());
    flug->setEntfernung(ui->spinBox_2->value());

}

