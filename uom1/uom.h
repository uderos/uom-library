#ifndef UDR_UOM_H
#define UDR_UOM_H

namespace uom
{

template <int MASS, int LENGTH, int TIME, int CHARGE = 0, typename VALUE_T = double>
struct quantity_t
{
	quantity_t();
	quantity_t(const VALUE_T & init_value);
	quantity_t(const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & rv);

	static constexpr int mass() 	{ return MASS; }
	static constexpr int length() 	{ return LENGTH; }
	static constexpr int time() 	{ return TIME; }
	static constexpr int charge() 	{ return CHARGE; }

	VALUE_T value;
};

template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T = double>
quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>::quantity_t() :
	value(VALUE_T(0))
{
}

template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T>
quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>::quantity_t(const VALUE_T & init_value) :
	value(init_value)
{
}

template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T = double>
quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>::quantity_t(
		const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & rv) :
	value(rv.value)
{
}

#ifdef OUM_STRING_SUPPORT

//template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T, typename CHAR_T = char>
//std::basic_string<CHAR_T> to_string(const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & q)
//{
//	std::basic_stringstream<CHAR_T> oss;
//	oss << q.value;
//	if (MASS)
//	{
//		oss << ' ' << 'M';
//		if (MASS != 1) oss << MASS;
//	}
//	if (LENGTH)
//	{
//		oss << 'L';
//		if (LENGTH != 1) oss << LENGTH;
//	}
//	if (TIME)
//	{
//		oss << 'T';
//		if (TIME != 1) oss << TIME;
//	}
//
//	if (CHARGE)
//	{
//		oss << 'Q';
//		if (CHARGE != 1) oss << CHARGE;
//	}
//
//	return oss.str();
//}

template <typename QUANTITY_T, typename CHAR_T = char>
std::basic_string<CHAR_T> to_string(const QUANTITY_T & q)
{
	std::basic_stringstream<CHAR_T> oss;
	oss << q.value;
	if (QUANTITY_T::mass())
	{
		oss << ' ' << 'M';
		if (QUANTITY_T::mass() != 1) oss << QUANTITY_T::mass();
	}
	if (QUANTITY_T::length())
	{
		oss << 'L';
		if (QUANTITY_T::length() != 1) oss << QUANTITY_T::length();
	}
	if (QUANTITY_T::time())
	{
		oss << 'T';
		if (QUANTITY_T::time() != 1) oss << QUANTITY_T::time();
	}

	if (QUANTITY_T::charge())
	{
		oss << 'Q';
		if (QUANTITY_T::charge() != 1) oss << QUANTITY_T::charge();
	}

	return oss.str();
}

#endif // OUM_STRING_SUPPORT


template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T>
quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>
operator+(const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & a,
		  const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & b)
{
	return quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>(a.value + b.value);
}

template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T>
quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>
operator-(const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & a,
		  const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & b)
{
	return quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T>(a.value - b.value);
}

template <int MASS1, int LENGTH1, int TIME1, int CHARGE1, 
		  int MASS2, int LENGTH2, int TIME2, int CHARGE2,
		  typename VALUE_T>
quantity_t<MASS1 + MASS2, LENGTH1 + LENGTH2, TIME1 + TIME2, CHARGE1 + CHARGE2, VALUE_T>
operator*(const quantity_t<MASS1, LENGTH1, TIME1, CHARGE1, VALUE_T> & a,
		  const quantity_t<MASS2, LENGTH2, TIME2, CHARGE2, VALUE_T> & b)
{
	return quantity_t<MASS1 + MASS2, LENGTH1 + LENGTH2, TIME1 + TIME2, CHARGE1 + CHARGE2, VALUE_T>(
		a.value * b.value);
}

template <int MASS1, int LENGTH1, int TIME1, int CHARGE1, 
		  int MASS2, int LENGTH2, int TIME2, int CHARGE2,
		  typename VALUE_T>
quantity_t<MASS1 - MASS2, LENGTH1 - LENGTH2, TIME1 - TIME2, CHARGE1 - CHARGE2, VALUE_T>
operator/(const quantity_t<MASS1, LENGTH1, TIME1, CHARGE1, VALUE_T> & a,
		  const quantity_t<MASS2, LENGTH2, TIME2, CHARGE2, VALUE_T> & b)
{
	return quantity_t<MASS1 - MASS2, LENGTH1 - LENGTH2, TIME1 - TIME2, CHARGE1 - CHARGE2, VALUE_T>(
		a.value / b.value);
}

template <typename VALUE_T = double>
using length_t = quantity_t<0, 1, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using mass_t = quantity_t<1, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using time_t = quantity_t<0, 0, 1, 0, VALUE_T>;

template <typename VALUE_T = double>
using charge_t = quantity_t<0, 0, 0, 1, VALUE_T>;

template <typename VALUE_T = double>
using speed_t = quantity_t<0, 1, -1, 0, VALUE_T>;

template <typename VALUE_T = double>
using acceleration_t = quantity_t<0, 1, -2, 0, VALUE_T>;

template <typename VALUE_T = double>
using force_t = quantity_t<1, 1, -2, 0, VALUE_T>;

template <typename VALUE_T = double>
using energy_t = quantity_t<1, 2, -2, 0, VALUE_T>;


}; // namespace uom

#endif UDR_UOM_H
