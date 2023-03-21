#include <rarray>
#include <netcdf>
#include <complex>

void powerspectrum(rarray<double, 1> t, 
			      rvector<std::complex<double>> frvector,
			      long int length);

double inner_product(rarray<double, 1>& A, rarray<double, 1>& B);

double corr_coeff(rarray<double, 1>& F, rarray<double, 1>& G);
