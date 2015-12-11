#ifndef PLOT_H
#define PLOT_H
#include <QVector>
#include "/usr/src/QT/Extras/qcustomplot/qcustomplot.h"

//class QCustomPlot;

//struct Data;



class Plot
{
public:
    Plot();
    QCustomPlot* custplot;
    //Data* data;

    double xrangelow, xrangehigh, xrange, xfullrangelow, xfullrangehigh, xfullrange;
    double yrangelow, yrangehigh, yrange, yfullrangelow, yfullrangehigh, yfullrange;


    //void SetupAxes();

    //void SetFullView();

    void SetupPlot(double period, int totaldatapoints, double maxy, double miny);

    void SetPlotRange( int xbarvalue, int ybarvalue, int xbarrange, int ybarrange );

    void SetData( QVector<double> x, QVector<double> y );





private:
    int MaxDataPoints;


};

#endif // PLOT_H
