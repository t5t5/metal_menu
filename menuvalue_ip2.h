#ifndef IP2MENUVALUE_H
#define IP2MENUVALUE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"

class Ip2MenuValue : public AbstractMenuValue
{
public:
	Ip2MenuValue(unsigned char* ip);

	virtual bool up() override;
	virtual bool down() override;
	virtual bool left() override;
	virtual bool right() override;

	virtual void apply() override;
	virtual void cancel() override;

	virtual void toChar(char* out, int size) const override;
private:
	void copyValue();
	int getDigit(const unsigned char* ip, int index, bool* isLast = nullptr) const;
	bool setDigit(unsigned char* ip, int index, int digit);

	unsigned char* m_ipPtr;
	unsigned char m_ip[4];
	int m_index;
	bool m_isEditing;
	bool m_isChanged;
};

#endif // IP2MENUVALUE_H
