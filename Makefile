C = g++
CFLAGS = -std=c++17 -c -O2
LDFLAGS = -lfftw3
MODULES = gcc/12 fftw/3 python/3

all: sincfftw

sincfftw: sincfftw.o
		$(CC) $(LDFLAGS) $< -o $@

sincfftw.o: sincfftw.cpp
		module load $(MODULES) && $(CC) $(CFLAGS) $< -o $@

.PHONY: clean

clean:
		rm -f sincfftw sincfftw.o output.dat

