Monte Carlo Integration:

Using C++ I wrote an algorithm ('MonteCarlo.cc') to find an approximate value of the integral:

10^6 * Int(sin(x0+x1+x2+x3+x4+x5+x6+x7)dx0dx1dx2dx3dx4dx5dx6dx7)

running over all paramaters from 0 to s (s = pi/8). The value found converged
towards the analytical result (537.1873411) with increasing number of samples N
as illustrated in the plot 'MonteCarloResults.png', note the error bars show the
standard deviation of the entire data set (nt = 25 calculations), not the 
uncertainty in the mean.

The errors for each value of N were plotted in 'LogLogErrors.png' using a log-log
scaling. The straight line trend with a gradient of ~-0.5 supports the
N^-0.5 power law for errors.

For N = 10^7 samples and taking the mean of 25 calculations, the integral's value
was given as 537.187(3).


Fresnel Integrals

Using GSL integration routine I wrote an algorithm ('Fresnel.cc') to numerically
evaluate the Fresnel integrals for various values of the parameter u. C(u) and
S(u) were plotted on the x and y axes respectively in 'cornu.png' with points 
corresponding to values of u in the range +8 to -8.


Diffraction from a single slit

Using the Fresnel integration algorithm above as a basis I wrote an algorithm
('Diffraction.cc') to find the diffraction pattern from a single slit. This
was done by evaluating the Fresnel integrals accross the slit to give the
real and imaginary components of the wavefunction, moving both of the 
integration limits by the same distance x to evaluate the wavefunction at each
position on the screen measured in the direction perpendicular
to the slit (assuming that the source is at infinity, i.e. the slit is illuminated
by plane waves).

From the wavefunction the amplitude and phase can be calculated from the
modulus squared and arctan of the imaginary/real ratio. Since only relative
amplitudes and phases matter this was normalised by the amplitude/phase at
x = 0.

The amplitudes and phases for screens at distance D = 30cm, 50cm and 100cm were
plotted in various files. As D increases, the amplitude pattern tends
towards the Fraunhofer limit of a sinc function.