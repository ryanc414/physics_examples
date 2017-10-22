#!/usr/bin/env python3
"""Plot Fresnel diffraction pattern."""
import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess
import csv_reader as csv

DIRNAME = os.path.dirname(os.path.realpath(__file__))
DISTANCES = (30, 50, 100)
FILENAMES = ["{0}/../data/{1}cm_diffraction.csv".format(DIRNAME, d)
             for d in DISTANCES]
FIG_TITLES = ["{}cm Diffraction".format(d) for d in DISTANCES]


def plot_diffraction_amplitudes():
    """Plot the diffraction amplitudes."""
    calculate_diffractions()

    for i in range(len(FILENAMES)):
        plt.figure(i + 1)
        x_vals, amplitudes, phases = get_diff_values(FILENAMES[i])
        plt.suptitle(FIG_TITLES[i])

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
    """Calculate the Fresnel integral values, using the example binary.
    Just return the values for the C and S integrals."""
    # Find the location of the binary relative to this script.
    binpath = DIRNAME + "/../bin/fresnel_diffraction"

    # The diffraction binary will output data to files.
    subprocess.call([binpath])


def get_diff_values(output_filename):
    with open(output_filename) as diff_file:
        diff_lines = diff_file.readlines()

    val_map = csv.to_val_map(diff_lines)
    return np.array(val_map["x"]), np.array(val_map["amplitude"]), np.array(val_map["phase"])


if __name__ == '__main__':
    plot_diffraction_amplitudes()

