#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<string>

#include"ort.h"
#include"myort.h"

#include<QScrollArea>
#include<vector>
#include<QRadioButton>
#include<QLabel>
#include<QGraphicsLineItem>

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

     int FindOrt( const string  Name);
     static Ort* findNearestNeighbor(const std::vector<Ort*>& orte, Ort* newOrt);
     static double Rechnung(const Ort& ort1, const Ort& ort2);
     static double Convert(double value);
     void Information(Ort *ort);
     void SchiebenExistierende();
     void SchiebenNewOrt();
     void connectMainRoadNetwork();
     void clearRouteLines();
private slots:
     void on_action_1_Ort_Anlegen_triggered();
     void on_action_2_Laden_triggered();
     void on_action_3_Speichern_triggered();
     void on_pushButton_alle_orten_clicked();
     void on_pushButton_Entfernung_clicked();
     void on_pushButton_information_clicked();
     void on_pushButton_Mein_Ort_clicked();
     void on_pushButton_Verschieben_clicked();
     void on_pushButton_ortLoschen_clicked();
     void on_pushButton_routing_clicked();
     void onBeendenClicked();

private:
     bool geladen=false;
     std::map<Ort*, std::vector<std::pair<Ort*, double>>> adjacencyList;

     void connectToNearestNeighbors(Ort* newOrt, int numNeighbors = 8);
     void deleteOrt(Ort* ort);
     void updateConnections(Ort* ort);
    struct RouteNode
    {
      RouteNode()
          : ort(nullptr), distance(std::numeric_limits<double>::max()), previous(nullptr), visited(false) {
      }
      Ort *ort;
      double distance;
      Ort *previous;
      bool visited;
    };
    void findRoute(Ort* start, Ort* end);
    bool areConnected(Ort* ort, QGraphicsLineItem* line);
    void clearRouteDisplay();
    std::vector<QGraphicsLineItem*> routeLines;

    QScrollArea* scrollArea;

    QWidget* mapContainer;
    Ort* findNearestNeighbor(Ort* newOrt);
    Ui::MainWindow *ui;
    const double gpsTopLeftX = 5.866;  // Längengrad (Longitude) des nordwestlichsten Punktes
    const double gpsTopLeftY = 55.058+0.3; // Breitengrad (Latitude) des nordwestlichsten Punktes

    const double gpsBottomRightX = 14.842+0.3;  // Längengrad (Longitude) des südöstlichsten Punktes ,plus peti a droite
    const double gpsBottomRightY = 48.051-0.8;  // Breitengrad (Latitude) des südöstlichsten Punktes,plus  grand dessans

    const int  WBerlin=765;
    const int HBerlin=422;

    int gpsToPixelX(double gpsX);
    int gpsToPixelY(double gpsY);

    int gpsToXBerlin(double gpsX);
    int gpsToYBerlin(double gpsY);

    const double LaenBerlin=13.3989367;
    const double BreitenBerlin=52.510885;
    void drawConnections();

    void AddRadioButton(const string& name,const double& Breitengrad,const double Laengengrad);

    vector<Ort*> MeinOrt;
    vector<QRadioButton*>MeinButton;
    vector<QLabel*> MeinLabel;
    MyOrt* myPosition=new MyOrt(8.6390052,49.87167,'p'," ",0,0," ","Hoschule Darmsatdt","Hoschule","Fachbereich Informatik");

    QGraphicsScene* scene;
    int pixW;
    int pixH;
    void showPosition(const double& Breitengrad,const double Laengengrad);

    std::vector<QGraphicsLineItem*> connectionLines;
};
#endif // MAINWINDOW_H
