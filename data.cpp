#include "data.h"

Data::Data()
{
    //maxdatapoints = 10000000; //100000 normally
}

void Data::SetupData(double period_, int frequency_, int maxdatapoints_)
{
    period = period_;
    frequency = frequency_;
    maxdatapoints = maxdatapoints_;
    resize(maxdatapoints);

}

void Data::resize( int datapoints )
{
    x.resize(datapoints);
    y.resize(datapoints);
    return;
}

int Data::getIndex(double xx)
{
    int errorreturnvalue = -1;
    double starttime = x[0];
    int index;

    index = (int) ((xx - starttime)/period);

    if( index >= maxdatapoints || index < 0 )
    {
        return errorreturnvalue;
    }

    return index;
}

double Data::gety (int xx )
{
    if( xx < 0 || xx > maxdatapoints )
    {
        return 0;
    }

    else
    {
        return y[xx];
    }
}

double Data::gety( double xx )
{
    int datapoint = (int) ((xx - x[0])*frequency);
    if( datapoint < 0 || datapoint > maxdatapoints )
    {
        return 0;
    }
    else
    {
        return y[datapoint];
    }
}

double Data::Integrate(double x1, double x2)
{
    int startdatapoint;
    int enddatapoint;
    if( x2 < x1 )
    {
        startdatapoint = (int) ((x2 - x[0])*frequency);
        enddatapoint = (int) ((x1 - x[0])*frequency);
    }
    else
    {
        startdatapoint = (int) ((x1 - x[0])*frequency);
        enddatapoint = (int) ((x2 - x[0])*frequency);
    }
    double average = 0;
    for( int i = startdatapoint; i < enddatapoint; i++ )
    {
        average = average + y[i];
    }
    average = average/(enddatapoint - startdatapoint);
    return average;
}

int Data::getMaxDataPoints()
{
    return maxdatapoints;
}
