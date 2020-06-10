import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
n = 8 # Número de vértices do grafo exemplo

# Adicionando os vértices em G
for i in range(n):
    G.add_node(i)

# Acrescentando suas arestas
for i in range(1, n):
    G.add_edge(0, i)

# Desenho de G
nx.draw(G, pos=nx.circular_layout(G), with_labels=True, font_weight='bold')
plt.show()