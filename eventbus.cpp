#include "eventbus.h"

#include <cstring>

#include "eventhandler.h"

EventBus::EventBus()
{
	std::memset(&subscribers, 0, sizeof(subscribers));
}

EventBus::~EventBus()
{
}

bool EventBus::subscribe(Event::EventType eventType, EventHandler* handler)
{
	if (!handler) { return false; }
	for (int i = 0; i < MaxSubscribers; ++i) {
		if (subscribers[i].handler == nullptr) {
			subscribers[i].handler = handler;
			subscribers[i].eventType = eventType;
			return true;
		}
	}
	return false;
}

void EventBus::unsubscribe(EventHandler* handler)
{
	if (!handler) { return; }
	for (int i = 0; i < MaxSubscribers; ++i) {
		if (subscribers[i].handler == handler) {
			subscribers[i].handler = nullptr;
			subscribers[i].eventType = Event::EventUndefined;
		}
	}
}

void EventBus::sendEvent(Event* e, const EventHandler* sender /* = nullptr */) const
{
	if (!e) { return; }
	for (int i = 0; i < MaxSubscribers; ++i) {
		if (subscribers[i].eventType == e->eventType()) {
			if (subscribers[i].handler != sender) {
				subscribers[i].handler->event(e);
			}
		}
	}
}

EventBus& eventBus()
{
	static EventBus instance;
	return instance;
}
