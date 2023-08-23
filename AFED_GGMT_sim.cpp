/*
    Tom Egg
    August 22, 2023
    C++ code to run simulation with two GGMT thermostats for a particle in a two dimensional potential well
*/

// Include necessary libraries
#include <iostream>
#include <fstream>
#include <string>
#include "Particle.h"

void run_simulation(Particle& p, GGMT& thermostat_1, GGMT& thermostat_2, int n_steps, double t_step, std::string& filename)
/*
    Function to run dynamics simulation
    Particle p : particle to propagate
    GGMT thermostat_1 : thermostat 1
    GGMT thermostat_2 : thermostat 2
    int n_steps : number of steps
    double t_step : timestep
    string filename : name of file to save to
*/
{
    // Variable to print completion bar
    int j = 0;
    double progress;

    // Write file
    std::ofstream file(filename);

    // If not open, error
    if (!file.is_open())
    {
        std::cerr << "Error: Unable to open the file " << filename << std::endl;
        return;
    }

    // Write the header row
    file << "Steps,X-Coordinate,Momentum,y,ym" << std::endl;

    // For loop to run simulation
    for (int i = 0; i < n_steps; i++)
    {
	// Progress
	progress = (static_cast<double>(i) / n_steps) * 100;

        // Append trajectories
        file << i << ", " << p.get_x() << ", " << p.get_xmomentum() << ", " << p.get_y() << ", " << p.get_ymomentum() << std::endl;

        // Propagate particle
        p.propagate_momentum(t_step);
        p.propagate_position(t_step);
        p.propagate_momentum(t_step, thermostat_1, 'x');
        p.propagate_momentum(t_step, thermostat_2, 'y');
        p.propagate_position(t_step);
        p.propagate_momentum(t_step);

    	// Progress tracking
    	// Update the progress bar
        if (progress >= j * 10)
        {
            std::cout << "["; // Start bracket
            for (int k = 0; k < j; k++) {
                std::cout << "="; // Equal signs for completed part
            }
            std::cout << ">"; // Greater than sign for current progress
            for (int k = j + 1; k < 10; k++) {
                std::cout << " "; // Spaces for remaining part
            }
            std::cout << "]\t" << j*10 << "%"; // End bracket
            j++;
            std::cout.flush(); // Flush the output buffer to ensure it's displayed immediately
            std::cout << '\r';
    	}
     }

    // Return
    file.close();
    std::cout << "[==========]\t100%" << std::endl;
    return;
}

// Main
int main()
{
    // Initialize result and starting variables
    int n_steps = 1500000;
    double coords[2] = {1.0, 1.0};
    double momenta[2] = {1.0, 1.0};
    double mass[2] = {300, 1};
    
    // Initialize Particle and two GGMTs
    GGMT thermostat_x(0.0, 0.0, 1.0, -1.0, 15.0, 9000.0, 15.0);
    GGMT thermostat_y(0.0, 0.0, 1.0, -1.0, 1.0, 8.0/3.0, 1.0);
    Particle particle(coords, momenta, mass);

    // Run simulation
    std::string filename = "results.csv";
    run_simulation(particle, thermostat_x, thermostat_y, n_steps, 0.00025, filename);

    // Exit
    std::cout << "END" << std::endl;
    return 0;
}
