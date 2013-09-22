#include "../include/Event.h"
#include "../include/EventDispatcher.h"

using namespace std;

using namespace eigen;
using namespace event;

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
}

void EventDispatcher::dispatchEvent(Event *event)
{
    vector< void (*)(Event*) > *listeners = findEventListeners(event->type);

    if (listeners) {
        for (vector< void (*)(Event*) >::iterator it = listeners->begin(); it != listeners->end(); (*it)(event), ++it);
    }
}

bool EventDispatcher::hasEventListener(string type, void (*listener)(Event*))
{
    return false;
}

void EventDispatcher::addEventListener(string type, void (*listener)(Event*))
{
    vector< void (*)(Event*) > *listeners = findEventListeners(type);

    if (!listeners)
    {
        listeners = new std::vector< void (*)(Event*) >;
        eventListenerList[type] = listeners;
    }

    listeners->push_back(listener);
}

void EventDispatcher::removeEventListener(string type, void(*listener)(Event*))
{
    /*
    std::map< string, std::vector< void (*listener)(Event*) > >::iterator it = eventListenerList.find(type);

    if (it != eventListenerList.end())
    {
        std::vector< void (*listener)(Event*) > listeners = it.second;
        std::vector< void (*listener)(Event*) >::iterator func_it = listeners.begin();
        
        for (; func_it != listeners.end(); ++func_it)
        {
            if (listener == *func_it) break;
        }

        if (func_it != listeners.end()) listeners.erase(func_it);
    }
    */
}

vector< void (*)(Event*) > *EventDispatcher::findEventListeners(string type)
{
    map< string, vector< void (*)(Event*) >* >::iterator it = eventListenerList.find(type);

    if (it == eventListenerList.end())
    {
        return NULL;
    }
    else
    {
        return it->second;
    }
}
