#ifndef TEST_H
#define TEST_H

#include "mainwindow.h"
#include <QtTest/QTest>
class test:public QObject
{
     Q_OBJECT
public:
  explicit  test(QObject *parent=0);
    private slots:
  void testDistanceCalculation();
  void testTwoPointSelection();
  void testNearestNeighbor();
  private:
  MainWindow* window;
};

#endif // TEST_H
