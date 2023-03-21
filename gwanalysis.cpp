#include "gwanalysis.h"
using namespace netCDF;

int main(){

	auto data = read_data_from_netcdf("GWprediction.nc");
	rvector<std::complex<double>> frvector = data.first;
	rarray<double, 1> time_data = data.second;
	
	rvector<double> absval = powerspectrum(frvector);
	
	return 0;


}
