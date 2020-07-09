import networkx as nx
import matplotlib.pyplot as plt

G = nx.Graph()
nm = input().split()

for n in range(int(nm[0])):
    G.add_node(n+1)

for _ in range(int(nm[1])):
    aresta_peso = input().split()
    G.add_edge(int(aresta_peso[0]), int(aresta_peso[1]), weight=int(aresta_peso[2]))
    #print('inserindo aresta ({}, {}) com peso {}'.format(int(aresta_peso[0]), int(aresta_peso[1]), int(aresta_peso[2])))

pos = nx.circular_layout(G)
nx.draw(G, with_labels=True, pos=pos)

labels = nx.get_edge_attributes(G,'weight')
nx.draw_networkx_edge_labels(G, pos=pos, edge_labels=labels)
plt.show()