#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#define PI 3.14159

#include <QMainWindow>
#include "/usr/src/QT/Extras/qcustomplot/qcustomplot.h"    //QCustomPlot header files
#include <stdlib.h>
#include <math.h>
#include <string>
#include <sstream>
#include <iostream>
#include <QVector>
#include <QTextStream>
#include "filefunctions.h"
#include "plot.h"
#include <QLineEdit>
//Function prototypes for other .cpp's


struct Data
{
    QVector<double> x;
    QVector<double> y;
    int maxdatapoints;
    int Frequency;
    double Period;

    Data();
    double gety(double xx);
    double getx(double yy);
    double Integrate(double x1, double x2);

    void resize(int datapoints);
};

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    File file;
    Plot plot;
    Data data;
    QApplication * Qapp;
    int ybarrange;
    int xbarrange;
    int minimumpagestep = 100;
    double cursor1pos, cursor2pos;      //position of cursors...
    int xCursorWidth = 10;


private slots:

    void on_xbar_sliderMoved(int position);

    void on_xbar_valueChanged(int value);

    void on_xZoomIn_clicked();

    void on_xZoomOut_clicked();

    void on_yZoomIn_clicked();

    void on_yZoomOut_clicked();

    void on_ybar_sliderMoved(int position);

    void on_ybar_valueChanged(int value);

    void on_actionOpen_File_triggered();

    void mousePress(QMouseEvent* click);



    void on_Accept_Event_clicked();

private:
    Ui::MainWindow *ui;
    //QCustomPlot* customPlot;

};

#endif // MAINWINDOW_H
