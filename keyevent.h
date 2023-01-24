#ifndef KEYEVENT_H
#define KEYEVENT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

enum Key
{
	Up,
	Down,
	Left,
	Right,
	Forward,
	Backward,
};

class KeyEvent
{
public:
	KeyEvent(Key key);
	~KeyEvent() = default;

	inline Key key() const { return m_key; }
private:
	Key m_key;
};

#endif // KEYEVENT_H
