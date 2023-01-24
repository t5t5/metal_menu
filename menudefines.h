#ifndef MENUDEFINES_H
#define MENUDEFINES_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>
#include <limits>

using MenuId = char;
//using MenuFunction = std::function<void(int)>;

const MenuId NoMenuId = -1;
const MenuId RootMenuId = 0;

class AbstractMenuValue
{
public:
	virtual ~AbstractMenuValue() { }

	virtual bool next() = 0;
	virtual bool previous() = 0;

	virtual void apply() = 0;
	virtual void cancel() = 0;

	virtual const char* toString() const = 0;
};

class MenuNoValue : public AbstractMenuValue
{
public:
	virtual ~MenuNoValue() override { }

	virtual bool next() override { return false; }
	virtual bool previous() override { return false; }
	virtual void apply() override { }
	virtual void cancel() override { }
	virtual const char* toString() const override { return nullptr; }
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
		, m_value(*valuePtr)
		, m_step(step)
		, m_min(min)
		, m_max(max)
	{ }
	virtual ~NumberMenuValue() override { }

	virtual bool next() override
	{
		auto v = m_value + m_step;
		if (v <= m_max) {
			m_value = v;
			return true;
		} else {
			return false;
		}
	}
	virtual bool previous() override
	{
		auto v = m_value - m_step;
		if (v >= m_min) {
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
			// TODO: event about update
		}
	}
	virtual void cancel() override
	{
		m_value = *m_valuePtr;
	}

	virtual const char* toString() const override { return nullptr; }
private:
	T* m_valuePtr;
	T m_value;
	T m_step;
	T m_min;
	T m_max;
};

struct MenuNode
{
	MenuId id;
	MenuId parentId;
	const char* name;
	AbstractMenuValue* value;
};

//struct MenuHandlerItem
//{
//	MenuFunction function;
//	MenuId id;

//	MenuHandlerItem(MenuId i, MenuFunction f) : function(f) , id(i) { }
//};

#endif // MENUNODE_H
