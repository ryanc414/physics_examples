all: bin/monte_carlo_example bin/fresnel_example bin/fresnel_diffraction bin/driven_pendulum bin/fft

bin/monte_carlo_example: src/monte_carlo.cc src/estimate.hh
	g++ src/monte_carlo.cc -lgsl -lgslcblas -lm -Wall -g -Og -o bin/monte_carlo_example

bin/fresnel_example: src/fresnel.cc src/fresnel_example.cc src/out_file.cc src/out_file.hh src/fresnel.hh src/estimate.hh
	g++ src/fresnel.cc src/fresnel_example.cc src/out_file.cc -lgsl -lgslcblas -lm -Wall -g -Og -o bin/fresnel_example

bin/fresnel_diffraction: src/fresnel.cc src/fresnel_diffraction.cc src/fresnel.hh src/estimate.hh
	g++ src/fresnel_diffraction.cc src/fresnel.cc -lgsl -lgslcblas -lm -Wall -g -Og -o bin/fresnel_diffraction

bin/driven_pendulum: src/driven_pendulum.cc src/out_file.cc src/out_file.hh
	g++ src/driven_pendulum.cc src/out_file.cc -lgsl -lgslcblas -lm -Wall -g -Og -std=c++11 -o bin/driven_pendulum

bin/fft: src/fft.cc src/out_file.cc src/out_file.hh
	g++ src/fft.cc src/out_file.cc -lfftw3 -lm -Wall -g -Og -std=c++11 -o bin/fft

.PHONY: clean
clean:
	rm -f bin/*

