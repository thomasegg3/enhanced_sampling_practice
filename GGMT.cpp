/*
    Tom Egg
    August 22, 2023
    cpp file for GGMT thermostat
*/

// Include GGMT
#include "GGMT.h"

GGMT::GGMT(double var1, double var2, double momenta1, double momenta2, double q1, double q2, double kT)
/*
    Constructor for a GGMT thermostat
    double var1 : thermostat variable 1
    double var2 : thermostat variable 2
    double momenta1 : momentum 1
    double momenta2 : momentum 2
    double q1 : effective mass for first moment
    double q2 : effective mass for second moment
    double kT : Boltzmann temperature
*/
{
    // Set thermostat variables
    eta1 = var1;
    eta2 = var2;
    p_1 = momenta1;
    p_2 = momenta2;
    q_1 = q1;
    q_2 = q2;
    kT = kT;
}

double GGMT::update_thermostat(double momentum, double mass, double t_step)
/*
    Function to update thermostat variables
    double momentum : particle momentum
    double mass : mass of particle
    double t_step : timestep size
    @return new momentum
*/
{
    // To update variables need Suzuki-Yoshida decomposition
    double w1, w2, w3;
    w1 = w3 = 1 / (2 - (std::pow(2, 1/3)));
    w2 = 1 - (2 * w1);
    double n_sy[3] = {w1, w2, w3};
    int n_c = 2;

    // Iterate and update variables
    for (int i = 0; i < n_c; i++)
    {
        for (double w : n_sy)
        {
            // Set dt
            double dt = (w * t_step) / n_c;

            // Set constant g
            double g = kT + (std::pow(momentum, 2) / mass);

            // Thermostat variable updating
            double g_1 = (std::pow(momentum, 2) / mass) - kT;
            p_1 += (dt / 2) * g_1;
            double g_2 = (std::pow(momentum, 4) / (3 * std::pow(mass, 2))) - std::pow(kT, 2);
            p_2 += (dt / 2) * g_2;
            double lambda = (p_1 / q_1) + (kT * p_2 / q_2);
            momentum *= std::exp(- (dt / 4) * lambda);
            momentum *= std::pow((1 / (1 + (2 * std::pow(momentum, 2) * (p_2 / (q_2 * 3 * mass)) * (dt / 2)))), 1/2);
            momentum *= std::exp(- (dt / 4) * lambda);
            eta1 += (dt * (p_1 / q_1));

            // Reset constant g
            g = kT + (std::pow(momentum, 2) / mass);

            // Finish thermostat variable update
            eta2 += ((dt * g * p_2) / q_2);
            momentum *= std::exp(-(dt / 4) * lambda);
            g_2 = (std::pow(momentum, 4) / (3 * std::pow(mass, 2))) - std::pow(kT, 2); 
            p_2 += (dt / 2) * g_2; 
            g_1 = (std::pow(momentum, 2) / mass) - kT;
            p_1 += (dt / 2) * g_1; 
        }
    }

    // Return new particle momentum
    return momentum;
}