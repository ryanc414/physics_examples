#!/usr/bin/env python3
"""Plot values for the Fresnel integrals."""
import matplotlib.pyplot as plt
import numpy as np
import os
import subprocess


def plot_fresnel_example():
    """Plot the values as a line graph."""
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
    raw_output = subprocess.check_output([binpath]).strip().decode("ascii")

    # Process the output - extract just the C and S integral values.
    lines = [line.split(',') for line in raw_output.split('\n')]
    headings = lines[0]
    values = [[float(val) for val in line] for line in lines[1:]]
    val_map = {heading: [val[i] for val in values]
               for i, heading in enumerate(headings)}

    return np.array(val_map["c value"]), np.array(val_map["s value"])


if __name__ == '__main__':
    plot_fresnel_example()

