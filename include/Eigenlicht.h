#ifndef __EIGENLICHT_H__
#define __EIGENLICHT_H__

#include "EventDispatcher.h"

namespace eigen
{

class Eigenlicht : public event::EventDispatcher
{
public:
    Eigenlicht();

    ~Eigenlicht();

    void update();
};

}
#endif
