#include "gwanalysis.h"

// Power spectrum function {{{
rvector<double> powerspectrum(rvector<std::complex<double>>& frvector){

		long int length = frvector.size();
		rvector<double> absval(length);

		for (long int i = 0; i < length; i++) {
			absval[i] = std::abs(frvector[i]);
			absval[i] =absval[i] * absval[i];
		}
		return absval;
};
//}}}

// Inner product function {{{
double inner_product(rarray<double, 1>& A, rarray<double, 1>& B) {
	    double result = 0.0;
	    for (int k = 0; k < A.extent(0); k++) {
		result += A[k] * B[k];
	    }
	    return result;
}
//}}}

// Correlation coefficient {{{
double corr_coeff(rarray<double, 1>& F, rarray<double, 1>& G) {
	    double F_norm = inner_product(F, F);
	    double G_norm = inner_product(G, G);
	    double FG_dot_product = inner_product(F, G);
	    double denom = std::sqrt(F_norm * G_norm);
	    if (denom == 0) {
		// To avoid division by zero errors, return 0 if the denominator is zero.
		return 0;
	    }
	    return FG_dot_product / denom;
}
//}}}

// Correlation with powerspectrum conversion {{{
double signal_corr(rvector<std::complex<double>>& A,
		   rvector<std::complex<double>>& B) {
	rvector<double> spect_A = powerspectrum(A);
	rvector<double> spect_B = powerspectrum(B);
	double correlation = corr_coeff(spect_A, spect_B);
	return correlation;
}
//}}}

// A sorter funciton that sorts the final arrays of filenames and correlators {{{
void sorter(std::vector<std::string>& filenames,
	    std::vector<double>& correlators) {

	long int num_files = correlators.size();

	for (int i = 0; i < num_files; i++) {
	for (int j = 0; j < num_files; j++) {
		if (correlators[i] > correlators[j]) {
		// Swap correlators[i] and correlators[j]
		double temp = correlators[i];
		correlators[i] = correlators[j];
		correlators[j] = temp;

		// Swap filenames[i] and filenames[j]
		std::string temp_str = filenames[i];
		filenames[i] = filenames[j];
		filenames[j] = temp_str;
        } } }
}
//}}}
