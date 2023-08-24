/*
    Tom Egg
    August 22, 2023
    cpp file for Particle
*/

// Include particle
#include "Particle.h"

Particle::Particle(const double coords[], const double momenta[], const double mass[])
/*
    Constructor for a particle
    double* coords : pointer to coordinate array with x and y
    double* momenta : pointer to momentum array 
    double* mass : pointer to array with two masses for adiabatic separation
*/
{
    // Set particle variables
    x = coords[0];
    y = coords[1];
    p_x = momenta[0];
    p_y = momenta[1];
    m_x = mass[0];
    m_y = mass[1];

    // Constants governing potential
    d = 5.0;
    a = 1.0;
    omega = 1.0;
    lam = 2.878;
}

void Particle::propagate_position(double t_step)
/*
    Function to update position
    double t_step : simulation timestep
*/
{
    // Update x and y
    x += ((t_step * p_x) / (2 * m_x));
    y += ((t_step * p_y) / (2 * m_y));

    // Return
    return;
}

void Particle::propagate_x(double t_step)
/*
    Function to propagate x only
    double t_step : simulation timestep
*/
{
    // Update x
    x += ((t_step * p_x) / m_x);
}

void Particle::propagate_y(double t_step)
/*
    Function to propagate y only
    double t_step : simulation timestep
*/
{
    // Update x
    y += ((t_step * p_y) / (2 * m_y));
}

void Particle::propagate_momentum(double t_step)
/*
    Function to update momentum
    double t_step : simulation timestep
*/
{
    // Set forces
    force_x = - ((((4 * d * x) / (std::pow(a, 4))) * (std::pow(x, 2) - std::pow(a, 2))) + (y * lam));
    force_y = - ((m_y * std::pow(omega, 2) * y) + (lam * x));

    // Update momentum
    p_x += (t_step / 2) * force_x;
    p_y += (t_step / 2) * force_y;

    // Return
    return;
}

void Particle::propagate_py(double t_step)
/*
    Function to propagate y momentum only
    double t_step : simulation timestep
*/
{
    // Set force
    force_y = - ((m_y * std::pow(omega, 2) * y) + (lam * x));

    // Update momentum
    p_y += (t_step / 2) * force_y;
}

void Particle::propagate_px(double t_step)
/*
    Function to propagate y momentum only
    double t_step : simulation timestep
*/
{
    // Set force
    force_x = - ((((4 * d * x) / (std::pow(a, 4))) * (std::pow(x, 2) - std::pow(a, 2))) + (y * lam));

    // Update momentum
    p_x += (t_step / 2) * force_x;
}

void Particle::propagate_momentum(double t_step, GGMT& thermostat, char idx, const int& factor)
/*
    Function to propagate momentum through thermostat operator
    double t_step : simulation timestep
    GGMT thermostat : thermostat governing 
    char idx : index to indicate which thermostat is propagated
*/
{
    // Switch statement
    switch (idx)
    {
        case 'x':
            thermostat.update_thermostat(p_x, m_x, t_step, factor);
            break;
                
        case 'y':
            thermostat.update_thermostat(p_y, m_y, t_step, factor);
            break;

        default:
            std::cerr << "Invalid index: " << idx << ". Expected 'x' or 'y'";
            break;
    }

    // Return
    return;
}

double Particle::get_x()
/*
    Function to return x coordinate
    @return x : x-coordinate
*/
{
    // Return x
    return x;
}

double Particle::get_y()
/*
    Function to return y coordinate
    @return x : y-coordinate
*/
{
    // Return y
    return y;
}

double Particle::get_xmomentum()
/*
    Function to return x momentum
    @return p_x : x momentum
*/
{
    // Return momentum
    return p_x;
}

double Particle::get_ymomentum()
/*
    Function to return y momentum
    @return x : y momentum
*/
{
    // Return momentum
    return p_y;
}
