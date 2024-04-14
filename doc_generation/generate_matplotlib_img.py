import ctypes
import os
from ctypes import CDLL
from typing import List

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.figure import Figure
from matplotlib.patches import Rectangle, Polygon

example_integer = CDLL("../example_integer.so")


class Integral(ctypes.Structure):
    _fields_ = [
        ("integral_func", ctypes.CFUNCTYPE(ctypes.c_float, ctypes.c_float)),
        ("start_point", ctypes.c_float),
        ("end_point", ctypes.c_float),
        ("calculating_accuracy", ctypes.c_int),
    ]


def get_integral_from_index(index: int) -> Integral:
    func = getattr(example_integer, f"get_{index}")
    func.argtypes = [ctypes.c_int]
    func.restype = Integral
    integral = func(100)
    return integral


def generate_func_on_plot(integral: Integral, ax: plt.Axes) -> None:
    x = np.linspace(integral.start_point, integral.end_point, 10000)
    y = np.array([integral.integral_func(xi) for xi in x])
    plt.figure(figsize=[100, 100])
    ax.plot(x, y)


def generate_plot_for_rectangle(index: int, data: list[tuple[float]]) -> Figure:
    fig, ax = plt.subplots()
    integral = get_integral_from_index(index)
    generate_func_on_plot(integral, ax)
    for x1, step, y in data:
        ax.add_patch(Rectangle((x1, 0), step, y, linewidth=1, edgecolor='r', facecolor='none'))
    return fig


def generate_plot_for_trapezoid(index: int, data: list[tuple[float]]) -> Figure:
    integral = get_integral_from_index(index)
    fig, ax = plt.subplots()
    generate_func_on_plot(integral, ax)
    for x1, x2, y1, y2 in data:
        x = [x1, x1, x2, x2]
        y = [0, y1, y2, 0]
        ax.add_patch(Polygon(xy=list(zip(x, y)), linewidth=1, edgecolor='r', facecolor='none'))
    return fig


def get_color_for_value(value: int) -> str:
    match value:
        case -1:
            return "red"
        case 0:
            return "gray"
        case 1:
            return "green"


def generate_plot_for_montecarlo(index: int, data: list[tuple[float, float, int]]) -> Figure:
    integral = get_integral_from_index(index)
    fig, ax = plt.subplots()
    generate_func_on_plot(integral, ax)
    for x, y, value in data:
        y = -y if value < 0 else y
        ax.plot(x, y, 'o', color=get_color_for_value(value), markersize=1)
    return fig


file_to_func = {
    "rectangle": generate_plot_for_rectangle,
    "trapezoid": generate_plot_for_trapezoid,
    "montecarlo": generate_plot_for_montecarlo
}


def read_data(file_name: str) -> list[map[float]]:
    with open(file_name, "r") as file:
        return [map(float, line.split(";")) for line in file.readlines()]


def main() -> None:
    directory = "../doc_data/"
    for file_name in os.listdir("../doc_data/"):
        if file_name.endswith(".jpg"):
            continue
        index, file_type = file_name.split("_")
        plot = file_to_func[file_type](index, read_data(directory + file_name))
        if plot:
            plot.savefig(f"../doc/{file_name}.jpg", dpi=1000)
            plt.close(plot)


if __name__ == '__main__':
    main()
