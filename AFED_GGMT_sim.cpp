/*
    Tom Egg
    August 22, 2023
    C++ code to run simulation with two GGMT thermostats for a particle in a two dimensional potential well
*/

// Include necessary libraries
#include <iostream>
#include <vector>
#include "omp.h"

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
    #pragma omp parallel for
    for (int i = 0; i < n_steps; i++)
    {
        // Append trajectories
        r.steps.push_back(i);
        r.x_coord.push_back(p.get_x());
        r.x_momenta.push_back(p.get_xmomentum());

        // Propagate particle
        p.propagate_momentum(t_step);
        p.propagete_position(t_step);

        // Parallelize thermostat updating
        #pragma omp sections
        {
            #pragma omp section
            p.propagate_momentum(t_step, thermostat_1, 'x');

            #pragma omp section
            p.propagate_momentum(t_step, thermostat_2, 'y');
        }

        // Finish particle propagation
        p.propagete_position(t_step);
        p.propagate_momentum(t_step);
    }

    // Return
    return;
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
    thermostat_x = GGMT(0.0, 0.0, 1.0, -1.0, 10.0, 2666.6666666, 15.0);
    thermostat_y = GGMT(0.0, 0.0, 1.0, -1.0, 1, 8/3, 1.0);
    particle = Particle(coords, momenta, mass);

    // Exit
    return 0;
}