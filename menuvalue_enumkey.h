#ifndef MENUVALUE_ENUMKEY_H
#define MENUVALUE_ENUMKEY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menuvalue_abstractsimple.h"

template <typename T>
class EnumKeyMenuValue : public AbstractSimpleMenuValue
{
public:
	struct Item
	{
		T value;
		const char* text;
		const char* translate;
	};

	template <int N>
	EnumKeyMenuValue(T* valuePtr, const Item(& items)[N])
		: m_valuePtr(valuePtr)
		, m_value(T())
		, m_items(items)
		, m_count(N)
		, m_index(findIndex(*valuePtr))
		, m_isEditing(false)
	{
	}

	virtual ~EnumKeyMenuValue() override { }

	virtual bool next() override
	{
		if (!m_isEditing) { m_index = findIndex(*m_valuePtr); }
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
		if (!m_isEditing) { m_index = findIndex(*m_valuePtr); }
		int index = m_index - 1;
		if (index >= 0) {
			m_isEditing = true;
			m_index = index;
			return true;
		} else {
			return false;
		}
	}

	virtual void apply() override
	{
		auto value = m_items[m_index].value;
		if (value != *m_valuePtr) {
			*m_valuePtr = value;
		}
		m_isEditing = false;
	}

	virtual void cancel() override
	{
		m_isEditing = false;
	}

	virtual void toChar(char* out, int size) const override
	{
		int index = m_isEditing ? m_index : findIndex(*m_valuePtr);
		const char* src = (language == 0) ? m_items[index].text : m_items[index].translate;
		memcpy_s(out, size, src, strlen(src) + 1);
	}
private:
	int findIndex(T value) const
	{
		for (int index = 0; index < m_count; ++index) {
			if (m_items[index].value == value) { return index; }
		}
		return 0;
	}

	T* m_valuePtr;
	T m_value;
	const Item* m_items;
	int m_count;
	int m_index;
	bool m_isEditing;
};

#endif // MENUVALUE_ENUMKEY_H
