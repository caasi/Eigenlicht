#ifndef __EIGENLICHT_EVENT_DISPATCHER_H__
#define __EIGENLICHT_EVENT_DISPATCHER_H__

#include <string>
#include <vector>
#include <map>

using namespace std;

namespace eigen
{
namespace event
{

class Event;

class EventDispatcher
{
public:
    EventDispatcher();

    ~EventDispatcher();

    void dispatchEvent(Event*);

    bool hasEventListener(string, void (*listener)(Event*));

    void addEventListener(string, void (*listener)(Event*));

    void removeEventListener(string, void (*listener)(Event*));

private:
    map< string, vector< void (*)(Event*) >* > eventListenerList;

    vector< void (*)(Event*) > *findEventListeners(string);
};

}
}

#endif
