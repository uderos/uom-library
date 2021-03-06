// uom1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define OUM_STRING_SUPPORT
#include "uom.h"

using zero_t = std::ratio<0>;
using one_t = std::ratio<1>;
using two_t = std::ratio<2>;
using minus_one_t = std::ratio<-1>;

static void f_test01()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::quantity_t<double, one_t, two_t, minus_one_t, zero_t, zero_t, zero_t, zero_t> acc(1.23);
	std::cout << "acc = " << uom::to_string(acc) << std::endl;

	const uom::quantity_t<double, zero_t, one_t, zero_t, zero_t, zero_t, zero_t, zero_t> len;
	std::cout << "len = " << uom::to_string(len) << std::endl;

	const uom::quantity_t<double, one_t, one_t, one_t, one_t, one_t, one_t, one_t> q_all(1.234);
	std::cout << "q_all= " << uom::to_string(q_all) << std::endl;
}

static void f_test02()
{
	//std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	//const uom::quantity_t<double, 1, 2, -2, 0, 0, 0, 0> q1(1.23);
	//const uom::quantity_t<double, 1, 2, -2, 0, 0, 0, 0> q2(4.56);
	//const auto q3 = q1 + q2;
	//std::cout << "q1 = " << uom::to_string(q1) << std::endl;
	//std::cout << "q2 = " << uom::to_string(q2) << std::endl;
	//std::cout << "q3 = " << uom::to_string(q3) << std::endl;
}

static void f_test03()
{
	//std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	//const uom::quantity_t<float, 1, -2, 3, -4, 0, 0, 0> q1(2.0);
	//const uom::quantity_t<float, 2, 3, 4, 5, 0, 0, 0>   q2(5.0);
	//const auto q3 = q1 * q2;
	//std::cout << "q1 = " << uom::to_string(q1) << std::endl;
	//std::cout << "q2 = " << uom::to_string(q2) << std::endl;
	//std::cout << "q3 = " << uom::to_string(q3) << std::endl;

	//std::cout << "q1:"
	//	<< " mass=" << q1.mass()
	//	<< " length=" << q1.length()
	//	<< " time=" << q1.time()
	//	<< " ecurrent=" << q1.ecurrent()
	//	<< std::endl;

	//std::cout << "q3:"
	//	<< " mass=" << q3.mass()
	//	<< " length=" << q3.length()
	//	<< " time=" << q3.time()
	//	<< " ecurrent=" << q3.ecurrent()
	//	<< std::endl;
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
		<< " ecurrent=" << len3.ecurrent()
		<< std::endl;

	std::cout << "sizeof(uom::length_t)             = " << sizeof(len1) << std::endl;
	std::cout << "sizeof(uom::length_t::value)      = " << sizeof(uom::energy_t<>::value) << std::endl;
	std::cout << "sizeof(uom::length_t::value_type) = " << sizeof(uom::energy_t<>::value_type) << std::endl;
	std::cout << "sizeof(len1.value)                = " << sizeof(len1.value) << std::endl;
}

static void f_test05()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::length_t<> len(1.0);
	const uom::mass_t<> mass(2.0);
	const uom::time_t<> time(3.0);
	const uom::ecurrent_t<> ecurrent(4.0);
	const uom::speed_t<> speed(5.0);
	const uom::acceleration_t<> acceleration(6.0);
	const uom::force_t<> force(-7.0);
	const uom::energy_t<> energy(8.0);
	const uom::epotential_t<> epotential(9.0);

	std::cout << "L: " << uom::to_string(len) << std::endl;
	std::cout << "M: " << uom::to_string(mass) << std::endl;
	std::cout << "T: " << uom::to_string(time) << std::endl;
	std::cout << "C: " << uom::to_string(ecurrent) << std::endl;
	std::cout << "S: " << uom::to_string(speed) << std::endl;
	std::cout << "A: " << uom::to_string(acceleration) << std::endl;
	std::cout << "F: " << uom::to_string(force) << std::endl;
	std::cout << "E: " << uom::to_string(energy) << std::endl;
	std::cout << "P: " << uom::to_string(epotential) << std::endl;

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

static void f_test07()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	uom::energy_t<> e1(1.0);

	const std::string s1 = uom::to_string<decltype(e1), char>(e1);
	const std::wstring ws1 = uom::to_string<decltype(e1), wchar_t>(e1);

	std::cout <<  "S1:  " << s1 << std::endl;
	std::wcout << "WS1: " << ws1 << std::endl;

}


uom::length_t<> f_len_sum(const uom::length_t<> & a, const uom::length_t<> & b)
{
	return a + b;
}

double f_double_sum(const double &a, const double & b)
{
	return a + b;
};

static void f_test08()
{
	uom::length_t<> l1(1.1);
	uom::length_t<> l2(2.2);
	auto l3 = f_len_sum(l1,  l2);

	double f1(1.1), f2(2.2);
	auto f3 = f_double_sum(f1, f2);
}

static void f_test09()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::length_t<> l1(9);
	const uom::epotential_t<> e1(16);

	std::cout << "L1:  " << uom::to_string(l1) << std::endl;
	std::cout << "E1:  " << uom::to_string(e1) << std::endl;

	const auto rl1 = uom::sqrt(l1);
	const auto re1 = uom::sqrt(e1);
	std::cout << "RL1: " << uom::to_string(rl1) << std::endl;
	std::cout << "RE1: " << uom::to_string(re1) << std::endl;
}

static void f_test10()
{
	std::cout << "\n" << __FUNCTION__ << "() BEGIN\n";

	const uom::length_t<> l1(9);
	const uom::epotential_t<> e1(16);

	std::cout << "L1:  " << uom::to_string(l1) << std::endl;
	std::cout << "E1:  " << uom::to_string(e1) << std::endl;

	const auto pl1 = uom::pow<std::ratio<1, 3>>(l1);
	std::cout << "PL1: " << uom::to_string(pl1) << std::endl;

	const auto pe1 = uom::pow<std::ratio<3, 1>>(e1);
	std::cout << "PE1: " << uom::to_string(pe1) << std::endl;
}


int main()
{
	f_test01();
	f_test02();
	f_test03();
	f_test04();
	f_test05();
	f_test06();
	f_test07();
	f_test08();
	f_test09();
	f_test10();

    return 0;
}

