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

	static constexpr int mass() 	{ return MASS; }		// TBD - do we need this?
	static constexpr int length() 	{ return LENGTH; }		// TBD - do we need this?
	static constexpr int time() 	{ return TIME; }		// TBD - do we need this?
	static constexpr int charge() 	{ return CHARGE; }		// TBD - do we need this?

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
template <int MASS, int LENGTH, int TIME, int CHARGE, typename VALUE_T, typename CHAR_T = char>
std::basic_string<CHAR_T> to_string(const quantity_t<MASS, LENGTH, TIME, CHARGE, VALUE_T> & q)
{
	std::basic_stringstream<CHAR_T> oss;
	oss << q.value;
	if (MASS)
	{
		oss << ' ' << 'M';
		if (MASS != 1) oss << MASS;
	}
	if (LENGTH)
	{
		oss << 'L';
		if (LENGTH != 1) oss << LENGTH;
	}
	if (TIME)
	{
		oss << 'T';
		if (TIME != 1) oss << TIME;
	}

	if (CHARGE)
	{
		oss << 'Q';
		if (CHARGE != 1) oss << CHARGE;
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

}; // namespace uom

#endif UDR_UOM_H
