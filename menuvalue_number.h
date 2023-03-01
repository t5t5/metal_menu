#ifndef MENUVALUE_NUMBER_H
#define MENUVALUE_NUMBER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <limits>
#include <string.h>

#include "menuvalue_abstractsimple.h"
#include "parameter_number.h"

template <typename T>
class NumberMenuValue : public AbstractSimpleMenuValue
{
public:
	NumberMenuValue(
			NumberParameter<T>* valuePtr,
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
		if (!m_isEditing) { m_value = m_valuePtr->value(); }
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
		if (!m_isEditing) { m_value = m_valuePtr->value(); }
		auto v = m_value - m_step;
		if (v >= m_min) {
			m_isEditing = true;
			m_value = v;
			return true;
		} else {
			return false;
		}
	}
	virtual bool apply() override
	{
		bool changed = m_valuePtr->setValue(m_value);
		m_isEditing = false;
		return changed;
	}
	virtual void cancel() override
	{
		m_isEditing = false;
	}

	virtual void toChar(char* out, int size) const override
	{
		T v = m_isEditing ? m_value : m_valuePtr->value();
		snprintf(out, size, "%d", v);
	}

	virtual Parameter* parameter() const override { return m_valuePtr; }
private:
	NumberParameter<T>* m_valuePtr;
	T m_value;
	T m_step;
	T m_min;
	T m_max;
	bool m_isEditing;
};

#endif // NUMBERMENUVALUE_H
