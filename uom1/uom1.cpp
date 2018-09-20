// uom1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define OUM_STRING_SUPPORT
#include "uom.h"

static void f_test01()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::quantity_t<1, 2, -2> acc(1.23);
	std::cout << "acc = " << uom::to_string(acc) << std::endl;

	const uom::quantity_t<0, 1, 0> len;
	std::cout << "len = " << uom::to_string(len) << std::endl;

}

static void f_test02()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::quantity_t<1, 2, -2> q1(1.23);
	const uom::quantity_t<1, 2, -2> q2(4.56);
	const auto q3 = q1 + q2;
	std::cout << "q1 = " << uom::to_string(q1) << std::endl;
	std::cout << "q2 = " << uom::to_string(q2) << std::endl;
	std::cout << "q3 = " << uom::to_string(q3) << std::endl;
}

static void f_test03()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::quantity_t<1, -2, 3, -4> q1(2.0);
	const uom::quantity_t<2, 3, 4, 5>   q2(5.0);
	const auto q3 = q1 * q2;
	std::cout << "q1 = " << uom::to_string(q1) << std::endl;
	std::cout << "q2 = " << uom::to_string(q2) << std::endl;
	std::cout << "q3 = " << uom::to_string(q3) << std::endl;

	std::cout << "q1:"
		<< " mass=" << q1.mass()
		<< " length=" << q1.length()
		<< " time=" << q1.time()
		<< " charge=" << q1.charge()
		<< std::endl;

	std::cout << "q3:"
		<< " mass=" << q3.mass()
		<< " length=" << q3.length()
		<< " time=" << q3.time()
		<< " charge=" << q3.charge()
		<< std::endl;
}

int main()
{
	f_test01();
	f_test02();
	f_test03();

    return 0;
}

