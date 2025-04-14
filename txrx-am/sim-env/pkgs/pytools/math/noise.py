import numpy as np

def awgn(signal, snr_db):
    """
    Добавляет аддитивный белый гауссовский шум (AWGN) к сигналу с заданным SNR.

    Параметры:
        signal (np.ndarray): исходный сигнал.
        snr_db (float): требуемое отношение сигнал/шум в децибелах.

    Возвращает:
        np.ndarray: сигнал с добавленным шумом.
    """
    # Вычисляем мощность сигнала
    signal_power = np.mean(signal ** 2)
    # Перевод SNR из дБ в линейное значение
    snr_linear = 10 ** (snr_db / 10.0)
    # Вычисляем мощность шума
    noise_power = signal_power / snr_linear
    # Генерируем шум
    noise = np.sqrt(noise_power) * np.random.randn(*signal.shape)
    return signal + noise
