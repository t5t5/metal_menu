#ifndef PARAMETER_NUMBER_H
#define PARAMETER_NUMBER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <cstring>

#include "parameter.h"

template <typename T>
class NumberParameter : public Parameter
{
public:
	NumberParameter(T value = T()) : m_value(value) { };
	virtual ~NumberParameter() override { }

	// получить текущее значение
	inline T value() const { return m_value; }
	// установить значение
	// если значение изменено, должен быть уведомлен протокол обмена
	inline bool setValue(T value)
	{
		bool changed = m_value != value;
		if (changed) { m_value = value; }
		return changed;
	}

	// Parameter interface
	virtual ParameterType type() const override { return ParameterTraits<T>::type; } ;
	virtual int size() const override { return sizeof(T); }
	virtual bool fromBytes(const char* buffer, int size) override
	{
		if (sizeof(T) > size) { return false; }
		T v;
		memcpy(&v, buffer, sizeof(T));
		bool changed = m_value != v;
		if (changed) { m_value = v; }
		return changed;
	}
	virtual bool toBytes(char* buffer, int size) const override
	{
		if (sizeof(T) > size) { return false; }
		memcpy(buffer, &m_value, sizeof(T));
		return true;
	}
private:
	T m_value;
};

#endif // PARAMETER_NUMBER_H
