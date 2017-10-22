all: bin/monte_carlo_example bin/fresnel_example bin/fresnel_diffraction 

bin/monte_carlo_example: src/monte_carlo.cc src/monte_carlo_example.cc
	g++ src/monte_carlo.cc src/monte_carlo_example.cc -lgsl -lgslcblas -lm -Wall -g -Og -o bin/monte_carlo_example

bin/fresnel_example: src/fresnel.cc src/fresnel_example.cc
	g++ src/fresnel.cc src/fresnel_example.cc -lgsl -lgslcblas -lm -Wall -g -Og -o bin/fresnel_example

bin/fresnel_diffraction: src/fresnel.cc src/fresnel_diffraction.cc
	g++ src/fresnel_diffraction.cc src/fresnel.cc -lgsl -lgslcblas -lm -Wall -g -Og -o bin/fresnel_diffraction

.PHONY: clean
clean:
	rm -f bin/*

