#include "eventmanager.h"

EventManager::EventManager()
{
    numberofacceptedevents = 0;
    numberofrejectedevents = 0;
    numberofneutralevents = 0;
}


void EventManager::addEventtolist(Event* event)
{
    eventlist.push_back(event);
    return;
}

void EventManager::removeEventfromlist(Event* event)
{
    eventlist.erase(eventlist.begin() + event->getIndex());
    return;
}

void EventManager::setPotentialevent(Event * potentialevent_)
{
    potentialevent = potentialevent_;
    return;
}

Event * EventManager::getPotentialevent()
{
    return potentialevent;
}

void EventManager::setTargetedevent(Event * targetedevent_)
{
    targetedevent = targetedevent_;
    return;
}

Event * EventManager::getTargetedevent()
{
    return targetedevent;
}

void EventManager::incrementNumberofacceptedevents()
{
    numberofacceptedevents = numberofacceptedevents + 1;
    return;
}

void EventManager::decrementNumberofacceptedevents()
{
    numberofacceptedevents = numberofacceptedevents - 1;
    return;
}

void EventManager::incrementNumberofneutralevents()
{
    numberofneutralevents = numberofneutralevents + 1;
    return;
}

void EventManager::decrementNumberofneutralevents()
{
    numberofneutralevents = numberofneutralevents - 1;
    return;
}

void EventManager::incrementNumberofrejectedevents()
{
    numberofrejectedevents = numberofrejectedevents + 1;
    return;
}

void EventManager::decrementNumberofrejectedevents()
{
    numberofrejectedevents = numberofrejectedevents - 1;
    return;
}

void EventManager::sortEvents()
{
    Event* temporaryevent;
    for( int i = 0; i < eventlist.size() - 1; i++ )
    {
        if( eventlist[i]->getStarttime() < eventlist[i + 1]->getStarttime() )
        {
            temporaryevent = eventlist[i];
            eventlist[i] = eventlist[i+1];
            eventlist[i+1] = temporaryevent;
        }
    }

    return;
}



