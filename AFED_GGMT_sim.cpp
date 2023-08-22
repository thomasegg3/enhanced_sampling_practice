/*
    Tom Egg
    August 22, 2023
    C++ code to run simulation with two GGMT thermostats for a particle in a two dimensional potential well
*/

// Include necessary libraries
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Particle.h"

// Struct for results
struct Result
{
    std::vector<int> steps;
    std::vector<double> x_coord;
    std::vector<double> x_momenta;
};

void run_simulation(Particle& p, GGMT& thermostat_1, GGMT& thermostat_2, int n_steps, double t_step, Result& r)
/*
    Function to run dynamics simulation
    Particle p : particle to propagate
    GGMT thermostat_1 : thermostat 1
    GGMT thermostat_2 : thermostat 2
    int n_steps : number of steps
    double t_step : timestep
    Result r : result struct
*/
{
    // For loop to run simulation
    for (int i = 0; i < n_steps; i++)
    {
        // Append trajectories
        r.steps.push_back(i);
        r.x_coord.push_back(p.get_x());
        r.x_momenta.push_back(p.get_xmomentum());

        // Propagate particle
        p.propagate_momentum(t_step);
        p.propagate_position(t_step);
        p.propagate_momentum(t_step, thermostat_1, 'x');
        p.propagate_momentum(t_step, thermostat_2, 'y');
        p.propagate_position(t_step);
        p.propagate_momentum(t_step);
    }

    // Return
    return;
}

void results_to_csv(const Result& r, const std::string& filename, int n_steps)
/*
    Function to save results to csv file
    Result results : result struct
    string filename : name of file to save as
    int n_steps : number of elements in list
*/
{
    // Write file
    std::ofstream file(filename);

    // If not open, error
    if (!file.is_open()) 
    {
        std::cerr << "Error: Unable to open the file " << filename << std::endl;
        return;
    }

    // Write the header row
    file << "Steps, X-Coordinate, Momentum" << std::endl;

    // Write the data rows
    for (int i = 0; i < n_steps; i++) 
    {
        file << r.steps[i] << ", " << r.x_coord[i] << ", " << r.x_momenta[i] << std::endl;
    }

    file.close();
}

// Main
int main()
{
    // Initialize result and starting variables
    Result md_results;
    int n_steps = 250000000;
    double coords[2] = {1.0, 1.0};
    double momenta[2] = {1.0, 1.0};
    double mass[2] = {300, 1};
    
    // Initialize Particle and two GGMTs
    GGMT thermostat_x(0.0, 0.0, 1.0, -1.0, 10.0, 2666.6666666, 15.0);
    GGMT thermostat_y(0.0, 0.0, 1.0, -1.0, 1.0, 8/3, 1.0);
    Particle particle(coords, momenta, mass);

    // Run simulation
    run_simulation(particle, thermostat_x, thermostat_y, n_steps, 0.0025, md_results);

    // Write results to file
    std::string filename = "results.csv";
    results_to_csv(md_results, filename, n_steps);

    // Exit
    return 0;
}