#ifndef UDR_UOM_H
#define UDR_UOM_H

#include <cmath>
#include <ratio>
#ifdef OUM_STRING_SUPPORT
#include <sstream>
#endif // OUM_STRING_SUPPORT

///////////////////////////////////////////////////////////////////////
// Some utility macros to help writing down the templates
///////////////////////////////////////////////////////////////////////

#define UOM_MEASURE_LIST MASS, LENGTH, TIME, ECURRENT, TEMPERATURE, AMOUNT, LUMINTENSITY
#define UOM_MEASURE_TEMPLATE_LIST	\
	typename MASS,					\
	typename LENGTH,				\
	typename TIME,					\
	typename ECURRENT,				\
	typename TEMPERATURE,			\
	typename AMOUNT,				\
	typename LUMINTENSITY			\

#define UOM_MEASURE_LIST1 MASS1, LENGTH1, TIME1, ECURRENT1, TEMPERATURE1, AMOUNT1, LUMINTENSITY1
#define UOM_MEASURE_TEMPLATE_LIST1	\
	typename MASS1,					\
	typename LENGTH1,				\
	typename TIME1,					\
	typename ECURRENT1,				\
	typename TEMPERATURE1,			\
	typename AMOUNT1,				\
	typename LUMINTENSITY1			\

#define UOM_MEASURE_LIST2 MASS2, LENGTH2, TIME2, ECURRENT2, TEMPERATURE2, AMOUNT2, LUMINTENSITY2
#define UOM_MEASURE_TEMPLATE_LIST2	\
	typename MASS2,						\
	typename LENGTH2,					\
	typename TIME2,						\
	typename ECURRENT2,					\
	typename TEMPERATURE2,				\
	typename AMOUNT2,					\
	typename LUMINTENSITY2				\


namespace uom
{

///////////////////////////////////////////////////////////////////////
// Some utilities
///////////////////////////////////////////////////////////////////////

// Convert a ratio into a floating point number at compile time
template <typename RATIO_T, typename VALUE_T>
struct ratio_to_float
{
	static constexpr VALUE_T ratio{ VALUE_T((RATIO_T::num) / VALUE_T(RATIO_T::den)) };
};



///////////////////////////////////////////////////////////////////////
// The template structure used to define a qualtity with its dimentions
///////////////////////////////////////////////////////////////////////
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
struct quantity_t
{
	using value_type = VALUE_T;
	static constexpr VALUE_T mass() { return VALUE_T(MASS::num) / VALUE_T(MASS::den); }
	static constexpr VALUE_T length() { return VALUE_T(LENGTH::num) / VALUE_T(LENGTH::den); }
	static constexpr VALUE_T time() { return VALUE_T(TIME::num) / VALUE_T(TIME::den); }
	static constexpr VALUE_T ecurrent() { return VALUE_T(ECURRENT::num) / VALUE_T(ECURRENT::den); }
	static constexpr VALUE_T temperature()  { return VALUE_T(TEMPERATURE::num) / VALUE_T(TEMPERATURE::den); }
	static constexpr VALUE_T amount() { return VALUE_T(AMOUNT::num) / VALUE_T(AMOUNT::den); }
	static constexpr VALUE_T luminosity() { return VALUE_T(LUMINTENSITY::num) / VALUE_T(LUMINTENSITY::den); }

	quantity_t();
	quantity_t(const VALUE_T & init_value);
	quantity_t(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & rv);

