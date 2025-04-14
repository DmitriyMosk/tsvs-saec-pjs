import numpy as np
import matplotlib.pyplot as plt
from scipy.signal import hilbert

plt.style.use('seaborn-v0_8-ticks')

# Параметры
fs = 1000
T = 1
t = np.linspace(0, T, int(fs*T), endpoint=False)
f_signal = 5
f_shift = 20
delay_samples = 100

signal = np.cos(2*np.pi*f_signal*t)
analytic_signal = hilbert(signal)

def plot_spectrum(signal, title, ax, color='b'):
    n = len(signal)
    freq = np.fft.fftshift(np.fft.fftfreq(n, 1/fs))
    spectrum = np.fft.fftshift(np.abs(np.fft.fft(signal)/n))
    ax.plot(freq, spectrum, color=color)
    ax.set_xlim(-50, 50)
    ax.set_title(title)
    ax.set_xlabel('Частота (Гц)')
    ax.set_ylabel('Амплитуда')

fig1, axs1 = plt.subplots(4, 2, figsize=(15, 16))

# Исходный сигнал
axs1[0,0].plot(t, signal)
axs1[0,0].set_title('Исходный сигнал (время)')
plot_spectrum(signal, 'Спектр исходного сигнала', axs1[0,1])

# Умножение на комплексную экспоненту
axs1[1,0].plot(t, np.real(analytic_signal * np.exp(1j*2*np.pi*f_shift*t)))
axs1[1,0].set_title('Комплексная экспонента (время)')
plot_spectrum(analytic_signal * np.exp(1j*2*np.pi*f_shift*t), 
            'Спектр: комплексная экспонента', axs1[1,1], '#2ca02c')

# Умножение на косинус
axs1[2,0].plot(t, np.real(analytic_signal * np.cos(2*np.pi*f_shift*t)))
axs1[2,0].set_title('Умножение на cos (время)')
plot_spectrum(analytic_signal * np.cos(2*np.pi*f_shift*t), 
            'Спектр: умножение на cos', axs1[2,1], '#d62728')

# Умножение на 2*косинус
axs1[3,0].plot(t, np.real(analytic_signal * 2*np.cos(2*np.pi*f_shift*t)))
axs1[3,0].set_title('Умножение на 2cos (время)')
plot_spectrum(analytic_signal * 2*np.cos(2*np.pi*f_shift*t), 
            'Спектр: умножение на 2cos', axs1[3,1], '#9467bd')

plt.tight_layout()

fig2, axs2 = plt.subplots(2, 2, figsize=(12, 8))

# Задержка мнимой части
imag_delayed = np.roll(np.imag(analytic_signal), delay_samples)
delayed_signal = np.real(analytic_signal) + 1j*imag_delayed

axs2[0,0].plot(t, np.real(delayed_signal), label='Real')
axs2[0,0].plot(t, np.imag(delayed_signal), label='Imag')
axs2[0,0].set_title(f'Задержка мнимой части ({delay_samples} отсчетов)')
plot_spectrum(delayed_signal, 'Спектр с задержкой мнимой части', axs2[0,1])

# Задержка действительной части (добавим для полноты)
real_delayed = np.roll(np.real(analytic_signal), delay_samples)
delayed_signal_real = real_delayed + 1j*np.imag(analytic_signal)

axs2[1,0].plot(t, np.real(delayed_signal_real), label='Real')
axs2[1,0].plot(t, np.imag(delayed_signal_real), label='Imag')
axs2[1,0].set_title(f'Задержка действительной части ({delay_samples} отсчетов)')
plot_spectrum(delayed_signal_real, 'Спектр с задержкой действительной части', axs2[1,1])

plt.tight_layout()
plt.show()
