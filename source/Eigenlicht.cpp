#include "../include/Eigenlicht.h"
#include "../include/Event.h"

using namespace eigen;
using namespace event;

Eigenlicht::Eigenlicht()
{
}

Eigenlicht::~Eigenlicht()
{
}

void Eigenlicht::update()
{
    dispatchEvent(new Event("update"));
}
