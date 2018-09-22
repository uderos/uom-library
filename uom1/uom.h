#ifndef UDR_UOM_H
#define UDR_UOM_H

#ifdef OUM_STRING_SUPPORT
#include <sstream>
#endif // OUM_STRING_SUPPORT

///////////////////////////////////////////////////////////////////////
// Some utility macros to help writing down the templates
///////////////////////////////////////////////////////////////////////

#define UOM_MEASURE_LIST MASS, LENGTH, TIME, ECURRENT, TEMPERATURE, AMOUNT, LUMINTENSITY
#define UOM_MEASURE_TEMPLATE_LIST	\
	int MASS,						\
	int LENGTH,						\
	int TIME,						\
	int ECURRENT,					\
	int TEMPERATURE,				\
	int AMOUNT,						\
	int LUMINTENSITY				\

#define UOM_MEASURE_LIST1 MASS1, LENGTH1, TIME1, ECURRENT1, TEMPERATURE1, AMOUNT1, LUMINOSITY1
#define UOM_MEASURE_TEMPLATE_LIST1	\
	int MASS1,						\
	int LENGTH1,					\
	int TIME1,						\
	int ECURRENT1,					\
	int TEMPERATURE1,				\
	int AMOUNT1,					\
	int LUMINOSITY1					\

#define UOM_MEASURE_LIST2 MASS2, LENGTH2, TIME2, ECURRENT2, TEMPERATURE2, AMOUNT2, LUMINOSITY2
#define UOM_MEASURE_TEMPLATE_LIST2	\
	int MASS2,						\
	int LENGTH2,					\
	int TIME2,						\
	int ECURRENT2,					\
	int TEMPERATURE2,				\
	int AMOUNT2,					\
	int LUMINOSITY2					\


namespace uom
{

///////////////////////////////////////////////////////////////////////
// The template structure used to define a qualtity with its dimentions
///////////////////////////////////////////////////////////////////////
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T = double>
struct quantity_t
{
	using value_type = VALUE_T;
	static constexpr int mass() { return MASS; }
	static constexpr int length() { return LENGTH; }
	static constexpr int time() { return TIME; }
	static constexpr int ecurrent() { return ECURRENT; }
	static constexpr int temperature() { return TEMPERATURE; }
	static constexpr int amount() { return AMOUNT; }
	static constexpr int luminosity() { return LUMINTENSITY; }

	quantity_t();
	quantity_t(const VALUE_T & init_value);
	quantity_t(const quantity_t<UOM_MEASURE_LIST, VALUE_T> & rv);

