In this repository I'm adding/tidying up some scripts I wrote during
university while learning C++, in the context of physical simulations.

Run `make all` from the top level to compile all the binaries. GSL is
required to link against.

Plots of the values calculated can then be viewed by running one of the
scripts/plot... python wrappers.

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
