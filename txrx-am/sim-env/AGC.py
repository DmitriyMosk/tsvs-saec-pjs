import numpy as np 
import matplotlib.pyplot as plt
import random 

plt.style.use('seaborn-v0_8-ticks')

###
#   Params
###

# Частота даискретизации [Hz]
fs                          = 1000
# Длительность импульса [сек]
signal_tau                  = 2 
# Колв-во гармоник
signal_components           = 100
# Частота каждой (signal_components) будет с шагом signal_components_freq_step 
signal_components_freq_step = 5
# Затухание сигнала     [db] 
signal_attenuation_n        = 2
# Усиление сигнала      [db]
signal_gain_n               = 2
# SNR [db]
signal_snr                  = 2    
# ADC bit depth [bits] 
adc_bit_depth               = 16   


###
#   End Params
###

"""
Генерит (components) кол-во гармоник
"""
def signal_generate(samples: int, components: int, components_freq_step=None): 
    t = np.arange(0, signal_tau, 1/fs)

    data = dict()

    # стартовая частота
    freq    = 5 + random.random() * 20
    signal  = 0

    for i in range(0, components): 
        freq += components_freq_step or 0;

        component = np.sin(2*np.pi*t*freq) + np.cos(2*np.pi*t*freq)
        signal += component

    data["t"]       = t
    data["signal"]  = signal

    return data


def signal_noise(snr: int): 
    print("gg") 

def signal_gain(db: int):
    print("ggwp") 

def signal_attenuate(db: int, block): 
    print("ggwp")

###
#   Plot functions
###

def plot_max_adc_bit_depth():
    print(adc_bit_depth);

def plot_sequence(x: np.array, y: np.array):
    plt.figure(figsize=(12, 8))
    plt.plot(x, y)

def plot_fft():
    print('ggwp')

###
#   Signal Generation
###

signal = signal_generate(fs * signal_tau, signal_components, signal_components_freq_step)
plot_sequence(x = signal["t"], y = signal["signal"]);

###
#  Test 1
#  Проверка простого усиления сгенерированного сигнала
#  В данном тесте будут выявлены недостатки обычного умножения сигнала
###
















plt.show()

    
