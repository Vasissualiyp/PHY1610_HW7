#include "gwanalysis.h"
#include <complex>
#include <fftw3.h>
using namespace netCDF;

// File import from the folder based on the file name{{{
std::pair<rvector<std::complex<double>>, rarray<double, 1>> read_data_from_netcdf(const std::string& filename) {

    // Open the NetCDF file
    std::string filepath = "/scinet/course/phy1610/gwdata/";
    netCDF::NcFile file(filepath + filename, NcFile::read);

    // Read the time array
    auto time_var = file.getVar("t");
    long int t_len = time_var.getDim(0).getSize();
    rarray<double, 1> time_data(t_len);
    time_var.getVar(time_data.data());

    // Read the f array
    rvector<std::complex<double>> frvector(file.getDim("nt").getSize());
    file.getVar("f").getVar(frvector.data());

    return {frvector, time_data};
}

//}}}

// Fourier transform the signal {{{
rvector<std::complex<double>> fft(rvector<std::complex<double>>& f) {
	int n = f.size();

	rvector<std::complex<double>> fhat(n);

	// Create FFTW plan and execute FFT
	fftw_plan p = fftw_plan_dft_1d(n, 
					reinterpret_cast<fftw_complex*>(f.data()),
					reinterpret_cast<fftw_complex*>(fhat.data()),
					FFTW_FORWARD, FFTW_ESTIMATE);
	fftw_execute(p);
	fftw_destroy_plan(p);

	return fhat;
}

//}}}

