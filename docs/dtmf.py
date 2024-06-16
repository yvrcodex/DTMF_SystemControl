import numpy as np
import matplotlib.pyplot as plt
import os
# Frequências DTMF
frequencias_linha = [697, 770, 852, 941]
frequencias_coluna = [1209, 1336, 1477, 1633]

# Mapeamento dos caracteres DTMF
dtmf_caracteres = [
    ['1', '2', '3', 'A'],
    ['4', '5', '6', 'B'],
    ['7', '8', '9', 'C'],
    ['*', '0', '#', 'D']
]

# Tempo (em segundos) para dois ciclos da frequência mínima
tempo_final = 2 * (1 / 697)
t = np.linspace(0, tempo_final, 1000)
t_ms = t * 1000  # Converter para milissegundos

# Criar a figura para sinais individuais
fig_individuais, axs_individuais = plt.subplots(4, 4, figsize=(15, 10))
fig_individuais.suptitle('DTMF - INDIVIDUAL TONES')

# Criar a figura para sinais resultantes
fig_resultantes, axs_resultantes = plt.subplots(4, 4, figsize=(15, 10))
fig_resultantes.suptitle('DTMF - COMPOSITE TONES')

# Loop para gerar os gráficos
for i, linha in enumerate(frequencias_linha):
    for j, coluna in enumerate(frequencias_coluna):
        # Calcular os sinais senoidais e normalizar para 0 a 5 volts
        sinal_linha = (np.sin(2 * np.pi * linha * t) + 1) * 2.5  # Normalizar para 0 a 5V
        sinal_coluna = (np.sin(2 * np.pi * coluna * t) + 1) * 2.5  # Normalizar para 0 a 5V
        sinal_resultante = (sinal_linha + sinal_coluna) / 2  # Média dos dois sinais para 0 a 5V

        # Plotar os sinais individuais
        ax_ind = axs_individuais[i, j]
        ax_ind.plot(t_ms, sinal_linha)
        ax_ind.plot(t_ms, sinal_coluna)
        ax_ind.set_xlabel('Tempo (ms)')
        ax_ind.set_ylabel('Amplitude (V)')
        ax_ind.set_title(f'DTMF {dtmf_caracteres[i][j]} ({linha}Hz, {coluna}Hz)')
        ax_ind.grid(True)

        # Plotar o sinal resultante
        ax_res = axs_resultantes[i, j]
        ax_res.plot(t_ms, sinal_resultante, color='red')
        ax_res.set_xlabel('Tempo (ms)')
        ax_res.set_ylabel('Amplitude (V)')
        ax_res.set_title(f'DTMF {dtmf_caracteres[i][j]} ({linha}Hz, {coluna}Hz)')
        ax_res.grid(True)

# Ajustar o layout e mostrar as figuras
plt.tight_layout()
fig_individuais.tight_layout(rect=[0, 0.03, 1, 0.95])
fig_resultantes.tight_layout(rect=[0, 0.03, 1, 0.95])
plt.show()

os.system('cls');
