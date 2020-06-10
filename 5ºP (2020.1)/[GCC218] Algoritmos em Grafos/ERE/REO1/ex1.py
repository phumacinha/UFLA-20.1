# N é a quantidade de casos que serão testados
N = int(input())

# Lista de listas de adjacência
grafos = []

for n in range(N):
    num_vertices_arestas = input().split()

    # V é a quantidade de vértices e E de arestas
    V, E = int(num_vertices_arestas[0]), int(num_vertices_arestas[1])

    # Lista de adjacencia de G
    lista_de_adjacencia = [[] for _ in range(V)]

    # Acrescentando suas arestas
    for _ in range(E):
        aresta = input().split()
        lista_de_adjacencia[int(aresta[0])].append(int(aresta[1]))

    grafos.append(lista_de_adjacencia)

caso = 1
for grafo in grafos:
    print('Caso {}:'.format(caso), end='')
    caso = caso + 1

    n = len(grafo)
    cor = ['B']*n

    # Nível de hierarquia
    hierarquia = 1

    def pathR_visit(s):
        global hierarquia
        # Inicializando o vertice origem
        cor[s] = 'C'
        
        vizinhos = grafo[s]
        
        for v in vizinhos:
            print('{}{}-{}'.format('  '*hierarquia, s, v), end='')
            if(cor[v] == 'B'):
                print(' pathR(G,{})'.format(v))
                cor[v] = 'C'
                hierarquia = hierarquia + 1
                pathR_visit(v)
            else:
                print('')

        hierarquia = hierarquia if hierarquia == 1 else hierarquia - 1
        cor[s] = 'P'

    for u in range(n):
        if(cor[u] == 'B' and len(grafo[u]) > 0):
            print('')
            pathR_visit(u)
        
    print('')