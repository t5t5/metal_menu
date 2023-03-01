#ifndef MENUVALUE_FLOATCONST_H
#define MENUVALUE_FLOATCONST_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menuvalue_abstractsimple.h"
#include "parameter_number.h"

class ConstFloatMenuValue : public AbstractSimpleMenuValue
{
public:
	ConstFloatMenuValue(NumberParameter<float>* valuePtr)
		: m_valuePtr(valuePtr)
	{
	}
	virtual ~ConstFloatMenuValue() override { }

	virtual bool isReadOnly() const override { return true; }

	virtual bool next() override { return false; }
	virtual bool previous() override { return false; }

	virtual bool apply() override { return false; }
	virtual void cancel() override { }

	virtual void toChar(char* out, int size) const override
	{
		snprintf(out, size, "%.2f", m_valuePtr->value());
	}

	virtual Parameter* parameter() const override
	{
		return m_valuePtr;
	}

private:
	NumberParameter<float>* m_valuePtr;
};

#endif // MENUVALUE_FLOATCONST_H
