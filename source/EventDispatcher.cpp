#include "../include/Event.h"
#include "../include/EventDispatcher.h"

using namespace eigen::event;

EventDispatcher::EventDispatcher()
{
}

EventDispatcher::~EventDispatcher()
{
    for (
        map< string, vector< void (*)(Event*) >* >::iterator listeners = eventListenerList.begin();
        listeners != eventListenerList.end();
        delete listeners->second, ++listeners
    );
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
    vector < void (*)(Event*) > *listeners = findEventListeners(type);

    if (listeners)
    {
        for (vector< void (*)(Event*) >::iterator it = listeners->begin(); it != listeners->end(); ++it)
        {
            if (*it == listener) return true;
        }
    }

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

bool EventDispatcher::removeEventListener(string type, void(*listener)(Event*))
{
    vector < void (*)(Event*) > *listeners = findEventListeners(type);

    if (listeners)
    {
        vector< void (*)(Event*) >::iterator func = listeners->begin();

        for (; func != listeners->end(); ++func)
        {
            if (*func == listener) break;
        }

        if (func != listeners->end())
        {
            listeners->erase(func);

            return true;
        }
    }

    return false;
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
