#ifndef __EIGEN_MANAGER_H__
#define __EIGEN_MANAGER_H__

#include <IReferenceCounted.h>
#include "EventDispatcher.h"

namespace eigen
{

class Manager : public event::EventDispatcher, public irr::IReferenceCounted
{
public:
    Manager();

    ~Manager();

    void update();
};

}
#endif