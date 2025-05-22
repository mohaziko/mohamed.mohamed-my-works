#include"mainwindow.h"
#include "ui_mainwindow.h"

#include<QDebug>
#include<QMessageBox>
#include <complex>
#include<istream>
#include<sstream>
using namespace std;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->Button_0, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_1, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_2, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_3, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_4, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_5, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_6, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_7, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_8, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_9, SIGNAL(released()), this, SLOT(digitPressed()));
    connect(ui->Button_divide, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Button_multiply, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Button_plus, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Button_minus, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->wurzel_button, SIGNAL(released()), this, SLOT(operationPressed()));
    connect(ui->Button_plusMinus, SIGNAL(released()), this, SLOT(unaryOperationPressed()));
    connect(ui->Button_percent, SIGNAL(released()), this, SLOT(unaryOperationPressed()));
    connect(ui->Button_KlammerAuf, SIGNAL(released()), this, SLOT(ButtonklammerAufreleased()));
    connect(ui->Button_KlammerZu, SIGNAL(released()), this, SLOT(ButtonklammerZureleased()));
    connect(ui->Button_Gleich, SIGNAL(released()), this, SLOT(ButtonGleichreleased()));
    connect(ui->Reset, SIGNAL(released()), this, SLOT(ButtonClearreleased()));
    connect(ui->Button_Erase, SIGNAL(released()), this, SLOT(Buttonreturnreleased()));
    connect(ui->Button_Dezimal, SIGNAL(released()), this, SLOT(ButtonPunktreleased()));
    connect(ui->sinButton,SIGNAL(released()), this,SLOT(sinPressed()));
    connect(ui->piButton, SIGNAL(released()), this,SLOT(piPressed()));
    connect(ui->modeButton, SIGNAL(released()), SLOT(cycleModePressed()));
    ui->label->setText("0");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setAngleMode(AngleFunctor::Mode mode)
{
     angleFunctor.setMode(mode);
}

void MainWindow::digitPressed()
{
    QString currentText = ui->label->text();

    if(currentText=="0"||currentText=="ERROR")
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender());

        if (button)
        {
            input =button->text();
            ui->label->setText(input);
        }
    }
    else
    {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        if (button)
        {
            input =currentText+ button->text();
            ui->label->setText(input);
        }
    }
}

void MainWindow::ButtonPunktreleased() //auto connect
{
    QString currentText = ui->label->text();

    // Initialisieren des QRegularExpression-Objekts
    static const QRegularExpression regEx("[^0-9]");

    // Prüfen, ob der letzte "Token" (Zahl) bereits einen Punkt enthält
    QStringList tokens = currentText.split(regEx, Qt::SkipEmptyParts);

    if (!tokens.isEmpty() && !tokens.last().contains('.'))
    {
        ui->label->setText(currentText + ".");
    }
    else
    {
        ui->label->setText(ui->label->text());  // Keine Änderung
    }
}

void MainWindow::ButtonklammerAufreleased() //auto connect
{
    ui->label->setText(ui->label->text()+"(");
}

void MainWindow::ButtonklammerZureleased() //auto connect
{
    ui->label->setText(ui->label->text()+")");
}

void MainWindow::operationPressed()
{
    QString currentText = ui->label->text();
    QPushButton* button = qobject_cast<QPushButton*>(sender());

    if (button)
    {
        QString buttonText = button->text();

        // Letztes Zeichen prüfen
        QChar lastChar = currentText[currentText.length() - 1];

        if (buttonText == "v")
        {
            // Prüfen, ob ein gültiger Ausdruck vorliegt
            if (lastChar.isDigit() || lastChar == ')')
            {
                // Fügt das Symbol √ ein
                input =  "v";
            }
            else
            {
                input = currentText + "v";
            }
            ui->label->setText(input);
        }
        else if (lastChar.isDigit() || lastChar == ')')
        {
            // Füge Operator hinzu, wenn die letzte Eingabe gültig ist
            input = currentText + buttonText;
            ui->label->setText(input);
        }
    }
}

void MainWindow::ButtonClearreleased() //auto connect
{
    ui->label->setText("0");
}

void MainWindow::Buttonreturnreleased() //auto connect
{
    QString currentText=ui->label->text();

    if( !currentText.isEmpty())
    {
        currentText.chop(1);
        ui->label->setText(currentText);
    }
}

