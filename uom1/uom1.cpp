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

static void f_test04()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";
	const uom::length_t<> len1(1.1);
	const uom::length_t<> len2(2.2);
	const auto  len3 = len1 + len2;

	std::cout << "11 = " << uom::to_string(len1) << std::endl;
	std::cout << "12 = " << uom::to_string(len2) << std::endl;
	std::cout << "13 = " << uom::to_string(len3) << std::endl;

	std::cout << "len3:"
		<< " value=" << len3.value
		<< " mass=" << len3.mass()
		<< " length=" << len3.length()
		<< " time=" << len3.time()
		<< " charge=" << len3.charge()
		<< std::endl;
}

static void f_test05()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::length_t<> len(1.0);
	const uom::mass_t<> mass(2.0);
	const uom::time_t<> time(3.0);
	const uom::charge_t<> charge(4.0);
	const uom::speed_t<> speed(5.0);
	const uom::acceleration_t<> acceleration(6.0);
	const uom::force_t<> force(-7.0);
	const uom::energy_t<> energy(8.0);

	std::cout << "L: " << uom::to_string(len) << std::endl;
	std::cout << "M: " << uom::to_string(mass) << std::endl;
	std::cout << "T: " << uom::to_string(time) << std::endl;
	std::cout << "C: " << uom::to_string(charge) << std::endl;
	std::cout << "S: " << uom::to_string(speed) << std::endl;
	std::cout << "A: " << uom::to_string(acceleration) << std::endl;
	std::cout << "F: " << uom::to_string(force) << std::endl;
	std::cout << "E: " << uom::to_string(energy) << std::endl;

	const auto energy2 = energy + (force * len);
	std::cout << "E2: " << uom::to_string(energy) << std::endl;
}

static void f_test06()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::length_t<> len1(1.0);
	const auto len2 = 2.0 * len1;
	const auto len3 = len1 * 3.0;

	std::cout << "L1: " << uom::to_string(len1) << std::endl;
	std::cout << "L2: " << uom::to_string(len2) << std::endl;
	std::cout << "L3: " << uom::to_string(len3) << std::endl;

	const uom::speed_t<> speed1(2.0);
	const auto speed2 = speed1 / 2.0;
	const auto speed3 = 1.0 / speed1;

	std::cout << "S1: " << uom::to_string(speed1) << std::endl;
	std::cout << "S2: " << uom::to_string(speed2) << std::endl;
	std::cout << "S3: " << uom::to_string(speed3) << std::endl;
}



int main()
{
	f_test01();
	f_test02();
	f_test03();
	f_test04();
	f_test05();
	f_test06();

    return 0;
}

