#include "gwanalysis.h"
using namespace netCDF;

int main(){
	
	// Give info about the filenames of sample files
	const std::string prefix = "detection"; // File name prefix
	const std::string suffix = ".nc";       // File name suffix
	const int num_files = 32;               // Number of files to generate
	const int best_fits_no= 5;  		// How many of the best fits do you want

	// Read the observational data file
	auto data = read_data_from_netcdf("GWprediction.nc");
	rvector<std::complex<double>> frvector = data.first;
	rarray<double, 1> time_data = data.second;
	rvector<std::complex<double>> gwfft1 = fft(frvector); 

	// Declare two empty vectors to store filenames and correlators
	std::vector<std::string> filenames;
	std::vector<double> correlators;

	// Loop through all the sample files
	for (int i = 1; i <= num_files; i++) {
		
		std::ostringstream filename;
		filename << prefix << std::setw(2) << std::setfill('0') << i << suffix;
		auto data2 = read_data_from_netcdf(filename.str());
		rvector<std::complex<double>> frvector2 = data2.first;
		rvector<std::complex<double>> gwfft2 = fft(frvector2); 
		
		double correlator = signal_corr(gwfft1, gwfft2);

		// Add filename and correlator to the respective vectors
		filenames.push_back(filename.str());
		correlators.push_back(correlator);
		
		// Free the memory
		data2.first.clear();
		data2.second.clear();
		frvector2.clear();
		gwfft2.clear();

	}
	
	// Sort the elements in both of the arrays
	sorter(filenames, correlators);

	// Final output
	std::cout << "Best signal source candidates: " << "\n" << std::endl;
	for (int i = 0; i < best_fits_no; i++) {
		std::cout << filenames[i] << std::endl;
		std::cout << "Correlation factor: " << correlators[i] << "\n" << std::endl;
	}

	return 0;
}
