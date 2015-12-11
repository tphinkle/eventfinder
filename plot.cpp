#include "plot.h"
#include <stdlib.h>


Plot::Plot()
{};


void Plot::SetupPlot(double period, int totaldatapoints, double maxy, double miny)
{

    custplot->addGraph();
    custplot->xAxis->setLabel("t (s)");
    custplot->yAxis->setLabel("I (pA)");

    xrangelow = 0;
    xrangehigh = .005;
    xrange = xrangehigh - xrangelow;
    xfullrangelow = 0;
    xfullrangehigh = period*(totaldatapoints - 1);
    xfullrange = period*totaldatapoints;


    yfullrangehigh = maxy + 0.5*(maxy - miny);
    yfullrangelow = miny - 0.5*(maxy - miny);
    yfullrange = yfullrangehigh - yfullrangelow;

    yrangelow = miny;
    yrangehigh = maxy;
    yrange = yrangehigh - yrangelow;


    return;
};


void Plot::SetPlotRange( int xbarvalue, int ybarvalue, int xbarrange, int ybarrange )
{
    xrangelow = (xfullrangehigh - xfullrangelow)*xbarvalue/xbarrange;
    xrangehigh = xrangelow + xrange;
    yrangelow = (yfullrangehigh - yfullrangelow)*ybarvalue/ybarrange;
    yrangehigh = yrangelow + yrange;
    custplot->xAxis->setRange(xrangelow, xrangehigh);
    custplot->yAxis->setRange(yrangelow, yrangehigh);
};


void Plot::SetData( QVector<double> x, QVector<double> y )
{
        custplot->graph(0)->setData(x, y);
        custplot->replot();
}
