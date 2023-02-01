#ifndef MENUVALUE_ABSTRACTSIMPLE_H
#define MENUVALUE_ABSTRACTSIMPLE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

class AbstractSimpleMenuValue : public AbstractMenuValue
{
public:
	virtual ~AbstractSimpleMenuValue() { }

	virtual bool up() override { return next(); }
	virtual bool down() override { return previous(); }
	virtual bool left() override { return previous(); }
	virtual bool right() override { return next(); }
protected:
	virtual bool next() = 0;
	virtual bool previous() = 0;
};

#endif // MENUVALUE_ABSTRACTSIMPLE_H
