#include "event.h"

Event::Event(int index_)
{
    acceptance = neutral;
    setIndex(index_);
}

int Event::getIndex()
{
    return index;
}

void Event::setIndex(int index_)
{
    index = index_;
    return;
}

double Event::getStarttime()
{
    return starttime;
}

double Event::getEndtime()
{
    return endtime;
}

double Event::getDuration()
{
    return duration;
}

void Event::setStarttime(double starttime_)
{
    starttime = starttime_;
    peakmanager.setEventstarttime(starttime);
    return;
}


void Event::setEndtime(double endtime_)
{
    endtime = endtime_;
    duration = endtime - starttime;
    peakmanager.setEventendtime(endtime);
    return;
}

void Event::setAmplitude(double amplitude_)
{
    amplitude = amplitude_;
    return;
}



AcceptanceState Event::getAcceptance()
{
    return acceptance;
}

void Event::setAcceptance(AcceptanceState acceptance_)
{
    acceptance = acceptance_;
    return;
}

void Event::setAccepted()
{
    acceptance = accepted;
    return;
}

void Event::setRejected()
{
    acceptance = rejected;
    return;
}




double Event::getAmplitude()
{
    return amplitude;
}

double Event::getLeftbaselineaverage()
{
    return leftbaselineaverage;
}

double Event::getLeftbaselinestddev()
{
    return leftbaselinestddev;
}

void Event::setLeftbaselineaverage(double leftbaselineaverage_)
{
    leftbaselineaverage = leftbaselineaverage_;
    return;
}

void Event::setLeftbaselinestddev(double leftbaselinestddev_)
{
    leftbaselinestddev = leftbaselinestddev_;
    return;
}

