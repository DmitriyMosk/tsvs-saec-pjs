import numpy as np 
#import plots as pl

class sim: 
    def __init__(self, ts, min, max): 
        self.left_size = min 
        self.right_size = max

        # precalc
        self.f_sampling = 1 / ts  

        self.t_sampling = ts
        self.t_quantize_grid = np.arange(min, max, self.f_sampling) 

        # instance empty buffer
        self._buff = np.array([]) 
        self._buff_quantized = np.array([])

    @property
    def fs(self): 
        return self.f_sampling 
    
    @property
    def ts(self): 
        return self.t_sampling
     
    def rx(self, signal): 
        if len(signal) == len(self.t_quantize_grid): 
            self._buff = signal 
        else: 
            ValueError("Problem in __FUNCTION__(def rx(self, signal))")

    def quantize_ch(self, T_q: float, signal: np.ndarray) -> np.ndarray:
        quantized_signal = np.round(signal / T_q) * T_q
        return quantized_signal
    
    @property 
    def buff(self): 
        return self._buff

    @property
    def qbuff(self): 
        return self._buff_quantized 

    def __enter__(self): 
        return self
    
    def __exit__(self, exc_type, exc_value, traceback): 
        return False
    
def sin(_sim: sim, freq, phase=0): 
    if isinstance(_sim, sim) :  
        return np.sin(2*np.pi*freq*_sim.t_quantize_grid + phase)
    else: 
        return np.sin(2*np.pi*freq*_sim + phase)
    
def cos(_sim: sim, freq, phase=0):
    if isinstance(_sim, sim):
        return np.cos(2*np.pi*freq*_sim.t_quantize_grid + phase)
    else:
        return np.cos(2*np.pi*freq*_sim + phase)

def iq_mapping(bits, modulation='QPSK'):
    """
    Функция IQ-маппинга.
    
    Принимает:
      - bits: одномерный массив бит (0 и 1)
      - modulation: тип модуляции ('QPSK' поддерживается)
      
    Возвращает:
      - symbols: массив комплексных символов, полученных по правилу QPSK.
      
    Правила QPSK:
      (0,0) -> -1 - 1j
      (0,1) -> -1 + 1j
      (1,0) ->  1 - 1j
      (1,1) ->  1 + 1j
    """
    if modulation == 'QPSK':
        symbol_map = {
            (0, 0): -1 - 1j,
            (0, 1): -1 + 1j,
            (1, 0):  1 - 1j,
            (1, 1):  1 + 1j
        }
        if len(bits) % 2 != 0:
            raise ValueError("Количество бит должно быть четным для QPSK модуляции.")
        symbols = np.array([symbol_map[(bits[i], bits[i+1])] for i in range(0, len(bits), 2)])
        return symbols
    else:
        raise ValueError("Поддерживаются только QPSK в данной реализации.")
