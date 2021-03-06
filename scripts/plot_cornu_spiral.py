#!/usr/bin/env python3
"""Plot values for the Fresnel integrals."""
import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess
import csv_reader as csv


OUT_FILENAME = "data/cornu.csv"


def plot_cornu_spiral():
    """Plot the Cornu spiral as a line graph."""
    c_vals, s_vals = calculate_values()
    plt.plot(c_vals, s_vals, '-', linewidth=1)
    plt.axis("equal")
    plt.xlabel("C(u)")
    plt.ylabel("S(u)")
    plt.show()


def calculate_values():
    """Calculate the Fresnel integral values, using the example binary.
    Just return the values for the C and S integrals."""
    # Find the location of the binary relative to this script.
    binpath = (os.path.dirname(os.path.realpath(__file__))
               + "/../bin/fresnel_example")
    subprocess.check_call([binpath, "-f", OUT_FILENAME])

    # Process the output - extract just the C and S integral values.
    with open(OUT_FILENAME, "r") as f:
        val_map = csv.to_val_map(f.readlines())

    return np.array(val_map["c value"]), np.array(val_map["s value"])


if __name__ == '__main__':
    plot_cornu_spiral()

