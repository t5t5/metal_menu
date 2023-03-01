#ifndef PARAMETER_HIPADDRESS_H
#define PARAMETER_HIPADDRESS_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include "parameter.h"

class IpAddressParameter : public Parameter
{
public:
	IpAddressParameter(uint8_t a, uint8_t b, uint8_t c, uint8_t d);
	virtual ~IpAddressParameter() override;

	const unsigned char* data() const;

	// Parameter interface
	virtual ParameterType type() const override;
	virtual int size() const override;
	virtual bool fromBytes(const char* buffer, int size) override;
	virtual bool toBytes(char* buffer, int size) const override;
private:
	static const int ElementCount = 4;
	unsigned char m_ip[ElementCount];
};

#endif // PARAMETER_HIPADDRESS_H
