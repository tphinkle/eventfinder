#include "peakmanager.h"
#include <vector>
#ifndef EVENT_H
#define EVENT_H

enum AcceptanceState {accepted, rejected, neutral};

class Event
{
public:
    Event(int index_);
    PeakManager peakmanager;
    std::vector<double>*x;
    std::vector<double>*y;


    double getStarttime();
    double getEndtime();
    double getAmplitude();
    double getDuration();
    int getIndex();
    double getLeftbaselineaverage();
    double getLeftbaselinestddev();
    AcceptanceState getAcceptance();

    void setStarttime(double starttime_);
    void setEndtime(double endtime_);
    void setAmplitude(double amplitude_);
    void setIndex(int index_);
    void setLeftbaselineaverage(double leftbaselineaverage);
    void setLeftbaselinestddev(double leftbaselinestddev);
    void setAcceptance(AcceptanceState acceptancestate_);
    void setAccepted();
    void setRejected();

private:
    double starttime;
    double endtime;
    double duration;
    double amplitude;
    int index;
    double leftbaselineaverage;
    double leftbaselinestddev;
    AcceptanceState acceptance;






};

#endif // EVENT_H
