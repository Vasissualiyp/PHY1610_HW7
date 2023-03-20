CXX = g++
CXXFLAGS=-O2 -g -std=c++17 -Wall -Wfatal-errors -Wconversion
LDFLAGS = -lfftw3
MODULES = gcc/12 fftw/3 python/3 rarray/2.5 hdf5 netcdf gsl
LIBS = -lgsl -lgslcblas -lnetcdf_c++4 -lnetcdf

all: gwanalysis

gwanalysis: gwanalysis.o
		$(CXX) $(LDFLAGS) $< -o $@

gwanalysis.o: gwanalysis.cpp
		module load $(MODULES) && $(CXX) $(CXXFLAGS) $< -o $@

test_read: test_read.o
	$(CXX) -g $(LDFLAGS) $< -o $@ $(LIBS)

test_read.o: test_read.cpp
	$(CXX) -c $(CXXFLAGS) -o test_read.o test_read.cpp

.PHONY: clean

run: gwanalysis
	./gwanalysis > output.dat

testread: test_read
	./test_read

clean:
		rm -f gwanalysis gwanalysis.o output.dat test_read.o test_read

