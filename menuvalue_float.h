#ifndef MENUVALUE_FLOAT_H
#define MENUVALUE_FLOAT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menuvalue_abstractsimple.h"

class FloatMenuValue : public AbstractSimpleMenuValue
{
public:
	FloatMenuValue(const float* valuePtr)
		: m_valuePtr(valuePtr)
	{
	}
	virtual ~FloatMenuValue() override { }

	virtual bool isReadOnly() const override { return true; }

	virtual bool next() override { return false; }
	virtual bool previous() override { return false; }

	virtual void apply() override { }
	virtual void cancel() override { }

	virtual void toChar(char* out, int size) const override
	{
		snprintf(out, size, "%.2f", *m_valuePtr);
	}
private:
	const float* m_valuePtr;
};

#endif // MENUVALUE_FLOAT_H
