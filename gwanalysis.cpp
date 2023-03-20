#include "gwanalysis.h"
using namespace netCDF;



 NcFile ncfile("gwdata/GWprediction.nc", NcFile::read);
 rvector<std::complex<double>> frvector(ncfile.getDim("nt").getSize());
 ncfile.getVar("f").getVar(frvector.data());


