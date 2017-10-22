#!/usr/bin/env python3
"""Process CSV file contents."""

def to_val_map(csv_lines):
    lines = [line.split(',') for line in csv_lines]
    headings = lines[0]
    values = [[float(val) for val in line] for line in lines[1:]]
    return {heading.strip(): [val[i] for val in values]
            for i, heading in enumerate(headings)}

