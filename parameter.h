#ifndef PARAMETER_H
#define PARAMETER_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <cstdint>

class Parameter
{
public:
	enum ParameterType
	{
		Int8Type,
		UInt8Type,
		Int16Type,
		UInt16Type,
		Int32Type,
		UInt32Type,
		FloatType,
		IpAddressType,
	};

	virtual ~Parameter() { };

	// тип параметра
	virtual ParameterType type() const = 0;
	// размер параметра
	virtual int size() const = 0;
	// установить значение параметра
	// вызывается, например, из протокола обмена
	// должны уведомляться все клиенты использующие этот параметр
	virtual bool fromBytes(const char* buffer, int size) = 0;
	// получить значение параметра
	// вызывается, например, из протокола обмена
	virtual bool toBytes(char* buffer, int size) const = 0;
};

template <typename T>
struct ParameterTraits;

template <>
struct ParameterTraits<int8_t>
{
	static constexpr Parameter::ParameterType type = Parameter::Int8Type;
};

template <>
struct ParameterTraits<uint8_t>
{
	static constexpr Parameter::ParameterType type = Parameter::UInt8Type;
};

template <>
struct ParameterTraits<int16_t>
{
	static constexpr Parameter::ParameterType type = Parameter::Int16Type;
};

template <>
struct ParameterTraits<uint16_t>
{
	static constexpr Parameter::ParameterType type = Parameter::UInt16Type;
};

template <>
struct ParameterTraits<int32_t>
{
	static constexpr Parameter::ParameterType type = Parameter::Int32Type;
};

template <>
struct ParameterTraits<uint32_t>
{
	static constexpr Parameter::ParameterType type = Parameter::UInt32Type;
};

template <>
struct ParameterTraits<float>
{
	static constexpr Parameter::ParameterType type = Parameter::FloatType;
};

#endif // PARAMETER_H
