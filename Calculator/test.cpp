#include "test.h"
#include "mainwindow.h"


Test::Test(QObject *parent):QObject(parent)
{

}

void Test::testadition()
{
    MainWindow calculator;
    QCOMPARE(calculator.Rechner("2+3"), 5.0);
}

void Test::testsubr()
{
    MainWindow calculator;
     QCOMPARE(calculator.Rechner("10-4"), 6.0);
}

void Test::testmulti()
{
    MainWindow calculator;
     QCOMPARE(calculator.Rechner("3*4"), 12);
}

void Test::testdivide()
{
    MainWindow calculator;
     QCOMPARE(calculator.Rechner("8/2"), 4.0);
}

void Test::testwurzel()
{
    MainWindow calculator;
    QCOMPARE(calculator.Rechner("v9"), 3.0);
}

void Test::testwurzelklammeUndMulti()
{
    MainWindow calculator;
 QCOMPARE(calculator.Rechner("v(4*4)"), 4.0);
}

void Test::testwurzelZero()
{
    MainWindow calculator;
 QCOMPARE(calculator.Rechner("v0"), 0.0);
}

void Test::testWurzelDezimalwerten()
{
 MainWindow calculator;
    QCOMPARE(calculator.Rechner("v2.25"), 1.5);
}

void Test::testWurzelM()
{
     MainWindow calculator;
     QCOMPARE(calculator.Rechner("v(2-18)"), 4.0);

}

void Test::testSinRad()
{
    MainWindow calculator;
    QCOMPARE(qRound(calculator.Rechner("sin(1.5707963267948966)") * 1000) / 1000.0, 1.0);
}

void Test::testSinDeg()
{
    MainWindow calculator;
    calculator.setAngleMode(AngleFunctor::Mode::DEG);
    QCOMPARE(qRound(calculator.Rechner("sin(90)") * 1000) / 1000.0, 1.0);
    //QCOMPARE(calculator.Rechner("sin(90)"),1.0);
}

void Test::testSinPi()
{
    MainWindow calculator;
    QCOMPARE(qRound(calculator.Rechner("sin(3.141592653589793)") * 1000) / 1000.0, 0.0);
}










