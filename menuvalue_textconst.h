#ifndef MENUVALUE_TEXTCONST_H
#define MENUVALUE_TEXTCONST_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menuvalue_abstractsimple.h"

class ConstTextMenuValue : public AbstractSimpleMenuValue
{
public:
	ConstTextMenuValue(const char* text)
		: m_text(text)
		, m_len(strlen(text) + 1)
	{
	}
	virtual ~ConstTextMenuValue() override { }

	virtual bool isReadOnly() const override { return true; }

	virtual bool next() override { return false; }
	virtual bool previous() override { return false; }

	virtual bool apply() override { return false; }
	virtual void cancel() override { }

	virtual void toChar(char* out, int size) const override
	{
		memcpy_s(out, size, m_text, m_len);
	}

	virtual Parameter* parameter() const override { return nullptr; }
private:
	const char* m_text;
	const int m_len;


};

#endif // MENUVALUE_TEXTCONST_H