void MainWindow::unaryOperationPressed()
{
    QPushButton *button = qobject_cast<QPushButton *>(sender());
    if (!button)
        return;

    QString buttonText = button->text();
    double labelNumber = ui->label->text().toDouble();
    QString newLabel;

    if (buttonText == "+/-")
    {
        labelNumber = -labelNumber;
        newLabel = QString::number(labelNumber, 'g', 12);
        ui->label->setText(newLabel);
    }
    else if (buttonText == "%")
    {
        labelNumber *= 0.01;
        newLabel = QString::number(labelNumber, 'g', 15);
        ui->label->setText(newLabel);
    }
}

void MainWindow::ButtonGleichreleased()
{

    QString currentString=ui->label->text();
    string eingabe=currentString.toStdString();
    double result=Rechner(eingabe);

    QString newResult=QString::number(result,'g',15);
    ui->label->setText(newResult);

}

void MainWindow::updateModeDisplay()
{
    switch(angleFunctor.getMode()) {
    case AngleFunctor::Mode::RAD:
       ui-> modeButton->setText("RAD");
        break;
    case AngleFunctor::Mode::DEG:
        ui-> modeButton->setText("DEG");
        break;
    case AngleFunctor::Mode::GON:
       ui->  modeButton->setText("GON");
        break;
    }
}

void MainWindow::cycleModePressed()
{
    switch(angleFunctor.getMode()) {
    case AngleFunctor::Mode::RAD:
        angleFunctor.setMode(AngleFunctor::Mode::DEG);
        break;
    case AngleFunctor::Mode::DEG:
        angleFunctor.setMode(AngleFunctor::Mode::GON);
        break;
    case AngleFunctor::Mode::GON:
        angleFunctor.setMode(AngleFunctor::Mode::RAD);
        break;
    }
    updateModeDisplay();
}

void MainWindow::sinPressed()
{
    QString currentText = ui->label->text();
    ui->label->setText(currentText + "sin(");
}

void MainWindow::piPressed()
{
    QString currentText = ui->label->text();
    ui->label->setText(currentText + QString::number(M_PI));
}




double MainWindow::ausdruck(const string& eingabe, size_t& index)
{
    double result;
    if (index >= eingabe.length()) return 0;

    char zeichen = eingabe[index];

    if (zeichen == '-')
    {
        index++;
        check(eingabe, index);
        result = -summand(eingabe, index);
    }
    else
    {
        if (zeichen == '+')
        {
            index++;
            check(eingabe, index);
        }
        result = summand(eingabe, index);
    }

    while (eingabe[index] == '+' || eingabe[index] == '-')
    {
        char op = eingabe[index];
        index++;
        check(eingabe, index);

        if (op == '+')
            result += summand(eingabe, index);
        else
            result -= summand(eingabe, index);
    }

    return result;

}

void MainWindow::   check(const string& eingabe, size_t& index)
{
    if (index >= eingabe.length()) return; // Überprüfen, ob Index gültig ist
    char zeichen = eingabe[index];
    if ((zeichen < '0' || zeichen > '9') &&
        (zeichen != 'e' &&
         zeichen != '+' &&
         zeichen != '-' &&
         zeichen != '*' &&
         zeichen != '/' &&
         zeichen != '(' &&
         zeichen != ')' &&
         zeichen != '.' &&
         zeichen != 'v' &&

         zeichen != ' '))

    {

        index++;
    }

}

double MainWindow::Rechner(string eingabe)
{

    size_t index = 0; // Startindex
    double result = ausdruck(eingabe, index);

    // Fehlerbehandlung: Sicherstellen, dass der gesamte String verarbeitet wurde
    while (index < eingabe.length())
    {
        if (!isspace(eingabe[index]))
        {
            QMessageBox::information(this, "ERROR", "Ungültige Eingabe!");
            return 0;
        }
        index++;
    }

    return result;
}

std::complex<double> MainWindow::computeSquareRoot(double number)
{
    if (number < 0) {
        // Berechne die Wurzel für negative Zahlen als komplexe Zahl
        return std::sqrt(std::complex<double>(number, 0));
    } else {
        // Normale Berechnung für nicht-negative Zahlen
        return std::sqrt(number);
    }
}

double MainWindow::summand(const string& eingabe, size_t& index)
{
    double result = factor(eingabe, index);
    while (eingabe[index] == '*' || eingabe[index] == '/')
    {
        char op = eingabe[index];
        index++;
        check(eingabe, index);
        if (op == '*')
            result *= factor(eingabe, index);
        else
        {
            double tmp = factor(eingabe, index);
            if (tmp == 0)
                QMessageBox::information(this,"ERROR","Division durch null nicht möeglich");    //cout << "Division durch 0, Rechnung abgebrochen" << endl;
            else
                result /= tmp;
        }
    }
    return result;

}

