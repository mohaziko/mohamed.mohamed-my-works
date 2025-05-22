#ifndef TEST_H
#define TEST_H

#include <QtTest/QTest>

class Test : public QObject {
    Q_OBJECT

public:
    explicit Test(QObject *parent=0);
private slots:
    void testadition();
    void testsubr();
    void testmulti();
    void testdivide();
    void testwurzel();
    void testwurzelklammeUndMulti();
    void testwurzelZero();
    void testWurzelDezimalwerten();
    void testWurzelM();
    void testSinRad();
    void testSinDeg();
    void testSinPi();

};

#endif // TEST_H
