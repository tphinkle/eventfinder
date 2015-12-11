#ifndef DATA_H
#define DATA_H
#include <QVector>
class Data
{


public:


    QVector<double> x;
    QVector<double> y;




    Data();
    double gety(int xx);
    double gety(double xx);
    double getx(double yy);
    int getIndex(double xx);
    double Integrate(double x1, double x2);
    void resize(int datapoints);
    void SetupData(double period, int frequency, int maxdatapoints_);
    int getMaxDataPoints();



private:
    int maxdatapoints;
    int frequency;
    double period;


};





#endif // DATA_H