	VALUE_T value; // The *only* data member - keep it this way
};

// Default constructor
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
quantity_t<VALUE_T, UOM_MEASURE_LIST>::quantity_t() :
	value(VALUE_T(0))
{
	static_assert(
		sizeof(quantity_t<VALUE_T, UOM_MEASURE_LIST>) ==
		sizeof(quantity_t<VALUE_T, UOM_MEASURE_LIST>::value_type));
	static_assert(
		sizeof(quantity_t<VALUE_T, UOM_MEASURE_LIST>) ==
		sizeof(this->value));
}

// Non-default Constructor
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
quantity_t<VALUE_T, UOM_MEASURE_LIST>::quantity_t(const VALUE_T & init_value) :
	value(init_value)
{
}

// Copy constructor
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
quantity_t<VALUE_T, UOM_MEASURE_LIST>::quantity_t(
		const quantity_t<VALUE_T, UOM_MEASURE_LIST> & rv) :
	value(rv.value)
{
}

// Sum operator
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<VALUE_T, UOM_MEASURE_LIST>
operator+(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & a,
		  const quantity_t<VALUE_T, UOM_MEASURE_LIST> & b)
{
	return quantity_t<VALUE_T, UOM_MEASURE_LIST>(a.value + b.value);
}

// Subtraction operator
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline 
quantity_t<VALUE_T, UOM_MEASURE_LIST>
operator-(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & a,
		  const quantity_t<VALUE_T, UOM_MEASURE_LIST> & b)
{
	return quantity_t<VALUE_T, UOM_MEASURE_LIST>(a.value - b.value);
}

// Multiplication of two quantities
template <UOM_MEASURE_TEMPLATE_LIST1, UOM_MEASURE_TEMPLATE_LIST2, typename VALUE_T>
inline
quantity_t<
	VALUE_T,
	std::ratio_add<MASS1, MASS2>, 
	std::ratio_add<LENGTH1, LENGTH2>,
	std::ratio_add<TIME1, TIME2>,
	std::ratio_add<ECURRENT1, ECURRENT2>,
	std::ratio_add<TEMPERATURE1, TEMPERATURE2>,
	std::ratio_add<AMOUNT1, AMOUNT2>,
	std::ratio_add<LUMINTENSITY1, LUMINTENSITY2>>
operator*(const quantity_t<VALUE_T, UOM_MEASURE_LIST1> & a,
		  const quantity_t<VALUE_T, UOM_MEASURE_LIST2> & b)
{
	return quantity_t<
		VALUE_T,
		std::ratio_add<MASS1, MASS2>,
		std::ratio_add<LENGTH1, LENGTH2>,
		std::ratio_add<TIME1, TIME2>,
		std::ratio_add<ECURRENT1, ECURRENT2>,
		std::ratio_add<TEMPERATURE1, TEMPERATURE2>,
		std::ratio_add<AMOUNT1, AMOUNT2>,
		std::ratio_add<LUMINTENSITY1, LUMINTENSITY2>>(a.value * b.value);
}

// Multiplication: quantities times dimensionless factor
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<VALUE_T, UOM_MEASURE_LIST>
operator*(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & a, const VALUE_T & f)
{
	return quantity_t<VALUE_T, UOM_MEASURE_LIST>(a.value * f);
}

// Multiplication: dimensionless factor times quantities 
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<VALUE_T, UOM_MEASURE_LIST>
operator*(const VALUE_T & f, const quantity_t<VALUE_T, UOM_MEASURE_LIST> & a)
	
{
	return quantity_t<VALUE_T, UOM_MEASURE_LIST>(f * a.value);
}

// Division: two quantities
template <UOM_MEASURE_TEMPLATE_LIST1, UOM_MEASURE_TEMPLATE_LIST2, typename VALUE_T>
inline
quantity_t<
	VALUE_T,
	std::ratio_subtract<MASS1, MASS2>,
	std::ratio_subtract<LENGTH1, LENGTH2>,
	std::ratio_subtract<TIME1, TIME2>,
	std::ratio_subtract<ECURRENT1, ECURRENT2>,
	std::ratio_subtract<TEMPERATURE1, TEMPERATURE2>,
	std::ratio_subtract<AMOUNT1, AMOUNT2>,
	std::ratio_subtract<LUMINTENSITY1, LUMINTENSITY2>>
operator/(const quantity_t<VALUE_T, UOM_MEASURE_LIST1> & a,
			  const quantity_t<VALUE_T, UOM_MEASURE_LIST2> & b)
{
	return quantity_t<
		VALUE_T,
		std::ratio_subtract<MASS1, MASS2>,
		std::ratio_subtract<LENGTH1, LENGTH2>,
		std::ratio_subtract<TIME1, TIME2>,
		std::ratio_subtract<ECURRENT1, ECURRENT2>,
		std::ratio_subtract<TEMPERATURE1, TEMPERATURE2>,
		std::ratio_subtract<AMOUNT1, AMOUNT2>,
		std::ratio_subtract<LUMINTENSITY1, LUMINTENSITY2>>(a.value * b.value);
}

// Division: quantities by dimensionless factor 
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<VALUE_T, UOM_MEASURE_LIST>
operator/(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & a, const VALUE_T & f)
{
	return quantity_t<VALUE_T, UOM_MEASURE_LIST>(a.value / f);
}

// Division: dimensionless factor by quantities
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<VALUE_T, UOM_MEASURE_LIST>
operator/(const VALUE_T & f, const quantity_t<VALUE_T, UOM_MEASURE_LIST> & a)

{
	return quantity_t<VALUE_T, UOM_MEASURE_LIST>(f / a.value);
}


// Square rooot of quantity
template <typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<
	VALUE_T,
	std::ratio_divide<MASS, std::ratio<2>>,
	std::ratio_divide<LENGTH, std::ratio<2>>,
	std::ratio_divide<TIME, std::ratio<2>>,
	std::ratio_divide<ECURRENT, std::ratio<2>>,
	std::ratio_divide<TEMPERATURE, std::ratio<2>>,
	std::ratio_divide<AMOUNT, std::ratio<2>>,
	std::ratio_divide<LUMINTENSITY, std::ratio<2>> >
sqrt(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & v)
{
	return quantity_t<
		VALUE_T,
		std::ratio_divide<MASS, std::ratio<2>>,
		std::ratio_divide<LENGTH, std::ratio<2>>,
		std::ratio_divide<TIME, std::ratio<2>>,
		std::ratio_divide<ECURRENT, std::ratio<2>>,
		std::ratio_divide<TEMPERATURE, std::ratio<2>>,
		std::ratio_divide<AMOUNT, std::ratio<2>>,
		std::ratio_divide<LUMINTENSITY, std::ratio<2>> >(std::sqrt(v.value));
}

// power of quantity
template <typename EXPONENT_T, typename VALUE_T, UOM_MEASURE_TEMPLATE_LIST>
inline
quantity_t<
	VALUE_T,
	std::ratio_multiply<MASS, EXPONENT_T>,
	std::ratio_multiply<LENGTH, EXPONENT_T>,
	std::ratio_multiply<TIME, EXPONENT_T>,
	std::ratio_multiply<ECURRENT, EXPONENT_T>,
	std::ratio_multiply<TEMPERATURE, EXPONENT_T>,
	std::ratio_multiply<AMOUNT, EXPONENT_T>,
	std::ratio_multiply<LUMINTENSITY, EXPONENT_T> >
pow(const quantity_t<VALUE_T, UOM_MEASURE_LIST> & v)
{
	constexpr VALUE_T exponent = ratio_to_float<EXPONENT_T, VALUE_T>::ratio;
	const VALUE_T new_value = std::pow(v.value, exponent);
	return quantity_t<
		VALUE_T,
		std::ratio_multiply<MASS, EXPONENT_T>,
		std::ratio_multiply<LENGTH, EXPONENT_T>,
		std::ratio_multiply<TIME, EXPONENT_T>,
		std::ratio_multiply<ECURRENT, EXPONENT_T>,
		std::ratio_multiply<TEMPERATURE, EXPONENT_T>,
		std::ratio_multiply<AMOUNT, EXPONENT_T>,
		std::ratio_multiply<LUMINTENSITY, EXPONENT_T> >(new_value);
}


///////////////////////////////////////////////////////////////////////
// Definitions of each SI base dimensions
///////////////////////////////////////////////////////////////////////
template <typename VALUE_T = double>
using mass_t = quantity_t<VALUE_T, std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using length_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using time_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using ecurrent_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using temperature_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using amount_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>, std::ratio<0>>;

template <typename VALUE_T = double>
using luminosity_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<1>>;


///////////////////////////////////////////////////////////////////////
// Definitions of some composite dimensions
///////////////////////////////////////////////////////////////////////

template <typename VALUE_T = double>
using speed_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<1>, std::ratio<-1>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using acceleration_t = quantity_t<VALUE_T, std::ratio<0>, std::ratio<1>, std::ratio<-2>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using force_t = quantity_t<VALUE_T, std::ratio<1>, std::ratio<1>, std::ratio<-2>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using energy_t = quantity_t<VALUE_T, std::ratio<1>, std::ratio<2>, std::ratio<-2>, std::ratio<0>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;

template <typename VALUE_T = double>
using epotential_t = quantity_t<VALUE_T, std::ratio<1>, std::ratio<2>, std::ratio<-3>, std::ratio<-1>, std::ratio<0>, std::ratio<0>, std::ratio<0>>;


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
