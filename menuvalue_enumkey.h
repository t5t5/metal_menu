#ifndef MENUVALUE_ENUMKEY_H
#define MENUVALUE_ENUMKEY_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menuvalue_abstractsimple.h"
#include "parameters.h"

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
	EnumKeyMenuValue(NumberParameter<T>* valuePtr, const Item(& items)[N])
		: m_valuePtr(valuePtr)
		, m_value(T())
		, m_items(items)
		, m_count(N)
		, m_index(findIndex(valuePtr->value()))
		, m_isEditing(false)
	{
	}

	virtual ~EnumKeyMenuValue() override { }

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
		auto value = m_items[m_index].value;
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
		int index = m_isEditing ? m_index : findIndex(m_valuePtr->value());
		const char* src = (language->value() == 0) ? m_items[index].text : m_items[index].translate;
		memcpy_s(out, size, src, strlen(src) + 1);
	}

	virtual Parameter* parameter() const override
	{
		return m_valuePtr;
	}
private:
	int findIndex(T value) const
	{
		for (int index = 0; index < m_count; ++index) {
			if (m_items[index].value == value) { return index; }
		}
		return 0;
	}

	NumberParameter<T>* m_valuePtr;
	T m_value;
	const Item* m_items;
	int m_count;
	int m_index;
	bool m_isEditing;
};

#endif // MENUVALUE_ENUMKEY_H
