#ifndef __EIGENLICHT_GUI_MANAGER_H__
#define __EIGENLICHT_GUI_MANAGER_H__

#include <map>
#include <vector>
#include <line3d.h>
#include <IReferenceCounted.h>
#include <ISceneManager.h>
#include <ISceneCollisionManager.h>
#include <IMeshSceneNode.h>
#include "EventDispatcher.h"
#include "IComponent.h"

using namespace std;

using namespace irr;
using namespace scene;

using namespace eigen;
using namespace event;
using namespace interactable;

namespace eigen
{

class GUIManager : public IComponent
{
public:
    static const int ID_COMPONENT = 1 << 8;

    GUIManager(ISceneManager*);

    ~GUIManager();

    void add(IComponent*);

    bool remove(IComponent*);

    void add(core::line3df*);

    /**
     * bubbleUP
     **
     * I need this method, because the tree is managed by scene node,
     * and I have to loop up component from that tree
     */
    void bubbleUp(ISceneNode*, Event*);

    void update();
private:
    ISceneManager *smgr;
    ISceneCollisionManager *collmgr;

    map<ISceneNode*, IComponent*> components;
    vector<core::line3df*> lines;
};

}
#endif
