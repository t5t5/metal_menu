#include "parameter_ipaddress.h"

#include <cstring>

IpAddressParameter::IpAddressParameter(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
{
	m_ip[0] = a;
	m_ip[1] = b;
	m_ip[2] = c;
	m_ip[3] = d;
}

IpAddressParameter::~IpAddressParameter()
{
}

const unsigned char* IpAddressParameter::data() const
{
	return m_ip;
}

Parameter::ParameterType IpAddressParameter::type() const
{
	return IpAddressType;
}

int IpAddressParameter::size() const
{
	return ElementCount;
}

bool IpAddressParameter::fromBytes(const char* buffer, int size)
{
	if (ElementCount > size) { return false; }
	bool changed = false;
	for (int i = 0; i < ElementCount; ++i) {
		changed |= (m_ip[i] != buffer[i]);
		m_ip[i] = buffer[i];
	}
	return changed;
}

bool IpAddressParameter::toBytes(char* buffer, int size) const
{
	if (ElementCount > size) { return false; }
	memcpy(buffer, m_ip, ElementCount);
	return true;
}
