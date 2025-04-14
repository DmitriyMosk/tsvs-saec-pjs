import matplotlib.pyplot as plt

def plot_histogram(data, bins=10, title="Histogram", xlabel="Value", ylabel="Frequency", **kwargs):
    """
    Строит гистограмму.

    Параметры:
        data (array-like): данные для гистограммы.
        bins (int): количество корзин.
        title (str): заголовок графика.
        xlabel (str): название оси X.
        ylabel (str): название оси Y.
        **kwargs: дополнительные параметры для plt.hist.
    """
    plt.figure()
    plt.hist(data, bins=bins, **kwargs)
    plt.title(title)
    plt.xlabel(xlabel)
    plt.ylabel(ylabel)
    plt.grid(True)
