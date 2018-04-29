In this repository I'm adding/tidying up some scripts I wrote during
university while learning C++, in the context of physical simulations.

Run `make all` from the top level to compile all the binaries. GSL is
required to link against.

Plots of the values calculated can then be viewed by running one of the
scripts/plot... python wrappers.

Scripts
=======
scripts/plot_cornu_spiral.py
----------------------------
Plots the Cornu spiral by numerically integrating the Fresnel integrals.

scripts/plot_diffraction.py
---------------------------
Plot near-field diffraction patterns from different sized appertures.

`make` targets:
===============

bin/monte_carlo_example
-----------------------
Finds an aproximate value to the following integral numerically:

10^6 * Integrate(sin(x_0 + x_1 + x_2 + x_3 + x_4 + x_5 + x_6 + x_7)
                 dx_0 dx_1 dx_2 dx_2 dx_3 dx_4 dx_5 dx_6 dx_7)

With all integration variables taking values from 0 to S = pi/8.

Uses Monte-Carlo estimation to sample pseudo-random points over the 8D
integral space and provide an estimate for the integral value and error.

bin/fresnel_example
-------------------
Integrate the Fresnel integrals numerically. CSV data is output to file,
from which a Cornu spiral can be plotted.

bin/fresnel_diffraction
-----------------------
Apply Fresnel integrals to near-field diffraction of various sized
appertures. CSV data is output to files under data/ from which
diffraction patterns can be plotted.

bin/driven_pendulum
-------------------
Simulate a driven pendulum by numerically solving a pair of ODEs
representing the dynamics of the system. CSV data is output to file,
from which the pendulum motion can be plotted.

