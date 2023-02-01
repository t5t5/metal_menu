#ifndef MENUACTION_FUNCTION_H
#define MENUACTION_FUNCTION_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <functional>

#include "menudefines.h"

class FunctionMenuAction : public AbstractMenuAction
{
public:
	FunctionMenuAction() { }
	FunctionMenuAction(std::function<void()> function)
		: m_function(function)
	{
	}

	void setFunction(std::function<void()> function)
	{
		m_function = function;
	}

	virtual ~FunctionMenuAction() override { }

	virtual void call() override
	{
		if (m_function) { m_function(); }
	}
private:
	std::function<void()> m_function;
};

#endif // MENUACTION_FUNCTION_H
