CXX = g++
CXXFLAGS=-O2 -g -std=c++17 -Wall -Wfatal-errors -Wconversion
LDFLAGS = -lfftw3
MODULES = gcc/12 fftw/3 python/3 rarray/2.5 hdf5 netcdf gsl
LIBS = -lgsl -lgslcblas -lnetcdf_c++4 -lnetcdf

all: gwanalysis

# Main modules compilation {{{
gwanalysis: gwanalysis.o gwcalc.o fourier.o
	$(CXX) $(LDFLAGS) gwanalysis.o gwcalc.o fourier.o -o gwanalysis $(LIBS)

gwanalysis.o: gwanalysis.cpp 
	module load $(MODULES) && $(CXX) -c $(CXXFLAGS) -o gwanalysis.o gwanalysis.cpp 
gwcalc.o: gwcalc.cpp 
	module load $(MODULES) && $(CXX) -c $(CXXFLAGS) -o gwcalc.o gwcalc.cpp 

fourier.o: fourier.cpp 
	module load $(MODULES) && $(CXX) -c $(CXXFLAGS) -o fourier.o fourier.cpp $(LIBS)
#}}}

# Module tests compilation {{{

unit_test: unit_test.o gwcalc.o fourier.o
	$(CXX) $(LDFLAGS) -o $@ $^ -lCatch2Main -lCatch2 $(LIBS) #-lboost_unit_test_framework

unit_test.o: unit_test.cpp
	$(CXX) -c $(CXXFLAGS) -o unit_test.o unit_test.cpp

functest: unit_test
	./unit_test

#}}}

# Test reader {{{
test_read: test_read.o
	$(CXX) -g $(LDFLAGS) $< -o $@ $(LIBS)

test_read.o: test_read.cpp
	$(CXX) -c $(CXXFLAGS) -o test_read.o test_read.cpp

testread: test_read
	./test_read
#}}}

.PHONY: clean all run

run: gwanalysis
	./gwanalysis > output.dat

clean:
	rm -f gwanalysis gwanalysis.o output.dat test_read.o test_read gwcalc.o test_inner_product.o test_inner_product test_corr_coeff.o test_corr_coeff unit_test

