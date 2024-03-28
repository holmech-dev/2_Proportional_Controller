/*********************
Program - Proportional Controller
Maintainer - C.Holmes
Version - 0
********************/

#include <iostream>
#include <fstream>
#include <vector>

// Variable Delarations
int tankRadius = 5; // Radius of the Water Tank
int tankVolumeMin = 0; // Minimum Volume of the Water Tank
int tankVolumeMax = 100; // Maximum Volume of the Water Tank
int volumeResolution = 10; // Resolution of Volume Increments
double dt = 0.04; // Simulation time interval
int t_0 = 0; // Simulation Initial Time
int t_end = 10; // Simulation End Time
int waterDensity = 1000; // Density of Water [kg/m^3]
double tLength = t_end / dt; // Vector length of time points based on interval
std::vector<double> t(tLength, 0.0); // Time Vector

int Kp = 1000; // Proportional gain constant

int tankVolumeInitial = 0; // Initial Tank Volume
int tankVolumeReference = 80; // Target Tank Volume
std::vector<double> tankVolumeRefVec(tLength, 0); // Reference Volume Vector
std::vector<double> tankVolumeActualVec(tLength, 0); // Actual Volume Vector
std::vector<double> error(tLength, 0); // Error Vector
std::vector<double> mDot(tLength, 0); // Mass Flow Rate Vector


// Function Declarations

int main () {

    // Open and create CSV file and header for plotting
    std::ofstream sim_out_file;
    sim_out_file.open("sim_out.csv");
    sim_out_file << "t,reference,error,actual,dt,mdot\n";

    std::cout << "\n\n";
    std::cout << "*************************************************************\n";
    std::cout << "Water Tank Proportional Controller Program Starting......  🕹️\n";
    std::cout << "*************************************************************\n";

    // User intput for Reference/Target water tank level
    std::cout << "\n";
    std::cout << "Please input a reference value: ";
    std::cin >>  tankVolumeReference;
    std::cout << "\n";
    std::cout << "Target Volume Reference at Start -> " << tankVolumeReference << std::endl;
    std::cout << "Tank Volume Value at Start -> " << tankVolumeInitial << std::endl;
    std::cout << "\n";

    tankVolumeRefVec[0] = tankVolumeReference;

    tankVolumeActualVec[0] = tankVolumeInitial;
    double tankVolumeActualPrev = tankVolumeActualVec[0];

    mDot[0] = 0;
    double mDotPrev = mDot[0];
    
    double errorPrev = 0;

    // Simulation Start
    // Iterate through simulation to length of time t
    for (int i = 0; i < t.size(); i++){
    //for (int i = 0; i < 300; i++){

        // Determine reference value vector for the tank
        tankVolumeRefVec[i] = tankVolumeReference;

        // Calculate the error between reference and actual
        errorPrev = tankVolumeRefVec[i] - tankVolumeActualPrev;

        // Calculate the control input, mass flow rate
        mDot[i] = Kp * errorPrev;
        
        // Calculate the true tank volume in the next time step using numerical integration
        tankVolumeActualVec[i] = tankVolumeActualPrev + (mDotPrev + mDot[i]) / (2*waterDensity)*(dt);

        tankVolumeActualPrev = tankVolumeActualVec[i];
        mDotPrev = mDot[i];

        sim_out_file << i << "," << tankVolumeRefVec[i] << "," << errorPrev << "," << tankVolumeActualVec[i] << "," << dt << "," << mDotPrev << "\n";

    }
    std::cout << "Tank Volume Value at End -> " << tankVolumeActualPrev << std::endl;
    std::cout << "\n";
}