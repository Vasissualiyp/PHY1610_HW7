#include "gwanalysis.h"
using namespace netCDF;

int main(){

	// Open the NetCDF file
	std::string filepath = "/scinet/course/phy1610/gwdata/";
	std::string filename = "GWprediction.nc";
	NcFile file(filepath + filename, NcFile::read);

	// Read the time array
	auto time_var = file.getVar("t");
	long int t_len = time_var.getDim(0).getSize();
	rarray<double, 1> time_data(t_len);
	time_var.getVar(time_data.data());

	// Read the f array
	rvector<std::complex<double>> frvector(file.getDim("nt").getSize());
	file.getVar("f").getVar(frvector.data());
	
	rvector<double> absval = powerspectrum(frvector);
	
	return 0;


}
