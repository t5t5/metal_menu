#include "menuvalue_ip2.h"

static const int IpElementCount = 4;
static const int IpCharCount = IpElementCount * 3;

Ip2MenuValue::Ip2MenuValue(unsigned char* ip)
	: m_ipPtr(ip)
	, m_index(0)
	, m_isEditing(false)
	, m_isChanged(false)
{

}

bool Ip2MenuValue::up()
{
	if (!m_isEditing) { copyValue(); }

	int digit = getDigit(m_ip, m_index);
	if ((digit < 9) && setDigit(m_ip, m_index, digit + 1)) {
		m_isChanged = true;
		m_isEditing = true;
		return true;
	}
	return false;
}

bool Ip2MenuValue::down()
{
	if (!m_isEditing) { copyValue(); }
	int digit = getDigit(m_ip, m_index);
	if ((digit > 0) && setDigit(m_ip, m_index, digit - 1)) {
		m_isChanged = true;
		m_isEditing = true;
		return true;
	}
	return false;
}

bool Ip2MenuValue::left()
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

bool Ip2MenuValue::right()
{
	// кнопка вправо - значение не меняет, управляет курсором
	if (m_index != (IpCharCount - 1)) {
		if (!m_isEditing) { copyValue(); }
		++m_index;
		m_isEditing = true;
		return true;
	}
	return false;
}

void Ip2MenuValue::apply()
{
	if (m_isChanged) {
		memcpy_s(m_ipPtr, IpElementCount, m_ip, sizeof(m_ip));
	}
	m_isEditing = false;
	m_isChanged = false;
}

void Ip2MenuValue::cancel()
{
	m_isEditing = false;
	m_isChanged = false;
}

void Ip2MenuValue::toChar(char* out, int size) const
{
	// >192<.168.100.123 : 4*3 (digits) + 3 (dots) + 2 (braces) + 1 (zero) = 18 chars max
	const unsigned char* ip = m_isEditing ? m_ip : m_ipPtr;
	bool isDigit = false;
	int position = 0;
	for (int i = 0; i < IpCharCount; ++i) {
		if (i == m_index) {
			if (position == size) { break; }
			out[position++] = '>';
		}

		bool isLast;
		int digit = getDigit(ip, i, &isLast);
		isDigit = isDigit || (digit > 0) || isLast;
		digit = isDigit ? (digit + '0') : ' ';
		if (position == size) { break; }
		out[position++] = digit;

		if (i == m_index) {
			if (position == size) { break; }
			out[position++] = '<';
		}
		if ((i != (IpCharCount - 1)) && ((i % 3) == 2)) {
			if (position == size) { break; }
			out[position++] = '.';
			isDigit = false;
		}
	}
}

void Ip2MenuValue::copyValue()
{
	memcpy_s(m_ip, sizeof(m_ip), m_ipPtr, IpElementCount);
	m_isChanged = false;
}

int Ip2MenuValue::getDigit(const unsigned char* ip, int index, bool* isLast /* = nullptr */) const
{
	int digit = ip[index / 3];
	bool last = false;
	switch (index % 3) {
	case 0: digit /= 100; break;
	case 1: digit /= 10; digit %= 10; break;
	case 2: digit %= 10; last = true; break;
	}
	if (isLast) { *isLast = last; }
	return digit;
}

bool Ip2MenuValue::setDigit(unsigned char* ip, int index, int digit)
{
	int num = ip[index / 3];
	int n = num;
	switch (index % 3) {
	case 0: n = digit * 100 + n % 100; break;
	case 1: n = n / 100 * 100 + digit * 10 + n % 10; break;
	case 2: n = n / 10 * 10 + digit; break;
	}
	if ((n < 0) || (n > 255) || (n == num)) {
		return false;
	} else {
		ip[index / 3] = n;
		return true;
	}
}
