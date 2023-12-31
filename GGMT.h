/*
    Tom Egg
    August 22, 2023
    Header file for GGMT thermostat
*/

// Include libraries
#include <iostream>
#include <iomanip>
#include <cmath>

// Indicate source file
#pragma once

// Thermostat class (Covers 2 moments (4th central moment))
class GGMT
{
    // Public
    public:
        GGMT(double var1, double var2, double momenta1, double momenta2, double q1, double q2, double boltzmann_temp);
        void update_thermostat(double& momentum, const double& mass, const double& t_step, const int& factor);

    // Private
    private:
        double eta1, eta2;  // Thermostat variables
        double p_1, p_2;    // Thermostat variable momenta
        double q_1, q_2;    // Effective masses
        double kT;          // Temperature
};