	VALUE_T value; // The *only* data member - keep it this way
};

// Default constructor
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T = double>
quantity_t<UOM_MEASURE_LIST, VALUE_T>::quantity_t() :
	value(VALUE_T(0))
{
	static_assert(
		sizeof(quantity_t<UOM_MEASURE_LIST, VALUE_T>) ==
		sizeof(quantity_t<UOM_MEASURE_LIST, VALUE_T>::value_type));
	static_assert(
		sizeof(quantity_t<UOM_MEASURE_LIST, VALUE_T>) ==
		sizeof(this->value));
}

// Non-default Constructor
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
quantity_t<UOM_MEASURE_LIST, VALUE_T>::quantity_t(const VALUE_T & init_value) :
	value(init_value)
{
}

// Copy constructor
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T = double>
quantity_t<UOM_MEASURE_LIST, VALUE_T>::quantity_t(
		const quantity_t<UOM_MEASURE_LIST, VALUE_T> & rv) :
	value(rv.value)
{
}

// Sum operator
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
inline
quantity_t<UOM_MEASURE_LIST, VALUE_T>
operator+(const quantity_t<UOM_MEASURE_LIST, VALUE_T> & a,
		  const quantity_t<UOM_MEASURE_LIST, VALUE_T> & b)
{
	return quantity_t<UOM_MEASURE_LIST, VALUE_T>(a.value + b.value);
}

// Subtraction operator
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
inline 
quantity_t<UOM_MEASURE_LIST, VALUE_T>
operator-(const quantity_t<UOM_MEASURE_LIST, VALUE_T> & a,
		  const quantity_t<UOM_MEASURE_LIST, VALUE_T> & b)
{
	return quantity_t<UOM_MEASURE_LIST, VALUE_T>(a.value - b.value);
}

// Multiplication of two quantities
template <UOM_MEASURE_TEMPLATE_LIST1, UOM_MEASURE_TEMPLATE_LIST2, typename VALUE_T>
inline
quantity_t<
	MASS1 + MASS2, 
	LENGTH1 + LENGTH2, 
	TIME1 + TIME2, 
	ECURRENT1 + ECURRENT2, 
	TEMPERATURE1 + TEMPERATURE2,
	AMOUNT1 + AMOUNT2,
	LUMINOSITY1 + LUMINOSITY2,
	VALUE_T>
operator*(const quantity_t<UOM_MEASURE_LIST1, VALUE_T> & a,
		  const quantity_t<UOM_MEASURE_LIST2, VALUE_T> & b)
{
	return quantity_t<
		MASS1 + MASS2,
		LENGTH1 + LENGTH2,
		TIME1 + TIME2,
		ECURRENT1 + ECURRENT2,
		TEMPERATURE1 + TEMPERATURE2,
		AMOUNT1 + AMOUNT2,
		LUMINOSITY1 + LUMINOSITY2,
		VALUE_T>(a.value * b.value);
}

// Multiplication: quantities times dimensionless factor
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
inline
quantity_t<UOM_MEASURE_LIST, VALUE_T>
operator*(const quantity_t<UOM_MEASURE_LIST, VALUE_T> & a, const VALUE_T & f)
{
	return quantity_t<UOM_MEASURE_LIST, VALUE_T>(a.value * f);
}

// Multiplication: dimensionless factor times quantities 
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
inline
quantity_t<UOM_MEASURE_LIST, VALUE_T>
operator*(const VALUE_T & f, const quantity_t<UOM_MEASURE_LIST, VALUE_T> & a)
	
{
	return quantity_t<UOM_MEASURE_LIST, VALUE_T>(f * a.value);
}

// Division: two quantities
template <UOM_MEASURE_TEMPLATE_LIST1, UOM_MEASURE_TEMPLATE_LIST2, typename VALUE_T>
inline
quantity_t<
	MASS1 - MASS2,
	LENGTH1 - LENGTH2,
	TIME1 - TIME2,
	ECURRENT1 - ECURRENT2,
	TEMPERATURE1 - TEMPERATURE2,
	AMOUNT1 - AMOUNT2,
	LUMINOSITY1 - LUMINOSITY2,
	VALUE_T>
	operator/(const quantity_t<UOM_MEASURE_LIST1, VALUE_T> & a,
			  const quantity_t<UOM_MEASURE_LIST2, VALUE_T> & b)
{
	return quantity_t<
		MASS1 - MASS2,
		LENGTH1 - LENGTH2,
		TIME1 - TIME2,
		ECURRENT1 - ECURRENT2,
		TEMPERATURE1 - TEMPERATURE2,
		AMOUNT1 - AMOUNT2,
		LUMINOSITY1 - LUMINOSITY2,
		VALUE_T>(a.value * b.value);
}

// Division: quantities by dimensionless factor 
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
inline
quantity_t<UOM_MEASURE_LIST, VALUE_T>
operator/(const quantity_t<UOM_MEASURE_LIST, VALUE_T> & a, const VALUE_T & f)
{
	return quantity_t<UOM_MEASURE_LIST, VALUE_T>(a.value / f);
}

// Division: dimensionless factor by quantities
template <UOM_MEASURE_TEMPLATE_LIST, typename VALUE_T>
inline
quantity_t<UOM_MEASURE_LIST, VALUE_T>
operator/(const VALUE_T & f, const quantity_t<UOM_MEASURE_LIST, VALUE_T> & a)

{
	return quantity_t<UOM_MEASURE_LIST, VALUE_T>(f / a.value);
}


///////////////////////////////////////////////////////////////////////
// Definitions of each SI base dimensions
///////////////////////////////////////////////////////////////////////
template <typename VALUE_T = double>
using mass_t = quantity_t<1, 0, 0, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using length_t = quantity_t<0, 1, 0, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using time_t = quantity_t<0, 0, 1, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using ecurrent_t = quantity_t<0, 0, 0, 1, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using temperature_t = quantity_t<0, 0, 0, 0, 1, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using amount_t = quantity_t<0, 0, 0, 0, 0, 1, 0, VALUE_T>;

template <typename VALUE_T = double>
using luminosity_t = quantity_t<0, 0, 0, 0, 0, 0, 1, VALUE_T>;


///////////////////////////////////////////////////////////////////////
// Definitions of some composite dimensions
///////////////////////////////////////////////////////////////////////

template <typename VALUE_T = double>
using speed_t = quantity_t<0, 1, -1, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using acceleration_t = quantity_t<0, 1, -2, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using force_t = quantity_t<1, 1, -2, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using energy_t = quantity_t<1, 2, -2, 0, 0, 0, 0, VALUE_T>;

template <typename VALUE_T = double>
using epotential_t = quantity_t<1, 2, -3, -1, 0, 0, 0, VALUE_T>;


///////////////////////////////////////////////////////////////////////
// Utility: string conversion
///////////////////////////////////////////////////////////////////////
#ifdef OUM_STRING_SUPPORT
template <typename QUANTITY_T, typename CHAR_T = char>
std::basic_string<CHAR_T> to_string(const QUANTITY_T & q)
{
	std::basic_stringstream<CHAR_T> oss;
	oss << q.value;
	if (QUANTITY_T::mass())
	{
		oss << 'M';
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

	if (QUANTITY_T::ecurrent())
	{
		oss << 'E';
		if (QUANTITY_T::ecurrent() != 1) oss << QUANTITY_T::ecurrent();
	}

	if (QUANTITY_T::temperature())
	{
		oss << 't';
		if (QUANTITY_T::temperature() != 1) oss << QUANTITY_T::temperature();
	}

	if (QUANTITY_T::amount())
	{
		oss << 'a';
		if (QUANTITY_T::amount() != 1) oss << QUANTITY_T::amount();
	}

	if (QUANTITY_T::luminosity())
	{
		oss << 'l';
		if (QUANTITY_T::luminosity() != 1) oss << QUANTITY_T::luminosity();
	}

	return oss.str();
}
#endif // OUM_STRING_SUPPORT

}; // namespace uom


// Un-define the utility macros
#undef UOM_MEASURE_LIST
#undef UOM_MEASURE_TEMPLATE_LIST
#undef UOM_MEASURE_LIST1
#undef UOM_MEASURE_TEMPLATE_LIST1
#undef UOM_MEASURE_LIST2
#undef UOM_MEASURE_TEMPLATE_LIST2

#endif // UDR_UOM_H
