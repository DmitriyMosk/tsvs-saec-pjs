import numpy as np
import matplotlib.pyplot as plt

# Параметры сигнала
fs = 1000                  # Частота дискретизации (samples per second)
t = np.linspace(0, 1, fs, endpoint=False)  # Временная ось, 1 секунда
freq = 5                   # Частота сигнала в Гц
signal = np.sin(2 * np.pi * freq * t)

# Добавляем шум
noise = 0.5 * np.random.randn(fs)
noisy_signal = signal + noise

# Задаём порог для squelch
threshold = 0.5

# Функция squelch: если |сигнал| < threshold, то значение обнуляется
squelched_signal = np.where(np.abs(noisy_signal) >= threshold, noisy_signal, 0)

# Построение графиков
plt.figure(figsize=(12, 8))

# График сигнала без squelch (с шумом)
plt.subplot(2, 1, 1)
plt.plot(t, noisy_signal, label='Сигнал без squelch')
plt.axhline(y=threshold, color='red', linestyle='--', label='Порог')
plt.axhline(y=-threshold, color='red', linestyle='--')
plt.title('Сигнал с шумом (без squelch)')
plt.xlabel('Время [с]')
plt.ylabel('Амплитуда')
plt.legend()
plt.grid(True)

# График сигнала с применённым squelch
plt.subplot(2, 1, 2)
plt.plot(t, squelched_signal, label='Сигнал с squelch', color='green')
plt.axhline(y=threshold, color='red', linestyle='--', label='Порог')
plt.axhline(y=-threshold, color='red', linestyle='--')
plt.title('Сигнал после применения squelch')
plt.xlabel('Время [с]')
plt.ylabel('Амплитуда')
plt.legend()
plt.grid(True)

plt.tight_layout()
plt.show()

