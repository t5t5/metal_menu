#ifndef EVENTBUS_H
#define EVENTBUS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "event.h"

class EventHandler;
class EventSender;

class EventBus
{
	friend class EventHandler;
	friend class EventSender;
public:
	EventBus();
	~EventBus();

	void sendEvent(Event* event, const EventHandler* sender = nullptr) const;
private:
	bool subscribe(Event::EventType eventType, EventHandler* handler);
	void unsubscribe(EventHandler* handler);

	struct Subscriber
	{
		EventHandler* handler;
		Event::EventType eventType;
	};
	static const int MaxSubscribers = 128;
	Subscriber subscribers[MaxSubscribers];
};

EventBus& eventBus();

#endif // EVENTBUS_H
