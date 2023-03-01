#ifndef MENUACTION_SETVALUE_NUMBER_H
#define MENUACTION_SETVALUE_NUMBER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "eventbus.h"
#include "menudefines.h"
#include "parameter_number.h"

template <typename T>
class SetValueNumberMenuAction : public AbstractMenuAction
{
public:
	SetValueNumberMenuAction(
			NumberParameter<T>* valuePtr,
			T value)
		: m_valuePtr(valuePtr)
		, m_value(value)
	{
	}

	virtual ~SetValueNumberMenuAction() override { }

	virtual void call() override
	{
		bool changed = m_valuePtr->setValue(m_value);
		if (changed) {
			ParameterChangedEvent e(m_valuePtr);
			eventBus().sendEvent(&e);
		}
	}
private:
	NumberParameter<T>* m_valuePtr;
	T m_value;
};



#endif // MENUACTION_SETVALUE_NUMBER_H
