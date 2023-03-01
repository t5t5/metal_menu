#ifndef IPMENUVALUE_H
#define IPMENUVALUE_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "menudefines.h"
#include "parameter_ipaddress.h"

class IpMenuValue : public AbstractMenuValue
{
public:
	IpMenuValue(IpAddressParameter* valuePtr);

	virtual bool up() override;
	virtual bool down() override;
	virtual bool left() override;
	virtual bool right() override;

	virtual bool apply() override;
	virtual void cancel() override;

	virtual void toChar(char* out, int size) const override;

	virtual Parameter* parameter() const override;
private:
	void copyValue();

	IpAddressParameter* m_ipPtr;
	unsigned char m_ip[4];
	int m_index;
	bool m_isEditing;
	bool m_isChanged;

};

#endif // IPMENUVALUE_H
