#include <string>

#include "../include/Event.h"

using namespace std;

using namespace eigen;
using namespace event;

Event::Event(string type):
    type(type)
{
}

Event::~Event()
{
}

