#ifndef MENUVALUE_TEXT_H
#define MENUVALUE_TEXT_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <string.h>

#include "menudefines.h"

class TextMenuValue : public AbstractMenuValue
{
public:
	TextMenuValue(const char* text)
		: m_text(text)
		, m_len(strlen(text) + 1)
	{
	}
	virtual ~TextMenuValue() override { }

	virtual bool isReadOnly() const override { return true; }
	virtual bool next() override { return false; }
	virtual bool previous() override { return false; }
	virtual void apply() override { }
	virtual void cancel() override { }
	virtual void toChar(char* out, int size) const override
	{
		memcpy_s(out, size, m_text, m_len);
	}
private:
	const char* m_text;
	const int m_len;

};

#endif // MENUVALUE_TEXT_H
