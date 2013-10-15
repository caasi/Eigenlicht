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

    virtual ~EventDispatcher();

    virtual void dispatchEvent(Event*);

    virtual bool hasEventListener(std::string, void (*listener)(Event*));

    virtual void addEventListener(std::string, void (*listener)(Event*));

    virtual bool removeEventListener(std::string, void (*listener)(Event*));

private:
    std::map< std::string, std::vector< void (*)(Event*) >* > eventListenerList;

    std::vector< void (*)(Event*) > *findEventListeners(std::string);
};

}
}

#endif
