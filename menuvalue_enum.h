#ifndef MENUVALUE_ENUM_H
#define MENUVALUE_ENUM_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menuvalue_abstractsimple.h"
#include "parameter_number.h"

template <typename T>
class EnumMenuValue : public AbstractSimpleMenuValue
{
public:
	template <int N>
	EnumMenuValue(NumberParameter<T>* valuePtr, const T(& item)[N])
		: m_valuePtr(valuePtr)
		, m_value(T())
		, m_items(item)
		, m_count(N)
		, m_index(findIndex(valuePtr->value()))
		, m_isEditing(false)
	{
	}

	virtual ~EnumMenuValue() override { }

	virtual bool next() override
	{
		if (!m_isEditing) { m_index = findIndex(m_valuePtr->value()); }
		int index = m_index + 1;
		if (index < m_count) {
			m_isEditing = true;
			m_index = index;
			return true;
		} else {
			return false;
		}
	}

	virtual bool previous() override
	{
		if (!m_isEditing) { m_index = findIndex(m_valuePtr->value()); }
		int index = m_index - 1;
		if (index >= 0) {
			m_isEditing = true;
			m_index = index;
			return true;
		} else {
			return false;
		}
	}

	virtual bool apply() override
	{
		auto value = m_items[m_index];
		bool changed = m_valuePtr->setValue(value);
		m_isEditing = false;
		return changed;
	}

	virtual void cancel() override
	{
		m_isEditing = false;
	}

	virtual void toChar(char* out, int size) const override
	{
		T v = m_isEditing
			? m_items[m_index]
			: m_valuePtr->value();
		snprintf(out, size, "%d", static_cast<int>(v));
	}

	virtual Parameter* parameter() const override
	{
		return m_valuePtr;
	}
private:
	int findIndex(T value) const
	{
		for (int index = 0; index < m_count; ++index) {
			if (m_items[index] == value) { return index; }
		}
		return 0;
	}

	NumberParameter<T>* m_valuePtr;
	T m_value;
	const T* m_items;
	int m_count;
	int m_index;
	bool m_isEditing;
};

#endif // MENUVALUE_ENUM_H