double MainWindow::factor(const string& eingabe, size_t& index)
{
    // double result;
    // if (index >= eingabe.length()) return 0;

    // char zeichen = eingabe[index];

    // if (zeichen == '(')
    // {
    //     index++; // Öffnende Klammer überspringen
    //     check(eingabe, index);
    //     result = ausdruck(eingabe, index);

    //     if (eingabe[index] != ')') // Nach Ausdruck darf hier nur ')' kommen
    //         QMessageBox::information(this,"ERROR","Klammer  fehlt");   // cout << "Rechte Klammer fehlt!" << endl;
    //     else
    //         index++; // Schließende Klammer überspringen

    //     check(eingabe, index);
    // }else if(zeichen == 'v'){
    //     index++; // Wurzelsymbol überspringen
    //     check(eingabe, index);
    //     result = factor(eingabe, index); // Berechne die Wurzel des nächsten Faktors

    //     if (result < 0)
    //     {
    //         auto complexResult = computeSquareRoot(result);

    //         result=complexResult.imag();
    //         return result; // Realteil zurückgeben (je nach Anforderung)
//     {
//         result = sqrt(result);
//     }
// }else if(zeichen == '-'){
//     index++;
//     check(eingabe, index);
//     result = -factor(eingabe, index);
// }

// else
// { // Wenn kein Klammerausdruck, kann hier nur Zahl kommen
//     result = zahl(eingabe, index);
// }
// return result;

    double result;
    if (index >= eingabe.length()) return 0;

    char zeichen = eingabe[index];

    if (zeichen == 's' && eingabe.substr(index, 3) == "sin") {
        index += 3; // "sin" überspringen
        check(eingabe, index);
        if (eingabe[index] != '(') {
            QMessageBox::information(this,"ERROR","Klammer nach sin fehlt");
            return 0;
        }
        index++; // '(' überspringen
        result = ausdruck(eingabe, index);
        result = angleFunctor(result); // Winkelfunktion anwenden

        if (eingabe[index] != ')') {
            QMessageBox::information(this,"ERROR","Schließende Klammer nach sin fehlt");
            return 0;
        }
        index++; // ')' überspringen
        check(eingabe, index);
    }
    else if (zeichen == '(')
    {
        index++; // Öffnende Klammer überspringen
        check(eingabe, index);
        result = ausdruck(eingabe, index);

        if (eingabe[index] != ')') // Nach Ausdruck darf hier nur ')' kommen
            QMessageBox::information(this,"ERROR","Klammer  fehlt");
        else
            index++; // Schließende Klammer überspringen

        check(eingabe, index);
    }
    else if(zeichen == 'v'){
        index++; // Wurzelsymbol überspringen
        check(eingabe, index);
        result = factor(eingabe, index); // Berechne die Wurzel des nächsten Faktors

        if (result < 0)
        {
            auto complexResult = computeSquareRoot(result);
            result = complexResult.imag();
            return result;
        }
        {
            result = sqrt(result);
        }
    }
    else if(zeichen == '-'){
        index++;
        check(eingabe, index);
        result = -factor(eingabe, index);
    }
    else if(zeichen == 'p' || (zeichen == 'p' && index + 1 < eingabe.length() && eingabe[index + 1] == 'i')) {
        if(zeichen == 'p')
            index++;
        else
            index += 2; // "pi" überspringen
        result = M_PI;
        check(eingabe, index);
    }
    else
    { // Wenn kein Klammerausdruck, kann hier nur Zahl kommen
        result = zahl(eingabe, index);
    }
    return result;






}

double MainWindow::zahl(const string& eingabe, size_t& index)
{
    double result = 0;
    if (index >= eingabe.length()) return 0;

    while (isdigit(eingabe[index]))
    {
        result = 10 * result + (eingabe[index] - '0');
        index++;
        check(eingabe, index);
    }

    if (eingabe[index] == '.')
    {
        index++;
        check(eingabe, index);
        double nachkommastelle = 1.0;

        while (isdigit(eingabe[index]))
        {
            nachkommastelle *= 10.0;
            result = result + double(eingabe[index] - '0') / nachkommastelle;
            index++;
            check(eingabe, index);
        }
    }
    return result;

}
