import matplotlib.pyplot as plt

def plot_scatter(x, y, title="Scatter Plot", xlabel="X", ylabel="Y", **kwargs):
    """
    Строит scatter-график.

    Параметры:
        x (array-like): значения по оси X.
        y (array-like): значения по оси Y.
        title (str): заголовок графика.
        xlabel (str): название оси X.
        ylabel (str): название оси Y.
        **kwargs: дополнительные параметры для plt.scatter.
    """
    plt.figure()
    plt.scatter(x, y, **kwargs)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
