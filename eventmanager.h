#ifndef EVENTMANAGER_H
#define EVENTMANAGER_H
#include "event.h"
#include <vector>



class EventManager
{
public:
    EventManager();
    int numberofacceptedevents;
    int numberofneutralevents;
    int numberofrejectedevents;
    //void setCurrentevent(Event * currentevent_);
    //Event * getCurrentevent();
    void setPotentialevent(Event * potentialevent_);
    Event * getPotentialevent();
    void setTargetedevent(Event * targetedevent_);
    Event * getTargetedevent();


    void addEventtolist(Event* event);
    void addEventtoacceptedlist(Event* event);
    void incrementNumberofacceptedevents();
    void decrementNumberofacceptedevents();
    void incrementNumberofrejectedevents();
    void decrementNumberofrejectedevents();
    void incrementNumberofneutralevents();
    void decrementNumberofneutralevents();
    void sortEvents();



    void removeEventfromlist(Event* event);
    std::vector<Event*> eventlist;
    std::vector<Event*> acceptedeventlist;

    //Event* currentevent;
    Event* potentialevent;
    Event* targetedevent;
private:


};

#endif // EVENTMANAGER_H
