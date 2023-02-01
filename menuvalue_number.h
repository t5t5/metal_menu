#ifndef MENUVALUE_NUMBER_H
#define MENUVALUE_NUMBER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <limits>
#include <string.h>

#include "menudefines.h"

template <typename T>
class NumberMenuValue : public AbstractMenuValue
{
public:
	NumberMenuValue(
			T* valuePtr,
			T step = 1,
			T min = std::numeric_limits<T>::min(),
			T max = std::numeric_limits<T>::max())
		: m_valuePtr(valuePtr)
		, m_value(T())
		, m_step(step)
		, m_min(min)
		, m_max(max)
		, m_isEditing(false)
	{ }
	virtual ~NumberMenuValue() override { }

	virtual bool next() override
	{
		if (!m_isEditing) { m_value = *m_valuePtr; }
		auto v = m_value + m_step;
		if (v <= m_max) {
			m_isEditing = true;
			m_value = v;
			return true;
		} else {
			return false;
		}
	}
	virtual bool previous() override
	{
		if (!m_isEditing) { m_value = *m_valuePtr; }
		auto v = m_value - m_step;
		if (v >= m_min) {
			m_isEditing = true;
			m_value = v;
			return true;
		} else {
			return false;
		}
	}
	virtual void apply() override
	{
		if (m_value != *m_valuePtr) {
			*m_valuePtr = m_value;
		}
		m_isEditing = false;
	}
	virtual void cancel() override
	{
		m_isEditing = false;
	}

	virtual void toChar(char* out, int size) const override
	{
		T v = m_isEditing ? m_value : *m_valuePtr;
		snprintf(out, size, "%d", v);
	}
private:
	T* m_valuePtr;
	T m_value;
	T m_step;
	T m_min;
	T m_max;
	bool m_isEditing;
};

#endif // NUMBERMENUVALUE_H
