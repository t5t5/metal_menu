#include "menuvalue_ip.h"

static const int ElementCount = 4;

IpMenuValue::IpMenuValue(IpAddressParameter* valuePtr)
	: m_ipPtr(valuePtr)
	, m_index(0)
	, m_isEditing(false)
	, m_isChanged(false)
{
}

bool IpMenuValue::up()
{
	if (!m_isEditing) { copyValue(); }
	int v = m_ip[m_index];
	if (v < 255) {
		++v;
		m_isChanged = true;
		m_isEditing = true;
		m_ip[m_index] = v;
		return true;
	}
	return false;
}

bool IpMenuValue::down()
{
	if (!m_isEditing) { copyValue(); }
	int v = m_ip[m_index];
	if (v > 0) {
		--v;
		m_isChanged = true;
		m_isEditing = true;
		m_ip[m_index] = v;
		return true;
	}
	return false;
}

bool IpMenuValue::left()
{
	// кнопка влево - значение не меняет, управляет курсором
	if (m_index) {
		if (!m_isEditing) { copyValue(); }
		--m_index;
		m_isEditing = true;
		return true;
	}
	return false;
}

bool IpMenuValue::right()
{
	// кнопка вправо - значение не меняет, управляет курсором
	if (m_index != (ElementCount - 1)) {
		if (!m_isEditing) { copyValue(); }
		++m_index;
		m_isEditing = true;
		return true;
	}
	return false;
}

bool IpMenuValue::apply()
{
	bool changed = m_isChanged;
	if (changed) {
		m_ipPtr->fromBytes(reinterpret_cast<char*>(m_ip), ElementCount);
	}
	m_isEditing = false;
	m_isChanged = false;
	return changed;
}

void IpMenuValue::cancel()
{
	m_isEditing = false;
	m_isChanged = false;
}

int numToString(int num, char* out, int size)
{
	if (size == 0) { return 0; }
	const int bufSize = 10;
	char buf[bufSize];
	int pos = bufSize - 1;
	do {
		int digit = num % 10;
		num /= 10;
		buf[pos--] = digit + '0';
	} while ((pos >= 0) && num);
	int digits = bufSize - (pos + 1);
	int bytes = size < digits ? size : digits;
	memcpy(out, &buf[pos + 1], bytes);
	if (bytes < size) { out[bytes] = 0; }
	return bytes;
}

void IpMenuValue::toChar(char* out, int size) const
{
	// >192<.168.100.123 : 4*3 (digits) + 3 (dots) + 2 (braces) + 1 (zero) = 18 chars max
	const unsigned char* ip = m_isEditing ? m_ip : m_ipPtr->data();
	int position = 0;
	for (int i = 0; i < ElementCount; ++i) {
		if (i == m_index) {
			if (position == size) { break; }
			out[position++] = '>';
		}
		int s = numToString(ip[i], out + position, size - position);
		position += s;
		if (i == m_index) {
			if (position == size) { break; }
			out[position++] = '<';
		}
		if (i < (ElementCount - 1)) {
			if (position == size) { break; }
			out[position++] = '.';
		}
	}
	if (position < size) {
		out[position] = 0;
	}
}

Parameter* IpMenuValue::parameter() const
{
	return m_ipPtr;
}

void IpMenuValue::copyValue()
{
	m_ipPtr->toBytes(reinterpret_cast<char*>(m_ip), ElementCount);
	m_isChanged = false;
}
