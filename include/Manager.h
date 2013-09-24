#ifndef __EIGEN_MANAGER_H__
#define __EIGEN_MANAGER_H__

#include <ISceneManager.h>
#include <ISceneNode.h>
#include "IComponent.h"
#include "ComponentContainer.h"

using namespace irr;
using namespace scene;

namespace eigen
{

class Manager : public interactable::ComponentContainer
{
public:
    Manager(ISceneManager*);

    ~Manager();

    virtual void add(IComponent*);

    virtual bool remove(IComponent*);

    void update();
private:
    ISceneManager *smgr;
    ISceneNode *testNode;
};

}
#endif
