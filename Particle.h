/*
    Tom Egg
    August 22, 2023
    Class for a particle governed by two GGMT thermostat
*/

// Include libraries
#include <iostream>
#include "GGMT.h"

// Indicate source file
#pragma once

// Particle class
class Particle
{
    // Public
    public:
        Particle(const double coords[], const double momenta[], const double mass[]);
        void propagate_position(double t_step);
        void propagate_momentum(double t_step);
        void propagate_momentum(double t_step, GGMT thermostat, char idx);
        double get_x();
        double get_xmomentum();
        double get_ymomentum();

    // Private
    private:

        // Particle and thermostat variables
        double x, y;        // x and y coordinates
        double p_x, p_y;    // x and y momenta
        double m_x, m_y     // x and y masses

        // Constants governing potential
        d = 4;
        a = 1;
        omega = 1;
        lambda = 2.878

        // Set force as gradient of potential
        double force_x, force_y;
};