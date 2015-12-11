#include "plot.h"

Plot::Plot()
{

};

void Plot::SetupPlot(double period, int totaldatapoints, double maxy, double miny)
{

    custplot->addGraph();
    custplot->xAxis->setLabel("t (s)");
    custplot->yAxis->setLabel("I (pA)");

    xrangelow = 0;
    xrangehigh = .005;
    xrange = xrangehigh - xrangelow;
    xfullrangelow = 0;
    xfullrangehigh = period*totaldatapoints;
    xfullrange = period*totaldatapoints;

    /*yrangelow = 0;
    yrangehigh = 100;
    yrange = yrangehigh - yrangelow;
    yfullrangehigh = 200;
    yfullrangelow = -200;
    yfullrange = yfullrangehigh - yfullrangelow;*/
    yrangelow = miny;
    yrangehigh = maxy;
    yrange = yrangehigh - yrangelow;
    yfullrangehigh = 30000;
    yfullrangelow = 0;
    yfullrange = yfullrangehigh - yfullrangelow;


};


void Plot::SetFullView()
{

};

