#include "gwanalysis.h"
using namespace netCDF;

int main(){
	
	const std::string prefix = "detection"; // File name prefix
	const std::string suffix = ".nc";       // File name suffix
	const int num_files = 32;               // Number of files to generate

	auto data = read_data_from_netcdf("GWprediction.nc");
	rvector<std::complex<double>> frvector = data.first;
	rarray<double, 1> time_data = data.second;
	rvector<std::complex<double>> gwfft1 = fft(frvector); 
	
	for (int i = 1; i <= num_files; i++) {
		
		std::ostringstream filename;
		filename << prefix << std::setw(2) << std::setfill('0') << i << suffix;
		auto data2 = read_data_from_netcdf(filename.str());
		rvector<std::complex<double>> frvector2 = data2.first;
		rvector<std::complex<double>> gwfft2 = fft(frvector2); 

		double correlator = signal_corr(gwfft1, gwfft2);
		
		std::cout << correlator << std::endl;
		data2.first.clear();
		data2.second.clear();	
		frvector2.clear();
		gwfft2.clear();

	}
	
	return 0;


}
