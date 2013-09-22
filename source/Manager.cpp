#include "../include/Manager.h"
#include "../include/Event.h"

using namespace eigen;
using namespace event;

Manager::Manager():
    IReferenceCounted()
{
}

Manager::~Manager()
{
}

void Manager::update()
{
    dispatchEvent(new Event("update"));
}
