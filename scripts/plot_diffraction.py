#!/usr/bin/env python3
"""Plot Fresnel diffraction pattern."""
import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess
import csv_reader as csv

DIRNAME = os.path.dirname(os.path.realpath(__file__))
DISTANCES = (30, 50, 100)
OUTPUT_FILENAMES = ["{0}/../data/{1}cm_diffraction.csv".format(DIRNAME, d)
                    for d in DISTANCES]
FIG_TITLES = ["{}cm Diffraction".format(d) for d in DISTANCES]


def plot_diffraction_patterns():
    """Plot the diffraction amplitudes and phases."""
    calculate_diffractions()

    for i, output_filename in enumerate(OUTPUT_FILENAMES):
        plt.figure(i + 1)
        x_vals, amplitudes, phases = get_diff_values(output_filename)
        plt.suptitle(FIG_TITLES[i])

        # Create two subplots - one for the amplitude, one for the phase.
        plt.subplot(121)
        plt.plot(x_vals, amplitudes, '-', linewidth=1)
        plt.xlabel("x")
        plt.ylabel("normalised amplitude")

        plt.subplot(122)
        plt.plot(x_vals, phases, '-', linewidth=1)
        plt.xlabel("x")
        plt.ylabel("normalised phase")

    plt.show()


def calculate_diffractions():
    """Calculate the values used to plot the diffraction patterns.
    The executable will write these out to files under data/."""
    # Find the location of the binary relative to this script.
    binpath = DIRNAME + "/../bin/fresnel_diffraction"

    # The diffraction binary will output data to files.
    subprocess.call([binpath])


def get_diff_values(output_filename):
    """Get the required values from the given output CSV file."""
    with open(output_filename) as diff_file:
        diff_lines = diff_file.readlines()

    val_map = csv.to_val_map(diff_lines)
    return np.array(val_map["x"]), np.array(val_map["amplitude"]), np.array(val_map["phase"])


if __name__ == '__main__':
    plot_diffraction_patterns()

