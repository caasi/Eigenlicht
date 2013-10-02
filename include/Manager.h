#ifndef __EIGENLICHT_MANAGER_H__
#define __EIGENLICHT_MANAGER_H__

#include <ISceneManager.h>
#include <IMeshSceneNode.h>
#include "IComponent.h"
#include "ComponentContainer.h"

using namespace irr;
using namespace scene;

namespace eigen
{

class Manager : public interactable::ComponentContainer
{
public:
    static const int ID_COMPONENT = 1 << 8;

    Manager(ISceneManager*);

    ~Manager();

    virtual void add(IComponent*);

    virtual bool remove(IComponent*);

    void update();

    ISceneNode *getTestNode() { return testNode; }
private:
    ISceneManager *smgr;
    IMeshSceneNode *testNode;
};

}
#endif
