#include "../include/Event.h"

using namespace eigen::event;

Event::Event(string type):
    type(type),
    target(NULL)
{
}

Event::~Event()
{
    target = NULL;
}

