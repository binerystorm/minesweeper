#include <vector>
#include <functional>

class EventArg
{
public:
    static const EventArg empty;
};

typedef std::function<void(EventArg)> action;

class Event
{
public:
    Event() = default;
    void subAction(action act);
    void unsubAction(action act);
    void trigger(EventArg arg);
private:
    std::vector<action> subscriptions;

};


