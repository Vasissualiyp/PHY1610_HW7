#include <rarray>
#include <netcdf>
#include <complex>
rvector<double> powerspectrum(rvector<std::complex<double>>& frvector);

double inner_product(rarray<double, 1>& A, rarray<double, 1>& B);

double corr_coeff(rarray<double, 1>& F, rarray<double, 1>& G);

double signal_corr(rvector<std::complex<double>>& A,
		   rvector<std::complex<double>>& B);
