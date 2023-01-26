#ifndef MENUDEFINES_H
#define MENUDEFINES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>
#include <limits>

using MenuId = char;
const MenuId NoMenuId = -1;
const MenuId RootMenuId = 0;

extern int language;

class AbstractMenuValue
{
public:
	virtual ~AbstractMenuValue() { }

	virtual bool next() = 0;
	virtual bool previous() = 0;

	virtual void apply() = 0;
	virtual void cancel() = 0;

	virtual void toChar(char* out, int size) const = 0;
};

class AbstractMenuAction
{
public:
	virtual ~AbstractMenuAction() { }

	virtual void call() = 0;
};

class MenuNoValue : public AbstractMenuValue
{
public:
	virtual ~MenuNoValue() override { }

	virtual bool next() override { return false; }
	virtual bool previous() override { return false; }
	virtual void apply() override { }
	virtual void cancel() override { }
	virtual void toChar(char*, int) const override { }
};

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

template <typename T>
class EnumMenuValue : public AbstractMenuValue
{
public:
	struct EnumItem { T item; };

	EnumMenuValue(T* valuePtr, const EnumItem* item, int N)
		: m_valuePtr(valuePtr)
		, m_value(T())
		, m_items(item)
		, m_count(N)
		, m_index(findIndex(*valuePtr))
//		, m_items(reinterpret_cast<const EnumItem*>(&items[0]))
		, m_isEditing(false)
	{
	}

	virtual ~EnumMenuValue() override { }

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
		auto value = m_items[m_index].item;
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
		T v = m_isEditing
			? m_items[m_index].item
			: *m_valuePtr;
		snprintf(out, size, "%d", static_cast<int>(v));
	}
private:
	int findIndex(T value) const
	{
		for (int index = 0; index < m_count; ++index) {
			if (m_items[index].item == value) { return index; }
		}
		return 0;
	}

	T* m_valuePtr;
	T m_value;
	const EnumItem* m_items;
	int m_count;
	int m_index;
	bool m_isEditing;
};

template <typename T>
class SetValueMenuAction : public AbstractMenuAction
{
public:
	SetValueMenuAction(
			T* valuePtr,
			T value)
		: m_valuePtr(valuePtr)
		, m_value(value)
	{
	}

	virtual ~SetValueMenuAction() override { }

	virtual void call() override
	{
		*m_valuePtr = m_value;
	}
private:
	T* m_valuePtr;
	T m_value;
};

struct MenuNode
{
	MenuId id;
	MenuId parentId;
	const char* name;
	const char* translate;
	AbstractMenuValue* value;
	AbstractMenuAction* action;
};

#endif // MENUNODE_H
