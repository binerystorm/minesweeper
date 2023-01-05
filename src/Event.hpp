#include <vector>
#include <functional>

#ifndef __EVENT_H__
#define __EVENT_H__

class EventArg
{
public:
    virtual ~EventArg(){};
};

typedef std::function<void(EventArg*)> action;

class Event
{
public:
    Event() = default;
    void subAction(action act);
    void unsubAction(action act);
    void trigger(EventArg* arg);
private:
    std::vector<action> subscriptions;

};
#endif // __EVENT_H__


