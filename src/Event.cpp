#include "Event.hpp"

void Event::subAction(action act)
{
    subscriptions.push_back(act);
}

void Event::unsubAction(action act)
{
    subscriptions.pop_back();
}

void Event::trigger(EventArg arg)
{
    for(action act : subscriptions)
    {
        act(arg);
    }
}
