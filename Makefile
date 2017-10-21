all: bin/monte_carlo_example bin/fresnel 

bin/monte_carlo_example: src/monte_carlo.cc src/monte_carlo_example.cc
	g++ src/monte_carlo.cc src/monte_carlo_example.cc -lgsl -lgslcblas -lm -Wall -o bin/monte_carlo_example

bin/fresnel: src/fresnel.cc
	g++ src/fresnel.cc -lgsl -lgslcblas -lm -Wall -o bin/fresnel

clean:
	rm bin/*

