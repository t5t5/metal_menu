#ifndef EVENT_H
#define EVENT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menumodelindex.h"

class Event
{
public:
	enum EventType
	{
		EventUndefined			= 0,
		EventKey,
		EventParameterChanged,
		EventModelItemChanged,
	};

	Event(EventType eventType) : m_eventType(eventType) { }
	virtual ~Event() { }

	inline EventType eventType() const { return m_eventType; }
private:
	EventType m_eventType;
};

// ------------------------------------------------------------------------

class Parameter;

class ParameterChangedEvent : public Event
{
public:
	ParameterChangedEvent() : Event(EventParameterChanged) { }
	ParameterChangedEvent(Parameter* p)
		: Event(EventParameterChanged)
		, m_parameter(p)
	{ }
	virtual ~ParameterChangedEvent() override { }

	Parameter* parameter() const { return m_parameter; }
	void setParameter(Parameter* p) { m_parameter = p; }
private:
	Parameter* m_parameter = nullptr;
};

// ------------------------------------------------------------------------

class MenuItemChangedEvent : public Event
{
public:
	MenuItemChangedEvent() : Event(EventModelItemChanged) { }
	MenuItemChangedEvent(const MenuModelIndex& index)
		: Event(EventModelItemChanged)
		, m_index(index)
	{ }
	virtual ~MenuItemChangedEvent() override { }

	MenuModelIndex index() const { return m_index; }
	void setIndex(const MenuModelIndex& index) { m_index = index; }
private:
	MenuModelIndex m_index;
};

// ------------------------------------------------------------------------

enum Key
{
	Up,
	Down,
	Left,
	Right,
	Forward,
	Backward,
};

class KeyEvent : public Event
{
public:
	KeyEvent() : Event(EventKey) { }
	KeyEvent(Key key)
		: Event(EventKey)
		, m_key(key)
	{ }
	virtual ~KeyEvent() override { }

	inline Key key() const { return m_key; }
	inline void setKey(Key key) { m_key = key; }
private:
	Key m_key;
};

// ------------------------------------------------------------------------

#endif // EVENT_H
