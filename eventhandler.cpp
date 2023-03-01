#include "eventhandler.h"

#include "eventbus.h"

EventHandler::EventHandler()
{
}

EventHandler::~EventHandler()
{
}

bool EventHandler::subscribe(Event::EventType eventType)
{
	return eventBus().subscribe(eventType, this);
}

void EventHandler::unsubscribe()
{
	eventBus().unsubscribe(this);
}

void EventHandler::sendEvent(Event* e) const
{
	eventBus().sendEvent(e, this);
}
