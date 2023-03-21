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

TEST_CASE("FFT works correctly") {
	rvector<std::complex<double>> f(3);
	for(int i=0; i<3; i++) {
		f[i] = i + 1 ;
	}
	//REQUIRE(f[0] == 1.0);
	rvector<std::complex<double>> fhat = fft(f);
	REQUIRE(fhat.size() == 3);

	// Check first frequency component
	REQUIRE(std::abs(fhat[0].real() - 10.0) < 1e-15);
	REQUIRE(std::abs(fhat[0].imag()) < 1e-15);

	// Check second frequency component
	REQUIRE(std::abs(fhat[1].real() - (-2.0)) < 1e-15);
	REQUIRE(std::abs(fhat[1].imag() - 2.0) < 1e-15);

	// Check third frequency component
	REQUIRE(std::abs(fhat[2].real() - (-2.0)) < 1e-15);
	REQUIRE(std::abs(fhat[2].imag()) < 1e-15);
}

