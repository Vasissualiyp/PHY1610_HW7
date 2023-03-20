#include <netcdf>
#include <complex>
#include <rarray>
#include <iostream>

using namespace netCDF;
using namespace std;

int main() {
    // Open the NetCDF file
    NcFile file("gwdata/GWprediction.nc", NcFile::read);

    int numVars = file.getVarCount();
    std::cout << "Count of variables " << numVars << std::endl;


    // Read the time array
    auto time_var = file.getVar("t");
    long int t_len = time_var.getDim(0).getSize();
    rarray<float, 1> time_data(t_len);
    time_var.getVar(time_data.data());

    // Read the x array
    rvector<std::complex<double>> frvector(file.getDim("nt").getSize());
    file.getVar("f").getVar(frvector.data());
    //long int x_len = x_var.getDim(0).getSize();
    //x_var.getVar(time_data.data());

    //// Print the contents of the arrays
    //for (long int i = 0; i < t_len; i++) {
    //    cout << "F: " << time_data[i] << endl;
    //    cout << endl;
    //}
    // Print the contents of the arrays
    for (long int i = 0; i < t_len; i++) {
        cout << "Time: " << time_data[i] << endl;
	cout << "Data: " << frvector[i] << endl;
        cout << endl;
    }

    return 0;
}

