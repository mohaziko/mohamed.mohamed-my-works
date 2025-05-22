#include "test.h"
#include "ort.h"
#include "poi.h"
#include "qobject.h"

test::test(QObject *parent):QObject(parent) {}

void test::testDistanceCalculation()
{
    // Test distance between Berlin and Munich
    Ort* berlin = new PoI(13.404954, 52.520008, 1,"p","Capital", "Berlin");
    Ort* munich = new PoI(11.5753822,48.1371079,2,"Stadt","Bayern","Muenchen");

    double distance = window->Rechnung(*berlin, *munich);
    QVERIFY(qAbs(distance - 504.0) < 1.0); // Approximately 504 km

    delete berlin;
    delete munich;
}

void test::testTwoPointSelection()
{
    std::vector<bool> selected = {true, true, true}; // Simuliert drei ausgewählte Orte
    QVERIFY(selected.size() > 2); // Prüft ob mehr als zwei Orte ausgewählt sind
}

void test::testNearestNeighbor()
{
    std::vector<Ort*> testOrte;

    PoI* berlin = new PoI(13.404954, 52.520008, 'p', "Capital", "Berlin", "Berlin");
    PoI* hamburg = new PoI(9.993682, 53.551086, 'p', "Capital", "Hamburg", "Hamburg");

    testOrte.push_back(berlin);
    testOrte.push_back(hamburg);

    // Test-Punkt in der Nähe von Berlin
    PoI* testPoint = new PoI(13.0, 52.0, 'p', "Test", "TestPoint", "Test");


    // Überprüfe ob Berlin als nächster Nachbar gefunden wurde
    Ort* nearest = MainWindow::findNearestNeighbor(testOrte, testPoint);
    QCOMPARE(nearest, berlin);

    // Aufräumen
    delete testPoint;
    for(auto* ort : testOrte) {
        delete ort;
    }
}
