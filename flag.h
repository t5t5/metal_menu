#ifndef FLAG_H
#define FLAG_H

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

#include <type_traits>

namespace detail
{

template <typename T, bool B = std::is_enum<T>::value>
struct is_enum_scoped : std::false_type {};

template <typename T>
struct is_enum_scoped<T, true>
	: std::integral_constant<bool,
		!std::is_convertible<T, typename std::underlying_type<T>::type>::value> {};

} // namespace detail

template <typename Enum>
class Flag
{
private:
	using underlying_value_type =
		typename std::conditional<
			detail::is_enum_scoped<Enum>::value,
			typename std::underlying_type<Enum>::type,
			Enum
		>::type;
	using mask_type = typename std::make_unsigned<underlying_value_type>::type;

	mask_type m_value;
public:
	inline Flag() : m_value(Enum()) { }
	inline Flag(Enum e) : m_value(e) { }
	inline Flag(mask_type e) : m_value(static_cast<Enum>(e)) { }

	Flag(const Flag& o) = default;
	Flag(Flag&& o) = default;

	inline mask_type value() const { return m_value; }

	template <Enum e>
	inline void setValue() { m_value = e; }
	inline void setValue(Enum e) { m_value = e; }
	inline void setValue(mask_type e) { m_value = e; }

	inline bool isEmpty() const { return m_value == 0; }

	inline bool test(Enum e) const
	{
		mask_type v = static_cast<mask_type>(e);
		return ((m_value & v) == v) && (e != 0 || m_value == v);
	}
	inline bool test(const Flag& e) const
	{
		return ((m_value & e.m_value) == e.m_value) &&
				(e.m_value != 0 || m_value == e.m_value);
	}

	inline operator mask_type() const { return m_value; }

	inline Flag& operator=(const Flag& e) = default;
	inline Flag& operator=(Flag&& e) = default;

	inline Flag& operator=(Enum e) { m_value = e; return *this; }
	inline Flag& operator=(mask_type e) { m_value = e; return *this; }

	inline Flag& operator&=(const Flag& e) { m_value &= e.m_value; return *this; }
	inline Flag& operator&=(Enum e) { m_value &= static_cast<mask_type>(e); return *this; }
	inline Flag& operator&=(mask_type e) { m_value &= e; return *this; }
	inline Flag& operator|=(const Flag& e) { m_value |= e.m_value; return *this; }
	inline Flag& operator|=(Enum e) { m_value |= static_cast<mask_type>(e); return *this; }
	inline Flag& operator|=(mask_type e) { m_value |= e; return *this; }
	inline Flag& operator^=(const Flag& e) { m_value ^= e.m_value; return *this; }
	inline Flag& operator^=(Enum e) { m_value ^= static_cast<mask_type>(e); return *this; }
	inline Flag& operator^=(mask_type e) { m_value ^= e; return *this; }
	inline Flag operator|(const Flag& e) const { return Flag(m_value | e.m_value); }
	inline Flag operator|(Enum e) const { return Flag(m_value | static_cast<mask_type>(e)); }
	inline Flag operator|(mask_type e) const { return Flag(m_value | e); }
	inline Flag operator^(const Flag& e) const { return Flag(m_value ^ e.m_value); }
	inline Flag operator^(Enum e) const { return Flag(m_value ^ static_cast<mask_type>(e)); }
	inline Flag operator^(mask_type e) const { return Flag(m_value ^ e); }
	inline Flag operator&(const Flag& e) const { return Flag(m_value & e.m_value); }
	inline Flag operator&(Enum e) const { return Flag(m_value & static_cast<mask_type>(e)); }
	inline Flag operator&(mask_type e) const { return Flag(m_value & e); }
	inline Flag operator~() const { return Flag(~m_value); }
};

#endif // FLAG_H
