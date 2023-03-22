#define CATCH_CONFIG_MAIN
#include <catch2/catch_all.hpp>
#include "gwanalysis.h"
#include <fstream>
#include <iostream>
#include <rarray>


TEST_CASE("Inner product works correctly") {//{{{
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
//}}}

TEST_CASE("Correlation coefficient works correctly") {//{{{
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
//}}}

TEST_CASE("Correlation coefficient for signal works correctly") {//{{{
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
//}}}

TEST_CASE("FFT works correctly") {//{{{
	rvector<std::complex<double>> f(3);
	for(int i=0; i<3; i++) {
		f[i] = i + 1 ;
	}
	//REQUIRE(f[0] == 1.0);
	rvector<std::complex<double>> fhat = fft(f);
	REQUIRE(fhat.size() == 3);
	
	double imgpart =0.86602540378443864676;
	
	// Check first frequency component
	REQUIRE(std::abs(fhat[0].real() - 6.0) < 1e-15);
	REQUIRE(std::abs(fhat[0].imag()) < 1e-15);

	// Check second frequency component
	REQUIRE(std::abs(fhat[1].real() - (-1.5)) < 1e-15);
	REQUIRE(std::abs(fhat[1].imag() - (imgpart)) < 1e-15);

	// Check third frequency component
	REQUIRE(std::abs(fhat[2].real() - (-1.5)) < 1e-15);
	REQUIRE(std::abs(fhat[2].imag() + (imgpart)) < 1e-15);
}
//}}}

TEST_CASE("Sorter function works correctly") { //{{{
    // Create test input data
    std::vector<std::string> filenames {"file1.txt", "file2.txt", "file3.txt"};
    std::vector<double> correlators {0.5, 0.2, 0.8};

    // Call the sorter function on the test data
    sorter(filenames, correlators);

    // Check that the resulting filenames and correlators are sorted correctly
    REQUIRE(filenames[0] == "file3.txt");
    REQUIRE(filenames[1] == "file1.txt");
    REQUIRE(filenames[2] == "file2.txt");

    REQUIRE(correlators[0] == 0.8);
    REQUIRE(correlators[1] == 0.5);
    REQUIRE(correlators[2] == 0.2);
}
//}}}
