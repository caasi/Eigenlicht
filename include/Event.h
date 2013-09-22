#ifndef __EIGENLICHT_EVENT_H__
#define __EIGENLICHT_EVENT_H__

#include <string>

using namespace std;

namespace eigen
{
namespace event
{

struct Event
{
    Event(string);

    ~Event();

    string type;
};

}
}

#endif
