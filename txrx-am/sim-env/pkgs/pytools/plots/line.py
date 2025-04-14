import matplotlib.pyplot as plt

def line(x, y, title="Line Plot", xlabel="X", ylabel="Y", **kwargs):
    """
    Строит линейный график.

    Параметры:
        x (array-like): значения по оси X.
        y (array-like): значения по оси Y.
        title (str): заголовок графика.
        xlabel (str): название оси X.
        ylabel (str): название оси Y.
        **kwargs: дополнительные параметры для plt.plot.
    """
    plt.figure()
    plt.plot(x, y, **kwargs)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)