#ifndef __EIGENLICHT_EVENT_H__
#define __EIGENLICHT_EVENT_H__

#include <string>

using namespace std;

namespace eigen
{
namespace event
{

class EventDispatcher;

struct Event
{
    Event(std::string);

    virtual ~Event();

    std::string type;

    EventDispatcher *target;
};

}
}

#endif
