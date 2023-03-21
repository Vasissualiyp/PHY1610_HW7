#include <rarray>
#include <netcdf>
#include <complex>

void powerspectrum(rarray<double, 1> t, 
			      rvector<std::complex<double>> frvector,
			      long int length);
