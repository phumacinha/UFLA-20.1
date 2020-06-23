'''
    ex01.py: Dado um grafo não-orientado qualquer G=(V,E), determinar se esse 
        grafo é bipartido. Deve-se implementar uma adaptação no Algoritmo de
        Busca em Profundidade para obter o resultado.

    Autor: Pedro Antônio de Souza
'''
arquivo = open('bipartido.txt', 'r')
dados = arquivo.readlines()

n = int(dados.pop(0).rstrip())

grafo = dict()

for v in range(n):
    grafo[v] = list()

for aresta in dados:
    aresta = aresta.rstrip().split()
    grafo[int(aresta[0])].append(int(aresta[1]))
    grafo[int(aresta[1])].append(int(aresta[0]))

visitado = [False for i in range(n)]

cor = [0 for i in range(n)]

def eh_bipartido (grafo, v):
    for u in grafo[v]:
        if (not visitado[u]):
            visitado[u] = True

            cor[u] = not cor[v]

            if (not eh_bipartido(grafo, u)):
                return False

        elif (cor[u] == cor[v]):
            return False

    return True          

def main():
    visitado[0] = True
    cor[0] = 0

    if (eh_bipartido(grafo, 0)):
        print('sim')
    else:
        print('nao')

if __name__ == '__main__':
    main()