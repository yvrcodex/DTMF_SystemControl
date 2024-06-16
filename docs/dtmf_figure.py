import matplotlib.pyplot as plt

# Dados da tabela DTMF
frequencias_linha = [697, 770, 852, 941]
frequencias_coluna = [1209, 1336, 1477, 1633]
dtmf_caracteres = [
    ['1', '2', '3', 'A'],
    ['4', '5', '6', 'B'],
    ['7', '8', '9', 'C'],
    ['*', '0', '#', 'D']
]

# Criar a figura e o eixo
fig, ax = plt.subplots(figsize=(8, 6))

# Ocultar os eixos
ax.axis('tight')
ax.axis('off')

# Criar a tabela
col_labels = ['1209 Hz', '1336 Hz', '1477 Hz', '1633 Hz']
row_labels = ['697 Hz', '770 Hz', '852 Hz', '941 Hz']
cell_text = dtmf_caracteres

# Adicionar a tabela à figura
table = ax.table(cellText=cell_text,
                 rowLabels=row_labels,
                 colLabels=col_labels,
                 cellLoc='center',
                 loc='center',
                 cellColours=[['#f0f0f0' for _ in range(4)] for _ in range(4)])

# Adicionar título
plt.title('Tabela DTMF - Frequências e Tons')

# Ajustar o layout
plt.tight_layout()

# Salvar a figura como PNG
plt.savefig('dtmf_tabela.png', dpi=300)

# Mostrar a figura
plt.show()
