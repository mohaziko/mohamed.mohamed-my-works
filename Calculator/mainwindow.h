#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "anglefunctor.h"
#include <QMainWindow>
#include<QString>
#include <QMainWindow>
#include <QRegularExpression>
#include <complex>

using namespace std;
QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QString input;

void setAngleMode(AngleFunctor::Mode mode);


    Ui::MainWindow *ui;
    double zahl(const std::string &eingabe, size_t &index);
    double factor(const string &eingabe, size_t &index);
    double summand(const string &eingabe, size_t &index);
    double ausdruck(const string &eingabe, size_t &index);
    void check(const string &eingabe, size_t &index);
    double Rechner(string eingabe);
    std::complex<double> computeSquareRoot(double number);
    void setAngleFunctor(const AngleFunctor &newAngleFunctor);

private slots:


    void digitPressed();
    void ButtonPunktreleased();
    void ButtonklammerAufreleased();
    void ButtonklammerZureleased();
    void operationPressed();
    void ButtonClearreleased();
    void Buttonreturnreleased();
    void unaryOperationPressed();
    void ButtonGleichreleased();
    void updateModeDisplay();
    void cycleModePressed();
    void sinPressed();
    void piPressed();
private:
     AngleFunctor angleFunctor;

};
#endif // MAINWINDOW_H
