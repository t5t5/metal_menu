#ifndef EVENTHANDLER_H
#define EVENTHANDLER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "event.h"

class EventHandler
{
public:
	EventHandler();
	virtual ~EventHandler();

	virtual void event(Event* event) = 0;
protected:
	bool subscribe(Event::EventType eventType);
	void unsubscribe();
	void sendEvent(Event* event) const;
};

#endif // EVENTHANDLER_H
