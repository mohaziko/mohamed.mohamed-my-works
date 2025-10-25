#ifndef SUCHERGEBNISDIALOG_H
#define SUCHERGEBNISDIALOG_H

#include "filmstudio.h"
#include <QDialog>
#include <QTableWidgetItem>

namespace Ui {
class SuchergebnisDialog;
}

class SuchergebnisDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SuchergebnisDialog(Filmstudio* s,QWidget *parent = nullptr);
    ~SuchergebnisDialog();
    void fillTableForPerson(const std::vector<Reiseplan *> &playerPlans, const std::vector<Reiseplan *> &passagierPlans, const QString &name);

    void addPlayerEntry(int nummer, const QString& name, const QString& beginn, const QString& ende, double preis);
    void addPassagierEntry(int nummer, const QString& name, const QString& beginn, const QString& ende, double preis);

    void setPassagierName(const QString& name);

    void starteSuche(const QString& name);

    void zeigeReiseabschnitte(int planN);

private slots:
    void on_pushButtonSuche_clicked();

    void on_WidgetReiseabschnitte_doubleClicked(const QModelIndex &index);

    void on_tableWidgetPlayer_itemDoubleClicked(QTableWidgetItem *item);

    void on_tableWidgetPassagier_itemDoubleClicked(QTableWidgetItem *item);

private:
    Ui::SuchergebnisDialog *ui;
     Filmstudio* studio;
    Reiseplan* aktuellerPlan = nullptr;
};

#endif // SUCHERGEBNISDIALOG_H
