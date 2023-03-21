#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "gwanalysis.h"
#include <fstream>
#include <iostream>
#include <rarray>

TEST_CASE("Inner product works correctly") {
	rarray<double, 1> vec1(3);
	for(int i=0; i<3; i++) {
		vec1[i] = i+1;
	}
	rarray<double, 1> vec2(3);
	for(int i=0; i<3; i++) {
		vec2[i] = i+4;
	}
	double result = inner_product(vec1, vec2);
	REQUIRE(result == 32);
	} 


TEST_CASE("Correlation coefficient works correctly") {
	rarray<double, 1> vec1(3);
	for(int i=0; i<3; i++) {
		vec1[i] = i+1;
	}
	rarray<double, 1> vec2(3);
	for(int i=0; i<3; i++) {
		vec2[i] = i+4;
	}
	double result = corr_coeff(vec1, vec2);
	REQUIRE(result == (32 / sqrt(77* 14)));
	}

TEST_CASE("Correlation coefficient for signal works correctly") {
	rvector<std::complex<double>> vec1(3);
	//rarray<double, 1> vec1(3);
	for(int i=0; i<3; i++) {
		vec1[i] = sqrt(i+1);
	}
	rvector<std::complex<double>> vec2(3);
	//rarray<double, 1> vec2(3);
	for(int i=0; i<3; i++) {
		vec2[i] = sqrt(i+4);
	}
	double result = signal_corr(vec1, vec2);
	REQUIRE(result == (32 / sqrt(77* 14)));
}
