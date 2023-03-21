#include "gwanalysis.h"

void powerspectrum(rarray<double, 1> t, 
			      rvector<std::complex<double>> frvector,
			      long int length) {
	rvector<double> absval(length);

	for (long int i = 0; i < length; i++) {
		absval[i] = std::abs(frvector[i]);
	};
};
